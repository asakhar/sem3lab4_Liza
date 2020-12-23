#include "Table.hpp"
#include <iomanip>
#include <fstream>

Table::TableItem::TableItem(long acode, BookEdition* abook)
    : code{acode}, book{abook}, next{nullptr}
{
}

Table::TableItem::~TableItem() { delete next; }

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
    stream << std::setw(20) << prev->next->code << ":" << *prev->next->book
           << '\n';
    prev = prev->next;
  }
  return stream;
}

void Table::save(std::string const& filename) const{
  std::ofstream file{filename};
  
}
void Table::open(std::string const& filename) {

}