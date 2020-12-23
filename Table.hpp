#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
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
  using KeyVal_t = std::pair<long, BookEdition*>;
  Table();
  Table(std::vector<KeyVal_t> books);
  ~Table();
  inline size_t size() const { return m_numberOfEditions; };
  Table& operator<<(KeyVal_t const& keyval);
  BookEdition*& operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
};

#endif // TABLE_HPP
