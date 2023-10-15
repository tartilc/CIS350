/*
 *Author: Luis E. Ortiz
 *Creation Date: 10/14/2018
 *Modification Date: 10/14/2018
 *Purpose: testing AVLTreeMap class template
*/

//#include <cstdlib>
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <string>

#include "Entry.h"
#include "AVLTreeMap.h"

//using namespace std;

int main() {
  AVLTreeMap< Entry<int,int> > T;

  T.put(12,0);
  T.put(5,1);
  T.put(15,2);
  T.put(3,3);
  T.put(10,4);
  T.put(13,5);
  T.put(17,6);
  T.put(4,7);
  T.put(7,8);
  T.put(11,9);
  T.put(14,10);
  T.put(6,11);
  T.put(8,12);

  T.print();

  T.erase(10);

  T.print();

  T.erase(17);

  T.print();

  T.put(9,13);

  T.print();
  //system("pause");
  return EXIT_SUCCESS;
}

