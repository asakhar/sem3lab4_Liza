#include "FictionEdition.hpp"
#ifdef DEBUG
#include <iomanip>
#endif
#include <sstream>

using namespace EditionTypes;

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

std::string FictionEdition::getAllInfo() const
{
  std::stringstream ss;
  ss << *this
#ifdef DEBUG
     << std::setw(15)
#endif
     << getSubject() << ';';
  return ss.str();
}