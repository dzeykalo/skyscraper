#include "lib.h"

void CheckTwo(two_array_vector &array)
{
  std::vector<int> v1{1,2,3,4};
  std::vector<int> v2{kBuildingHeight};
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    if (array[m][0] == v1 && array[m][1] == v2)
    {
      array[m][0] = {1};
    }
    else if (array[m][5] == v1 && array[m][4] == v2)
    {
      array[m][5] = {1};
    }
  }
  
}

void CheckThree(two_array_vector &array)
{
  std::vector<int> v1{1,3};
  std::vector<int> v2{kBuildingHeight};
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    if (array[m][0] == v1 && array[m][3] == v2)
    {
      array[m][0] = {3};
    }
    else if (array[m][3] == v1 && array[m][0] == v2)
    {
      array[m][3] = {3};
    }
  }
  for(uint32_t n = 0; n < kBuildingHeight; ++n)
  {
    if (array[0][n] == v1 && array[3][n] == v2)
    {
      array[0][n] = {3};
    }
    else if (array[3][n] == v1 && array[0][n] == v2)
    {
      array[3][n] = {3};
    }
  }
  
}

void CheckFour(two_array_vector &array)
{
  std::vector<int> v1{1,2};
  std::vector<int> v2{4};
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    
    if (array[m][0] == v1 && array[m][2] == v2)
    {
      array[m][0] = {1};
      array[m][1] = {2};
    }
    else if (array[m][3] == v1 && array[m][1] == v2)
    {
      array[m][3] = {1};
      array[m][2] = {2};
    }
  }
  
}

void CheckFifth(two_array_vector &array)
{
  std::vector<int> v1{1,2,3};
  std::vector<int> v2{4};
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  { 
    if (array[m][0] == v1 && array[m][3] == v2)
    {
      array[m][0] = {3};
    }
    else if (array[m][3] == v1 && array[m][0] == v2)
    {
      array[m][3] = {3};
    }
  }
  for(uint32_t n = 0; n < kBuildingHeight; ++n)
  {
    if (array[0][n] == v1 && array[3][n] == v2)
    {
      array[0][n] = {3};
    }
    else if (array[3][n] == v1 && array[0][n] == v2)
    {
      array[3][n] = {3};
    }
  }
}

void CheckSix(two_array_vector &array, std::map<int, std::vector<int>> &visible)
{
  std::vector<int> v1{kBuildingHeight};
  for(auto &i:visible[2])
  {
    int direction = i & 0xff;
    int m = (i >> 16) & 0xff;
    int n = (i >> 8) & 0xff;
    switch (direction)
    {
    case 1:
      if (array[kBuildingHeight-1][n] == v1)
        array[m][n] = {5};
      break;
    case 2:
      if (array[m][0] == v1)
        array[m][n] = {5};
      break;
    case 3:
      if (array[0][n] == v1)
        array[m][n] = {5};
      break;
    case 4:
      if (array[m][kBuildingHeight-1] == v1)
        array[m][n] = {5};
      break;
    }            
  }
  
}