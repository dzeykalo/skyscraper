
#include "lib.h"
#include "rules.h"

int main(int argc, char* argv[]) 
{
  if (argc < 2)
    { std::cerr << "no input data\n"; exit(-1); }

  std::array<std::array<std::vector<int>,kBuildingHeight>,kBuildingHeight> Array;
  std::map<int, std::vector<int>> Visible;
  InitArray(Array, argv[1], Visible);
  Search(Array);
  SearchSingleSolution(Array, Visible);
  RuleForVisibleFour(Array, Visible);
  RuleForVisibleThree_0(Array, Visible);
  GetElement(Array);
  Search(Array);

  RuleForVisibleTwo_0(Array, Visible);
  Search(Array);
  RuleForVisibleThree_1(Array, Visible);
  RuleForVisibleTwo_1(Array, Visible);
  Search(Array);
  RuleForVisibleThree_2(Array, Visible);
  Search(Array);
  

  for ( auto &m:Array)
  {
    for ( auto &n:m)
    {
      for ( auto &i:n)
        std::cout << i ;
      std::cout << "\t";
    }
    std::cout << std::endl;
  }

  return 0;
}

