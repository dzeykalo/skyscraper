#include "lib.h"

std::vector<int>& GetElementFromDirection(two_array_vector &array, int m, int n, int direction, int pos)
{
  // direction -> 1 - down; 2 - left; 3- up; 4- right;
  // array[][][pos][][][]

  switch (direction)
  {
  case 1:
    return array[pos][n];
    break;
  case 2:
    return array[m][kBuildingHeight-1-pos];
    break;
  case 3:
    return array[kBuildingHeight-1-pos][n];
    break;
  case 4:
    return array[m][pos];
    break;
  default:
    return array[m][n];
    break;
  }
}

void SearchSingleSolution(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  try
  {
    auto& v = visible.at(kBuildingHeight);
    for(auto &i:v)
    {
      int direction = i & 0xff;
      int m = (i >> 16) & 0xff;
      int n = (i >> 8) & 0xff;
      for(int i = 0; i < kBuildingHeight; ++i)
      {
        GetElementFromDirection(array, m, n, direction, i) = {i+1};
      }
    }
  }
  catch(...)
  {
    return;
  }
}

void RuleForVisibleTwo_0(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // If last element is 6, the first is 5.
  std::vector<int> v1{kBuildingHeight};
  for(auto &i:visible[2])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    if (GetElementFromDirection(array, m, n, direction, 5) == v1)
      array[m][n] = {5};             
  }
}

void RuleForVisibleTwo_1(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // Perform last. If there are 6, the first element is highest.
  std::vector<int> v1{kBuildingHeight};
  for(auto &i:visible[2])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    if (array[m][n].size() > 1)
    {
      for (int i = 2; i < kBuildingHeight; ++i)
      {
        auto& element = GetElementFromDirection(array, m, n, direction, i);
        if (element == v1)
          array[m][n] = {array[m][n].back()};
      }
    }
  }
}

void RuleForVisibleThree_0(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // The first two positions can't be 6
  // The first one can't be 5.
  for(auto &i:visible[3])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    for (int j = 0; j < 2; ++j)
    {
      auto& element = GetElementFromDirection(array, m, n, direction, j);
      std::vector<int>::iterator itr;
      if (j==0)
        itr = std::remove_if(element.begin(), element.end(), [](int i){return (i==5 || i==6);});
      else
        itr = std::remove(element.begin(), element.end(), 6);

      element.erase(itr, element.end());
    }
  }
}

void RuleForVisibleThree_1(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // If sequence 5 and 6, the first element is 4
  std::vector<int> v1{5};
  std::vector<int> v2{kBuildingHeight};
  for(auto &i:visible[3])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    auto& last = GetElementFromDirection(array, m, n, direction, 5);
    auto& penult = GetElementFromDirection(array, m, n, direction, 4);
    if (penult == v1 && last == v2)
      array[m][n] = {4};
  }
}

void RuleForVisibleThree_2(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // Perform last. If sequence 5 and 6, the first element is highest value
  std::vector<int> v1{5};
  std::vector<int> v2{kBuildingHeight};
  for(auto &i:visible[3])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    bool five = false;
    bool six  = false;
    for (int j = 2; j < kBuildingHeight; ++j)
    {
      auto& element = GetElementFromDirection(array, m, n, direction, j);
      if (element == v1)
        five = true;
      else if (five && element == v2)
        six  = true;
    }
    if (five && six)
      array[m][n] = {array[m][n].back()};
  }
}

void RuleForVisibleFour(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  // The first three positions can't be 6
  // The first two positions can't be 5
  // The first position can't be 4
  for(auto &i:visible[4])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    for (int j = 0; j < 3; ++j)
    {
      auto& element = GetElementFromDirection(array, m, n, direction, j);
      std::vector<int>::iterator itr;
      if (j==0)
        itr = std::remove_if(element.begin(), element.end(), [](int i){return (i==4 || i==5 || i==6);});
      else if (j==1)
        itr = std::remove_if(element.begin(), element.end(), [](int i){return (i==5 || i==6);});
      else
        itr = std::remove(element.begin(), element.end(), 6);
        
      element.erase(itr, element.end());
    }          
  }
}
