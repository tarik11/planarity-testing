#ifndef GRAF_H
#define GRAF_H

#include <vector>
#include <deque>
#include <list>
#include <utility>
using namespace std;

class Graf {
  vector<list<int>> lista_susjedstva;
  int E = 0;
  bool usmjeren;
  public:
  Graf(int n, bool usmjeren = false);
  void dodajGranu(int i, int j);
  void IspisiGraf();
  /// Funkcije za puteve
  vector<int> PutIzmedjuDvaDodana(int z, int R, int pocetni, int krajnji, vector<vector<bool>>& dodane_grane, vector<vector<bool>>& regije_cvorova, int velicina_puta);
  vector<int> PutIzmedjuDvaKojaNisuDodana(int pocetni, int krajnji, vector<vector<bool>>& dodane_grane);
  vector<int> DFSPut(int pocetni, vector<bool>& dodani_cvorovi, vector<vector<bool>>& dodane_grane);
  void DFSRekPut(int pocetni, int cvor, vector<bool> &posjecen, vector<int>& put, vector<bool>& dodani_cvorovi, vector<vector<bool>>& dodane_grane, bool& nadjen);
  /// Test planarnosti
  bool TestPlanarnosti();
  /// Funkcije za pronalazak ciklusa
  bool isCyclic(vector<int> &ciklus);
  bool isCyclicUtil(int v, bool visited[], int parent, vector<int> &ciklus);

  ///Funkcije za obradu regija
  void ModifikujPostojeciPut(vector<int> put, vector<vector<bool>>& regije_cvorova, int regija, int zajednicka_regija);
  void ModifikujDodaneGrane(vector<int>& put, vector<vector<bool>>& dodane_grane, vector<bool>& dodani_cvorovi);
  void ModifikujRegije(int zajednicka_regija, int regija, vector<vector<bool>>& regije_cvorova, vector<int>& put, vector<int>& ciklus, vector<bool>& dodani_cvorovi);
  bool DaLiCvorImaObjeRegije(int regija, int zajednicka_regija, int cvor, vector<vector<bool>>& regije_cvorova);
  int NadjiZajednickuRegiju(int R, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova);
  int BrojZajednickihRegija(int R, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova);
  bool JelBlokirano(int regija, int zajednicka_regija, int trenutni, vector<vector<bool>>& regije_cvorova);
  ///Dodatno testiranje blokiranih
  int DaLiImajuZajednickuRegijuTriCvora(int ciklus, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova);
  void VratiModifikovanuRegije(int zajednicka_regija, int regija, vector<vector<bool>>& regije_cvorova, vector<int>& put, vector<int>& ciklus, vector<bool>& dodani_cvorovi);
  void VratiModifikovaneDodaneGrane(vector<int>& put, vector<vector<bool>>& dodane_grane, vector<bool>& dodani_cvorovi);
  void VratiModifikovanPostojeciPut(vector<int> put, vector<vector<bool>>& regije_cvorova, int regija, int zajednicka_regija);

};



#endif // GRAF_H
