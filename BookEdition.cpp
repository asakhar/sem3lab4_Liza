#include "BookEdition.hpp"
#include <cstring>
#ifdef DEBUG
#include <iomanip>
#endif
// #include <memory>
#include <sstream>
using namespace EditionTypes;

std::ostream& operator<<(std::ostream& stream, EditionType type)
{
  return stream << _typestrings[type];
}

BookEdition::BookEdition()
    : m_year{0}, m_numberOfCopies{0}, m_editionType{Undefined}
{
}

BookEdition::BookEdition(std::string const& author, std::string const& title,
                         long year, std::string const& publisher,
                         size_t numberOfCopies)
    : m_year{year}, m_numberOfCopies{numberOfCopies}, m_editionType{Undefined}
{
  m_author    = author;
  m_title     = title;
  m_publisher = publisher;
}
BookEdition::BookEdition(std::string const& author, std::string const& title,
                         long year, std::string const& publisher,
                         size_t numberOfCopies, EditionType etype)
    : m_year{year}, m_numberOfCopies{numberOfCopies}, m_editionType{etype}
{
  m_author    = author;
  m_title     = title;
  m_publisher = publisher;
}

std::ostream& operator<<(std::ostream& stream, BookEdition const& book)
{
  return stream
#ifdef DEBUG
         << std::setw(15)
#endif
         << book.m_author << ";"
#ifdef DEBUG
         << std::setw(15)
#endif

         << book.m_title << ";"
#ifdef DEBUG
         << std::setw(15)
#endif
         << book.m_year << ";"

#ifdef DEBUG
         << std::setw(15)
#endif
         << book.m_publisher << ";"
#ifdef DEBUG
         << std::setw(15)
#endif

         << book.m_numberOfCopies << ";"
#ifdef DEBUG
         << std::setw(15)
#endif

         << book.m_editionType << ';';
}

std::string BookEdition::getAllInfo() const
{
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