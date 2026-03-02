#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "shuffle.h"
using namespace HKSTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

int main(int argc, char **argv) {
  vector<int> inorder;
  for (int i=0; i<16; ++i)
    inorder.push_back(i);
  Shuffle(inorder);
  for (int i=0; i<16; ++i)
    cout << inorder[i] << " ";
  cout << endl;

  return 0;
}
