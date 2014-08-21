#include <iostream>
#include "binaryheap.h"

using namespace std;

using ::can::common::Compare;
using ::can::common::BinaryHeap;

typedef Compare<int> cmp;

typedef BinaryHeap<int, cmp> MyHeap;


int main()
{
  int array[] = {16, 4, 10, 14, 7, 9, 3, 2, 68, 1};
  //int array[] = {16, 14, 10, 4, 7, 9, 3, 2, 8, 1};
  MyHeap mh(10);

  //mh.Build();

  for(size_t i = 0; i < 10; ++i)
  {
    mh.Insert(array[i]);
  }

  for(size_t i = 0; i < 10; ++i)
  {
    cout << mh.at(i) << endl;
  }

  //mh.ReplaceToExtreme(7, 5);
  mh.ReplaceFarFromExtreme(2, 6);
  cout << "---------------------" << endl;
  for(size_t i = 0; i < 10; ++i)
  {
    cout << mh.at(i) << endl;
  }

  while(mh.size())
  {
    cout << "Extreme: " << mh.Extreme() << endl;
    mh.Remove(0);
  }
  return 0;
}



