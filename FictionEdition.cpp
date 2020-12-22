#include "FictionEdition.hpp"

FictionEdition::FictionEdition(std::string const& author,
                               std::string const& title, long year,
                               std::string const& publisher,
                               size_t numberOfCopies,
                               std::string const& subject)
    : BookEdition{author, title, year, publisher, numberOfCopies, Fiction}
{
  m_subject = subject;
}

std::string const& FictionEdition::getSubject() { return m_subject; }