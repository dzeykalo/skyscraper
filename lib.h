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

bool operator == (const std::vector<int> &v, int value)
{
  auto result = std::find(v.begin(), v.end(), value);
  if (result != v.end())
    return true;
  return false;
}

std::vector<int> GetOptions(int val)
{
  if (val == 1)
    return {kBuildingHeight};
  else if (val == 0)
    return {1,2,3,4,5,6};

  std::vector<int> v;
  int max_options = kBuildingHeight - val + 1;
  for (int i = 1; i <= max_options; ++i)
    v.push_back(i);
  return v;
}

void Options(std::vector<int> &v)
{
  if (!v.empty())
  {
    if(v.size() == 1)
      v = GetOptions(v.back());
    else
      v = GetOptions(std::max(v.front(),v.back()));
  }
  else
    v = {1,2,3,4,5,6};
}

void InitArray(two_array_vector &array, const char* input_data, std::map<int, std::vector<int>> &visible)
{
  int m = 0; int n = 0;
  bool back = false;
  int direction = 1; // 1 - down; 2 - left; 3- up; 4- right;
  for(uint32_t i = 0; i < kInputLength; i+=2)
  {
    array[m][n].push_back(input_data[i]-'0');
    visible[input_data[i]-'0'].push_back((m<<16)+(n<<8)+direction);
    if ((m==0 || m==kBuildingHeight-1) && (n==0 || n==kBuildingHeight-1) && !(m==n && m==0))
    {
        i+=2; direction++; 
        array[m][n].push_back(input_data[i]-'0');
        visible[input_data[i]-'0'].push_back((m<<16)+(n<<8)+direction);
    }
    if (n!=kBuildingHeight-1 && !back) n++;
    else if (m!=kBuildingHeight-1 && !back) m++;
    else if (m==kBuildingHeight-1 && !back) { back = true; n-- ;}
    else if (n!=0) n--;
    else if (m!=0) m--;
  }

  for ( auto &i:array)
  {
    for ( auto &v:i)
      Options(v);
  }
  
}

bool CheckRowColumn(two_array_vector &array, int index, int duplicate_value, bool column)
{
  std::vector<int> v{duplicate_value};
  for(int i = 0; i < kBuildingHeight; ++i)
  {
    int m = index; int n = i;
    if (column) 
      { m = i; n = index; }

    if (array[m][n] == v)
        return true;
  }
  return false;
}

void ReplaceUnique(two_array_vector &array, std::array<int,kBuildingHeight> &repeat_count, int index, bool column, bool &search)
{
  for (int i = 0; i < kBuildingHeight; ++i)
  {
    if (repeat_count[i] == 1)
    {
      for(uint32_t j = 0; j < kBuildingHeight; ++j)
      {
        int m = index; int n = j;
        if (column) 
          { m = j; n = index; }
        if (array[m][n] == i+1 && !CheckRowColumn(array, index, i+1, column))
        {
          array[m][n] = {i+1};
          search = true;
        }
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

void SearchUnique(two_array_vector &array, bool &search)
{
  std::array<int,kBuildingHeight> repeat_count;
  for(uint32_t m = 0; m < kBuildingHeight; ++m)
  {
    RepeatCount(array, repeat_count, m, false);
    ReplaceUnique(array, repeat_count, m, false, search);
  }

  for(uint32_t n = 0; n < kBuildingHeight; ++n)
  {
    RepeatCount(array, repeat_count, n, true);
    ReplaceUnique(array, repeat_count, n, true, search);
  }
}

void RemoveDuplicate(two_array_vector &array, uint32_t m, uint32_t n, int duplicate_value, bool &search)
{
  for(uint32_t i = 0; i < kBuildingHeight; ++i)
  {
    if (array[m][i].size() > 1)
    {
      auto itr = std::remove(array[m][i].begin(), array[m][i].end(), duplicate_value);
      if (itr != array[m][i].end())
      {
        search = true;
        array[m][i].erase(itr, array[m][i].end());
      }
    }
  }
    
  for(uint32_t i = 0; i < kBuildingHeight; ++i)
  {
    if (array[i][n].size() > 1)
    {
      auto itr = std::remove(array[i][n].begin(), array[i][n].end(), duplicate_value);
      if (itr != array[i][n].end()) 
      {
        search = true;
        array[i][n].erase(itr, array[i][n].end());
      }
    }
  }
}

void SearchDuplicate(two_array_vector &array)
{
  bool search = true;
  while (search)
  {
    search = false;
    for(uint32_t m = 0; m < kBuildingHeight; ++m)
    {
      for(uint32_t n = 0; n < kBuildingHeight; ++n)
      {
        if (array[m][n].size() == 1)
        {
          RemoveDuplicate(array, m, n, array[m][n].back(), search);
        }
      }
    }
  }
}

void Search(two_array_vector &array)
{
  bool search = true;
  while (search)
  {
    search = false;
    SearchDuplicate(array);
    SearchUnique(array, search);
  }
}

void GetElement(two_array_vector &array)
{
  char answer;
  std::cout << "Are there any famous skyscrapers in grid (y/n)? "; std::cin >> answer;
  if(answer != 'y')
    return;
  std::cout << "How many elements (1..6)? "; std::cin >> answer;

  int max_elements = answer -'0';
  if(max_elements <= 0 || max_elements > 7)
    return;

  std::string imput;
  std::cout << "Example input (1..6). [1][2]=3 enter as 123" << std::endl;
  for(int i = 0; i < max_elements; ++i)
  {
    std::cout << "Element " << i+1 << ": "; std::cin >> imput;
    array[(imput[0] - '0')-1][(imput[1] - '0')-1] = {imput[2] - '0'};
  }
}