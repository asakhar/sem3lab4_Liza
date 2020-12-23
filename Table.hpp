#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
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

  struct BookEditionWrapper
  {
  private:
    BookEdition*& m_polymorphic;

  public:
    BookEditionWrapper(BookEdition*& ptr) : m_polymorphic{ptr} {};
    BookEdition& operator=(BookEdition&& book) { return *m_polymorphic = book; }
    BookEdition& operator=(FictionEdition&& book)
    {
      //
      return *(m_polymorphic = &book);
    }
    BookEdition& operator=(ScientificEdition&& book)
    {
      //
      return *(m_polymorphic = &book);
    }
    BookEdition& operator=(LearningEdition&& book)
    {
      //
      return *(m_polymorphic = &book);
    }
    BookEdition& operator=   (FictionEdition const& book)
    {
      //
      auto tmp = new FictionEdition(book);
      return *(m_polymorphic = tmp);
    }
    BookEdition& operator=(ScientificEdition const& book)
    {
      //
      auto tmp = new ScientificEdition(book);
      return *(m_polymorphic = tmp);
    }
    BookEdition& operator=  (LearningEdition const& book)
    {
      //
      auto tmp = new LearningEdition(book);
      return *(m_polymorphic = tmp);
    }
    operator BookEdition&() { return *m_polymorphic; }
    BookEdition* operator&() {
      return m_polymorphic;
    }
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
  BookEditionWrapper operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
};

#endif // TABLE_HPP
