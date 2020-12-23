#ifndef FICTIONEDITION_HPP
#define FICTIONEDITION_HPP
#include "BookEdition.hpp"

class FictionEdition : public BookEdition
{
private:
  EditionTypes::EditionType m_editionType = EditionTypes::Fiction;
  std::string m_subject;

public:
  FictionEdition(std::string const& author, std::string const& title, long year,
                 std::string const& publisher, size_t numberOfCopies,
                 std::string const& subject);
  // FictionEdition(FictionEdition const& fe)
  //     : BookEdition{fe.m_author, fe.m_title, fe.m_year, fe.m_publisher,
  //                   fe.m_numberOfCopies, EditionTypes::Fiction}
  // {
  //   m_subject = fe.m_subject;
  // }
  std::string const& getSubject() const;
  virtual std::string getAllInfo() const;
};

#endif