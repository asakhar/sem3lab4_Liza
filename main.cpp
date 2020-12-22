#include "BookEdition.hpp"
#include "ScientificEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"

using namespace std::string_literals;

int main(int argc, char const *argv[])
{
  std::string b;
  std::cin >> b;
  
  BookEdition a{b, ""s, 1l, ""s, 2ul, Learning};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, "New Year"};
  std::cout << a << c;
  return 0;
}
