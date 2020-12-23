#ifndef BOOKEDITION_HPP
#define BOOKEDITION_HPP
#include <iostream>
#include <string>

namespace EditionTypes
{
enum EditionType
{
  Undefined,
  Learning,
  Scientific,
  Fiction
};
static char const* const _typestrings[] = {"Undefined", "Learning",
                                           "Scientific", "Fiction"};
} // namespace EditionTypes
class BookEdition
{
protected:
  std::string m_author;
  std::string m_title;
  long m_year;
  std::string m_publisher;
  size_t m_numberOfCopies;
  EditionTypes::EditionType m_editionType;
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies,
              EditionTypes::EditionType editionType);

public:
  BookEdition();
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies);
  friend std::ostream& operator<<(std::ostream&, BookEdition const&);
  virtual std::string getAllInfo() const;
  EditionTypes::EditionType getEditionType() const;
  size_t getNumberOfCopies() const;
  size_t setNumberOfCopies(size_t nc);
  BookEdition& operator++();
  BookEdition& operator++(int);
  BookEdition& operator--();
  BookEdition& operator--(int);
};
#endif