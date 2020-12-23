#include "Table.hpp"
#include <fstream>
#ifdef DEBUG
#include <iomanip>
#endif

using namespace EditionTypes;

Table::TableItem::TableItem() : code{0}, book{0}, next{0} {}

Table::TableItem::TableItem(long acode, BookEdition* abook)
    : code{acode}, next{nullptr}, book{abook}
{
}

Table::TableItem::~TableItem() { delete next; delete book; }

Table::Table() : m_beforeFirst{new Table::TableItem}, m_numberOfEditions{0} {}

Table::~Table() { delete m_beforeFirst; }

BookEdition*& Table::operator[](long key)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (key <= prev->next->code)
      break;
    prev = prev->next;
  }
  if (prev->next && key == prev->next->code)
    return prev->next->book;
  else
  {
    auto tmp         = prev->next;
    prev->next       = new TableItem{key, nullptr};
    prev->next->next = tmp;
    return prev->next->book;
  }
}
BookEdition Table::erase(long key)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (key <= prev->next->code)
      break;
    prev = prev->next;
  }
  if (prev->next && key == prev->next->code)
  {
    BookEdition tmp{*prev->next->book};
    auto tmp2        = prev->next->next;
    prev->next->next = nullptr;
    delete prev->next;
    prev->next = tmp2;
    m_numberOfEditions--;
    return tmp;
  }
  throw std::out_of_range("Key error.");
}
std::ostream& operator<<(std::ostream& stream, Table const& table)
{
  auto prev = table.m_beforeFirst;
  for (auto i = 0ul; i < table.size(); i++)
  {
    stream
#ifdef DEBUG
        << std::setw(20)
#endif
        << prev->next->code << ":" << *prev->next->book << '\n';
    prev = prev->next;
  }
  return stream;
}

void Table::save(std::string const& filename) const
{
  std::ofstream file{filename};
  for (auto row : *this)
    file << row.first << ';' << row.second->getAllInfo() << '\n';
  file.close();
}
void Table::open(std::string const& filename)
{
  delete m_beforeFirst->next;
  m_beforeFirst->next = nullptr;
  m_numberOfEditions  = 0;
  std::ifstream file{filename};
  while (!file.eof())
  {
    std::string keeper[7];
    long year, code;
    size_t num;
    file >> code;
    file.get();
    std::getline(file, keeper[0], ';');
    std::getline(file, keeper[1], ';');
    file >> year;
    file.get();
    std::getline(file, keeper[2], ';');
    file >> num;
    file.get();
    std::getline(file, keeper[3], ';');
    if (keeper[3] == _typestrings[0])
    {

      (*this) << KeyVal_t<BookEdition>{
          code, new BookEdition{keeper[0], keeper[1], year, keeper[2], num}};
    }
    else if (keeper[3] == _typestrings[1])
    {
      std::getline(file, keeper[4], ';');
      long groups[8];
      size_t count;
      file >> count;
      file.get();
      for (auto i = 0; i < count; i++)
      {
        file >> groups[i];
        file.get();
      }
      (*this) << KeyVal_t<LearningEdition>{
          code, new LearningEdition{keeper[0], keeper[1], year, keeper[2], num,
                                    keeper[4], groups, count}};
    }
    else if (keeper[3] == _typestrings[2])
    {
      size_t count;
      file >> count;
      file.get();
      for (auto i = 0; i < count; i++)
      {
        std::getline(file, keeper[i + 4], ';');
      }
      (*this) << KeyVal_t<ScientificEdition>{
          code, new ScientificEdition{keeper[0], keeper[1], year, keeper[2],
                                      num, keeper + 4, count}};
    }
    else if (keeper[3] == _typestrings[3])
    {
      std::getline(file, keeper[4], ';');
      (*this) << KeyVal_t<FictionEdition>{
          code, new FictionEdition{keeper[0], keeper[1], year, keeper[2], num,
                                   keeper[4]}};
    }
    file.get();
  }
}