#ifndef FICTIONEDITION_HPP
#define FICTIONEDITION_HPP
#include "BookEdition.hpp"

class FictionEdition : public BookEdition
{
private:
  EditionType m_editionType = Fiction;
  std::string m_subject;

public:
  FictionEdition(std::string const& author,
                                 std::string const& title, long year,
                                 std::string const& publisher,
                                 size_t numberOfCopies,
                                 std::string const& subject);
  std::string const& getSubject();
};

#endif