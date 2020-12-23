#include "FictionEdition.hpp"
#include <sstream>
#include <iomanip>

FictionEdition::FictionEdition(std::string const& author,
                               std::string const& title, long year,
                               std::string const& publisher,
                               size_t numberOfCopies,
                               std::string const& subject)
    : BookEdition{author, title, year, publisher, numberOfCopies, Fiction}
{
  m_subject = subject;
}

std::string const& FictionEdition::getSubject() const { return m_subject; }

std::string FictionEdition::getAllInfo() const {
  std::stringstream ss;
  ss << *this << std::setw(15) << getSubject() << ';';
  return ss.str();
}