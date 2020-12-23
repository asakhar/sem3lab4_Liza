#ifndef SCIENTIFICEDITION_HPP
#define SCIENTIFICEDITION_HPP
#include "BookEdition.hpp"
#include <vector>

class ScientificEdition : public BookEdition
{
private:
  EditionTypes::EditionType m_editionType = EditionTypes::Scientific;
  std::string m_courceTitles[3];
  size_t m_numberOfCources;

public:
  ScientificEdition(std::string const& author, std::string const& title,
                    long year, std::string const& publisher,
                    size_t numberOfCopies,
                    std::vector<std::string> const& courceTitles = {});
  ScientificEdition(std::string const& author, std::string const& title,
                    long year, std::string const& publisher,
                    size_t numberOfCopies, std::string const courceTitles[],
                    size_t numberOfCources);
  ScientificEdition(ScientificEdition const& se)
      : BookEdition{se.m_author,         se.m_title,
                    se.m_year,           se.m_publisher,
                    se.m_numberOfCopies, EditionTypes::Scientific}
  {
    for (m_numberOfCources = 0; m_numberOfCources < se.getNumberOfCources();
         m_numberOfCources++)
      m_courceTitles[m_numberOfCources] = se.m_courceTitles[m_numberOfCources];
  }
  size_t getNumberOfCources() const;
  std::string const* getCourceTitles() const;
  std::string getCourceTitlesAsString() const;
  std::string& operator[](size_t index) noexcept;
  std::string& at(size_t index);
  std::string eraseCource(size_t index);
  ScientificEdition& operator<<(std::string const& cource);

  virtual std::string getAllInfo() const;
};

#endif