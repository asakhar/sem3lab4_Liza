#include "BookEdition.hpp"
#include <cstring>
#include <iomanip>
#include <memory>
#include <sstream>

std::ostream& operator<<(std::ostream& stream, EditionType type)
{
  static char const* const _typestrings[] = {"Undefined", "Learning",
                                             "Scientific", "Fiction"};
  return stream << _typestrings[type];
}

BookEdition::BookEdition()
    : m_year{0}, m_numberOfCopies{0}, m_editionType{Undefined}
{
}

BookEdition::BookEdition(std::string const& author, std::string const& title,
                         long year, std::string const& publisher,
                         size_t numberOfCopies, EditionType editionType)
    : m_year{year}, m_numberOfCopies{numberOfCopies}, m_editionType{editionType}
{
  m_author    = author;
  m_title     = title;
  m_publisher = publisher;
}

std::ostream& operator<<(std::ostream& stream, BookEdition const& book)
{
  return stream << std::setw(15) << book.m_author << ";" << std::setw(15)
                << book.m_title << ";" << std::setw(15) << book.m_year << ";"
                << std::setw(15) << book.m_publisher << ";" << std::setw(15)
                << book.m_numberOfCopies << ";" << std::setw(15)
                << book.m_editionType << ';';
}

std::string BookEdition::getAllInfo() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

EditionType BookEdition::getEditionType() const { return m_editionType; };
size_t BookEdition::getNumberOfCopies() const { return m_numberOfCopies; };
size_t BookEdition::setNumberOfCopies(size_t nc)
{
  return m_numberOfCopies = nc;
};
BookEdition& BookEdition::operator++()
{
  m_numberOfCopies++;
  return *this;
}
BookEdition& BookEdition::operator++(int)
{
  m_numberOfCopies++;
  return *this;
}
BookEdition& BookEdition::operator--()
{
  m_numberOfCopies--;
  return *this;
}
BookEdition& BookEdition::operator--(int)
{
  m_numberOfCopies--;
  return *this;
}