#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include <algorithm>
#include <iterator>
#include <tuple>

template <class _Ty>
concept NotPtrDerivedBook =
    !std::is_pointer<_Ty>::value && !std::is_same<std::nullptr_t, _Ty>::value &&
    std::is_base_of<BookEdition, _Ty>::value;

template <size_t __i>
concept NotNull =
    std::is_same<std::true_type, std::integral_constant<bool, __i>>::value;

class Table
{
private:
  struct TableItem
  {
    long code;
    BookEdition* book;
    TableItem* next;
    TableItem();
    TableItem(long acode, BookEdition* abook);

    template <NotPtrDerivedBook _Ty>
    TableItem(long acode, _Ty const& obj) : code{acode}
    {
      book = new _Ty{obj};
    }

    ~TableItem();
  };
  TableItem* m_beforeFirst;
  size_t m_numberOfEditions;

public:
  template <typename _Ty>
  using KeyVal_t = std::pair<long, _Ty*>;
  Table();

private:
  template <NotNull __i, typename... _Args>
  static void copyToVector(std::tuple<KeyVal_t<_Args>...>& books,
                           std::vector<KeyVal_t<BookEdition>>& vec)
  {

    constexpr size_t len =
        std::tuple_size<std::tuple<KeyVal_t<_Args>...>>::value;
    using type =
        typename std::tuple_element<len - __i,
                                    std::tuple<KeyVal_t<_Args>...>>::type;

    auto val               = std::get<len - __i>(books);
    using second_t_pointer = decltype(val.second);
    using second_t = typename std::remove_pointer<second_t_pointer>::type;
    vec[len - __i] = type{val.first, new second_t{*val.second}};
    copyToVector<__i - 1>(books, vec);
  }

  template <size_t __i, typename... _Args>
  static void copyToVector(std::tuple<KeyVal_t<_Args>...>& books,
                           std::vector<KeyVal_t<BookEdition>>& vec)
  {
  }

public:
  template <typename... _Args>
  Table(std::tuple<KeyVal_t<_Args>...> books) : m_numberOfEditions{0}
  {
    constexpr size_t len =
        std::tuple_size<std::tuple<KeyVal_t<_Args>...>>::value;
    std::vector<KeyVal_t<BookEdition>> vector{len};
    copyToVector<len>(books, vector);
    std::sort(vector.begin(), vector.end(),
              [](auto& fir, auto& sec) { return fir.first < sec.first; });
    auto prev = (m_beforeFirst = new Table::TableItem);
    for (auto i = 0ul; i < len; i++)
    {
      auto pair  = vector[i];
      prev->next = new Table::TableItem{pair.first, pair.second};
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
    prev->next       = new TableItem{keyval.first, *keyval.second};
    prev->next->next = tmp;
    m_numberOfEditions++;
    return *this;
  }
  BookEdition*& operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  void save(std::string const& filename) const;
  void open(std::string const& filename);
  class iterator : public std::iterator<std::forward_iterator_tag, TableItem>
  {
    // using reference = BookEdition*&;
    pointer pos_;

  public:
    iterator() : pos_(nullptr) {}
    iterator(pointer v) : pos_(v) {}
    // ~iterator() {}

    iterator operator++(int) /* postfix */
    {
      iterator ret{pos_};
      ++(*this);
      return ret;
    }
    iterator& operator++() /* prefix */
    {
      if (pos_)
        pos_ = pos_->next;
      return *this;
    }
    KeyVal_t<BookEdition> operator*() const
    {
      return KeyVal_t<BookEdition>{pos_->code, pos_->book};
    }
    BookEdition* operator->() const { return pos_->book; }
    bool operator==(const iterator& rhs) const { return pos_ == rhs.pos_; }
    bool operator!=(const iterator& rhs) const { return pos_ != rhs.pos_; }
  };

  iterator begin() const { return m_beforeFirst->next; }

  iterator end() const { return {}; }
};

#endif // TABLE_HPP
