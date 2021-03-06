#include "LearningEdition.hpp"
#include <sstream>

LearningEdition::LearningEdition(std::string const& author,
                                 std::string const& title, long year,
                                 std::string const& publisher,
                                 size_t numberOfCopies,
                                 std::string const& courceTitle,
                                 std::vector<long> groupsIndexes)
    : BookEdition{author, title, year, publisher, numberOfCopies, Learning}
{
  if (groupsIndexes.size() > 8)
    throw std::runtime_error("Too many groups. Expected 8 at most.");
  m_courceTitle    = courceTitle;
  m_numberOfGroups = 0;
  for (auto& groupIndex : groupsIndexes)
    m_groupsIndexes[m_numberOfGroups++] = groupIndex;
}

LearningEdition::LearningEdition(std::string const& author,
                                 std::string const& title, long year,
                                 std::string const& publisher,
                                 size_t numberOfCopies,
                                 std::string const& courceTitle,
                                 long groupsIndexes[], size_t numberOfGroups)
    : BookEdition{author, title, year, publisher, numberOfCopies, Learning}
{
  if (numberOfGroups > 8)
    throw std::runtime_error("Too many groups. Expected 8 at most.");
  m_courceTitle    = courceTitle;
  m_numberOfGroups = numberOfGroups;
  for (auto i = 0ul; i < numberOfGroups; i++)
    m_groupsIndexes[i] = groupsIndexes[i];
}

std::string const& LearningEdition::getCourceTitle() const
{
  return m_courceTitle;
}
std::string const& LearningEdition::setCourceTitle(std::string const& title)
{
  return m_courceTitle = title;
}
long const* LearningEdition::getGroups() const { return m_groupsIndexes; }

size_t LearningEdition::getNumberOfGroups() const { return m_numberOfGroups; }
std::string LearningEdition::getGroupsAsString() const
{
  std::stringstream ss;
  for (auto i = 0ul; i < getNumberOfGroups(); i++)
    ss << m_groupsIndexes[i] << ((i == getNumberOfGroups() - 1) ? "" : ", ");
  return ss.str();
}
long& LearningEdition::operator[](size_t index) noexcept
{
  return m_groupsIndexes[index];
}
long& LearningEdition::at(size_t index)
{
  if (index < getNumberOfGroups())
    return m_groupsIndexes[index];
  throw std::out_of_range("Index was out of range.");
}
void LearningEdition::removeGroup(long groupIndex)
{
  auto flag = 0ul;
  for (auto i = 0ul; i < getNumberOfGroups(); i++)
    if (m_groupsIndexes[i] == groupIndex)
      flag++;
    else
      m_groupsIndexes[i - flag] = m_groupsIndexes[i];
  m_numberOfGroups -= flag;
}
long LearningEdition::erase(size_t index)
{
  auto flag = 0ul;
  if (index >= getNumberOfGroups())
    throw std::out_of_range("Index was out of range.");
  long res;
  for (auto i = 0ul; i < getNumberOfGroups(); i++)
    if (i == index)
    {
      flag++;
      res = m_groupsIndexes[i];
    }
    else
      m_groupsIndexes[i - flag] = m_groupsIndexes[i];
  m_numberOfGroups -= flag;
  return res;
}