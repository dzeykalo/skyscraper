#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <map>

const int kBuildingHeight = 6;
const int kInputDataLength = 24;
const int kInputCommaLength = 23;
const int kInputLength = kInputDataLength + kInputCommaLength;

using two_array_vector = std::array<std::array<std::vector<int>,kBuildingHeight>,kBuildingHeight>;

bool operator == (const std::vector<int> &v1, const std::vector<int> &v2)
{
  if (v1.size() != v2.size())
    return false;
  return std::equal(v1.begin(), v1.end(), v2.begin());
}

std::vector<int> GetOptions(int val)
{
  std::cout << "val = " << val << std::endl;
  if (val == 1)
    return {kBuildingHeight};

  std::vector<int> v;
  int tmp = kBuildingHeight - val + 1;
  for (int i = 1; i <= tmp; ++i)
    v.push_back(i);
  return v;
}

std::vector<int> GetUnique(std::vector<int> v, int val)
{
  auto tmp = GetOptions(val);
  std::vector<int> ret;
  std::set_intersection(v.begin(), v.end(), tmp.begin(), tmp.end(), std::back_inserter(ret));
  return ret;
}

void InitArray(two_array_vector &array, const char* input_data, std::map<int, std::vector<int>> &visible)
{
  for ( auto &i:array)
    i.fill({1,2,3,4,5,6});

  int m = 0; int n = 1;
  bool back = false;
  int direction = 1; // 1 - down; 2 - left; 3- up; 4- right;
  for(uint32_t i = 2; i < kInputLength; i+=2)
  {
    array[m][n] = GetOptions(input_data[i]-'0');
    visible[input_data[i]-'0'].push_back((m<<16)+(n<<8)+direction);
    if ((m==0 || m==kBuildingHeight-1) && (n==0 || n==kBuildingHeight-1))
    {
      i+=2; direction++;
      array[m][n] = GetUnique(array[m][n], input_data[i]-'0');
      visible[input_data[i]-'0'].push_back((m<<16)+(n<<8)+direction);
    }
    if (n!=kBuildingHeight-1 && !back) n++;
    else if (m!=kBuildingHeight-1 && !back) m++;
    else if (m==kBuildingHeight-1 && !back) { back = true; n-- ;}
    else if (n!=0) n--;
    else if (m!=0) m--;
  }
  std::cout << array[0][0].back() << std::endl;
  // array[0][0] = GetUnique(array[0][0], input_data[0]-'0');
  // visible[input_data[0]-'0'].push_back(1);
}

bool CheckRowColumn(two_array_vector &array, int m, int n, int duplicate_value)
{
  for(int i = 0; i < kBuildingHeight; ++i)
  {
    if (i != n)
    {
      auto result = std::find(array[m][i].begin(), array[m][i].end(), duplicate_value);
      if (result != array[m][i].end())
        return true;
    }
  }
  for(int i = 0; i < kBuildingHeight; ++i)
  {
    if (i != m)
    {
      auto result = std::find(array[i][n].begin(), array[i][n].end(), duplicate_value);
      if (result != array[i][n].end())
        return true;
    }
  }
  return false;
}

void ReplaceUnique(two_array_vector &array, std::array<int,kBuildingHeight> &repeat_count, uint32_t index, bool column)
{
  for (int i = 0; i < kBuildingHeight; ++i)
  {
    if (repeat_count[i] == 1)
    {
      for(uint32_t j = 0; j < kBuildingHeight; ++j)
      {
        uint32_t m = index; uint32_t n = j;
        if (column) 
          { m = j; n = index; }
        auto result = std::find(array[m][n].begin(), array[m][n].end(), i+1);
        if (result != array[m][n].end() && !CheckRowColumn(array, m, n, i+1))
          array[m][n] = {i+1};
      }
    }
  }
}

void RepeatCount(two_array_vector &array, std::array<int,kBuildingHeight> &repeat_count, uint32_t index, bool column)
{
  repeat_count.fill(0);
  for(uint32_t j = 0; j < kBuildingHeight; ++j)
  {
    uint32_t m = index; uint32_t n = j;
    if (column)
      { m = j; n = index; }
    if (array[m][n].size() > 1)
    {
      for(auto i : array[m][n])
        repeat_count[i-1] += 1;
    }
  }
}

void SearchUnique(two_array_vector &array)
{
  std::array<int,kBuildingHeight> repeat_count;
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    RepeatCount(array, repeat_count, m, false);
    ReplaceUnique(array, repeat_count, m, false);
  }

  for(uint32_t n = 0; n < kBuildingHeight; ++n)
  {
    RepeatCount(array, repeat_count, n, true);
    ReplaceUnique(array, repeat_count, n, true);
  }
}

void RemoveDuplicate(two_array_vector &array, uint32_t m, uint32_t n, int duplicate_value)
{
  for(uint32_t i = 0; i < kBuildingHeight; ++i)
  {
    if (array[m][i].size() > 1)
      array[m][i].erase(std::remove(array[m][i].begin(), array[m][i].end(), duplicate_value), array[m][i].end());
  }
    
  for(uint32_t i = 0; i < kBuildingHeight; ++i)
  {
    if (array[i][n].size() > 1)
      array[i][n].erase(std::remove(array[i][n].begin(), array[i][n].end(), duplicate_value), array[i][n].end()); 
  }
}

void SearchDuplicate(two_array_vector &array)
{
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    for(uint32_t n = 0; n < kBuildingHeight; ++n)
    {
      if (array[m][n].size() == 1)
      {
        RemoveDuplicate(array, m, n, array[m][n].back());
      }
    }
  }
}

void SearchSingleSolution(two_array_vector &array)
{
  std::vector<int> v1{1};
  std::vector<int> v2{kBuildingHeight};
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    if (array[m][0] == v1 && array[m][kBuildingHeight-1] == v2)
    {
      for(int n = 1; n < kBuildingHeight-1; ++n)
        array[m][n] = {n+1};
    }
    else if (array[m][0] == v2 && array[m][kBuildingHeight-1] == v1)
    {
      for(int n = kBuildingHeight-2; n > 0; --n)
        array[m][n] = {kBuildingHeight-n};
    }
  }
  for(uint32_t n = 0; n < kBuildingHeight; ++n)
  {
    if (array[0][n] == v1 && array[kBuildingHeight-1][n] == v2)
    {
      for(int m = 1; m < kBuildingHeight-1; ++m)
        array[m][n] = {m+1};
    }
    else if (array[0][n] == v2 && array[kBuildingHeight-1][n] == v1)
    {
      for(int m = kBuildingHeight-2; m > 0; --m)
        array[m][n] = {kBuildingHeight-m};
    }
  }
}


