#ifndef LEARNINGEDITION_HPP
#define LEARNINGEDITION_HPP
#include "BookEdition.hpp"
#include <vector>

class LearningEdition : public BookEdition
{
private:
  EditionTypes::EditionType m_editionType = EditionTypes::Learning;
  std::string m_courceTitle;
  long m_groupsIndexes[8];
  size_t m_numberOfGroups;

public:
  LearningEdition(std::string const& author, std::string const& title,
                  long year, std::string const& publisher,
                  size_t numberOfCopies, std::string const& courceTitle,
                  std::vector<long> groupsIndexes = {});
  LearningEdition(std::string const& author, std::string const& title,
                  long year, std::string const& publisher,
                  size_t numberOfCopies, std::string const& courceTitle,
                  long groupsIndexes[], size_t numberOfGroups);
  LearningEdition(LearningEdition const& le)
      : BookEdition{le.m_author, le.m_title, le.m_year, le.m_publisher,
                    le.m_numberOfCopies, EditionTypes::Learning}
  {
    m_courceTitle = le.m_courceTitle;
    for(m_numberOfGroups = 0; m_numberOfGroups < le.getNumberOfGroups(); m_numberOfGroups++)
      m_groupsIndexes[m_numberOfGroups] = le.m_groupsIndexes[m_numberOfGroups];
  }
  std::string const& getCourceTitle() const;
  std::string const& setCourceTitle(std::string const& title);
  long const* getGroups() const;
  size_t getNumberOfGroups() const;
  std::string getGroupsAsString() const;
  long& operator[](size_t index) noexcept;
  long& at(size_t index);
  void removeGroup(long groupIndex);
  long erase(size_t index);
  virtual std::string getAllInfo() const;
};

#endif