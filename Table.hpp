#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include <algorithm>
#include <vector>
class Table
{
private:
  struct TableItem
  {
    long code;
    BookEdition* book;
    TableItem* next;
    TableItem(long acode = 0, BookEdition* abook = 0);
    ~TableItem();
  };
  TableItem* m_beforeFirst;
  size_t m_numberOfEditions;

public:
  template <typename _Ty>
  using KeyVal_t = std::pair<long, _Ty*>;
  Table();
  template <typename _Ty>
  Table(std::vector<KeyVal_t<_Ty>> books) : m_numberOfEditions{0}
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
  ~Table();
  inline size_t size() const { return m_numberOfEditions; };
  template <typename _Ty>
  Table& operator<<(KeyVal_t<_Ty> const& keyval)
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
  BookEdition*& operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  void save(std::string const& filename) const;
  void open(std::string const& filename);
};

#endif // TABLE_HPP
