/*
 *Author: Luis E. Ortiz
 *Creation Date: 10/09/2018
 *Modification Date: 10/14/2018
 *Purpose: testing AVLTreeMap class template
*/

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <string>

#include "Entry.h"
#include "AVLTreeMap.h"

using namespace std;

int main() {
  AVLTreeMap< Entry<int,int> > T;

  T.put(44,0);
  T.put(17,1);
  T.put(78,2);
  T.put(32,3);
  T.put(50,4);
  T.put(88,5);
  T.put(48,6);
  T.put(62,7);

  T.print();

  T.put(54,8);

  T.print();

  T.erase(32);

  T.print();
  
  //system("pause");
  return EXIT_SUCCESS;
}

