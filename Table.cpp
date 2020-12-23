#include "Table.hpp"
#include <algorithm>
#include <iomanip>

Table::TableItem::TableItem(long acode, BookEdition* abook)
    : code{acode}, book{abook}, next{nullptr}
{
}

Table::TableItem::~TableItem() {
  delete next;
}

Table::Table() : m_beforeFirst{new Table::TableItem}, m_numberOfEditions{0} {}
Table::Table(std::vector<KeyVal_t> books) : m_numberOfEditions{0}
{
  std::sort(books.begin(), books.end(),
            [](auto& fir, auto& sec) { return fir.first < sec.first; });
  auto prev = (m_beforeFirst = new Table::TableItem);
  for (auto& book : books)
  {
    prev->next = new Table::TableItem{book.first, book.second};
    prev       = prev->next;
    m_numberOfEditions++;
  }
}

Table::~Table() {
  delete m_beforeFirst;
}

Table& Table::operator<<(KeyVal_t const& keyval)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (keyval.first < prev->next->code)
      break;
    prev = prev->next;
  }
  auto tmp         = prev->next;
  prev->next       = new TableItem{keyval.first, keyval.second};
  prev->next->next = tmp;
  m_numberOfEditions++;
  return *this;
}
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
  if (prev->next && key == prev->next->code) {
    BookEdition tmp{*prev->next->book};
    auto tmp2 = prev->next->next;
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
    stream << std::setw(20) << prev->next->code << ":" << *prev->next->book;
    prev = prev->next;
  }
  return stream;
}