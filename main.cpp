#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include <fstream>

using namespace std::string_literals;

int main(int argc, char const* argv[])
{
  std::string b = "sdfg";
  // std::cin >> b;

  BookEdition a{b, ""s, 1l, ""s, 2ul, Learning};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, "New Year"};
  ScientificEdition d{"someauth", "sometitle", -100, "somepbl", 9999};
  d--;
  std::cout << a << '\n' << c << '\n' << d << "\n\n";

  d << "cource 1"
    << "cource 2"
    << "cource 3";
  // std::cout << d.getCourceTitlesAsString();
  std::vector<std::pair<long, BookEdition*>> vec{{2, &a}, {-3, &c}, {5, &d}};
  Table tab{vec};
  for (auto i : vec)
    std::cout << i.first << " "; // copy check
  std::cout << "\n\n\n";
  tab << Table::KeyVal_t<ScientificEdition>{-5, &d};
  tab << Table::KeyVal_t<FictionEdition>{1, &c};
  tab << Table::KeyVal_t<BookEdition>{6, &a};
  // std::cout << *tab[6];
  // std::cout << ((ScientificEdition*)(tab[-5]))->getCourceTitlesAsString();
  // tab.erase(7);

  // std::cout << std::endl << std::endl << tab;
  tab.save("1234.csv");
  // std::ofstream file("123.csv");
  // std::vector<long> keys{-5, -3, 1, 2, 5, 6};
  // for (auto& i : keys)
  //   file << tab[i]->getAllInfo() << '\n';
  // file.close();
  return 0;
}
