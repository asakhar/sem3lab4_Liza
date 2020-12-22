#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"

using namespace std::string_literals;

int main(int argc, char const* argv[])
{
  std::string b;
  std::cin >> b;

  BookEdition a{b, ""s, 1l, ""s, 2ul, Learning};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, "New Year"};
  ScientificEdition d{"someauth", "sometitle", -100, "somepbl", 9999};
  d--;
  std::cout << a << c << d;

  d << "cource 1"
    << "cource 2"
    << "cource 3";
  std::cout << d.getCourceTitlesAsString();
  std::vector<std::pair<long, BookEdition*>> vec{{2, &a}, {-3, &c}, {5, &d}};
  Table tab{vec};
  for (auto i : vec)
    std::cout << i.first << " "; //copy check
  tab << Table::KeyVal_t{-5, &d};
  tab << Table::KeyVal_t{1, &c};
  tab << Table::KeyVal_t{6, &a};
  std::cout << *tab[6];
  tab.erase(7); 

  std::cout << std::endl << std::endl << tab;
  return 0;
}
