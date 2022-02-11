#include <iostream>
#include "graf.h"

using namespace std;

int main() {

  // K 5
  /*
  Graf G5(5);
  G5.dodajGranu(0,1);
  G5.dodajGranu(0,2);
  G5.dodajGranu(0,3);
  G5.dodajGranu(0,4);
  G5.dodajGranu(1,2);
  G5.dodajGranu(1,3);
  G5.dodajGranu(1,4);
  G5.dodajGranu(2,3);
  G5.dodajGranu(2,4);
  G5.dodajGranu(3,4);

  cout << G5.TestPlanarnosti();
  */

  //K 3, 3
  /*
  Graf G3(6);

  G3.dodajGranu(0, 3);
  G3.dodajGranu(0, 4);
  G3.dodajGranu(0, 5);
  G3.dodajGranu(1, 3);
  G3.dodajGranu(1, 4);
  G3.dodajGranu(1, 5);
  G3.dodajGranu(2, 3);
  G3.dodajGranu(2, 4);
  G3.dodajGranu(2, 5);

  cout << G3.TestPlanarnosti();
  */

  /*
 Graf G4(7);
  G4.dodajGranu(0,1);
  G4.dodajGranu(1,2);
  G4.dodajGranu(2,3);
  G4.dodajGranu(3,4);
  G4.dodajGranu(4,5);
  G4.dodajGranu(5,6);

  cout << G4.TestPlanarnosti();

   */



  Graf G(8);
  G.dodajGranu(0,1);
  G.dodajGranu(0,2);
  G.dodajGranu(1,2);
  G.dodajGranu(2,3);
  G.dodajGranu(3,0);
  G.dodajGranu(3,4);
  G.dodajGranu(4,1);
  G.dodajGranu(1,7);
  G.dodajGranu(7,5);
  // G.dodajGranu(5,2);
  // G.dodajGranu(5,1);
  G.dodajGranu(2,7);
  G.dodajGranu(5,6);
  G.dodajGranu(6,3);
  G.dodajGranu(6,0);
  G.dodajGranu(6,1);

  cout << G.TestPlanarnosti();




}
