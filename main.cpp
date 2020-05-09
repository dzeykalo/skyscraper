
#include "lib.h"
#include "rules.h"

int main(int argc, char* argv[]) 
{
  if (argc < 2)
    { std::cerr << "no input data\n"; exit(-1); }

  std::array<std::array<std::vector<int>,kBuildingHeight>,kBuildingHeight> Array;
  std::map<int, std::vector<int>> Visible;
  InitArray(Array, argv[1], Visible);
  // SearchUnique(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);
  // SearchSingleSolution(Array);
  // SearchUnique(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);
  // CheckTwo(Array);
  // SearchUnique(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);
  // CheckThree(Array);
  // CheckSix(Array, Visible);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);

  // CheckFour(Array);
  // SearchDuplicate(Array);
  // CheckFifth(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);
  // SearchDuplicate(Array);


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

