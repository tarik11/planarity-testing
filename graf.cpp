#include "graf.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

Graf::Graf(int n, bool usmjeren) :usmjeren(usmjeren) {
  lista_susjedstva.resize(n);
}

void Graf::dodajGranu(int i, int j) {
  lista_susjedstva[i].push_back(j);
  if(!usmjeren)
    lista_susjedstva[j].push_back(i);
  E++;
}

void Graf::IspisiGraf() {
  for(int i=0;i<lista_susjedstva.size();i++) {
    cout<<i<<": ";
    for(auto it = lista_susjedstva[i].begin();it!=lista_susjedstva[i].end();it++)
        cout<<*it<<" ";
    cout<<endl;
  }
}


void ispisiV(vector<int> v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void ispisiM(vector<vector<bool>> m){
    for(int i = 0; i < m.size(); i++){
        cout << "U Regija " << i << " su cvororve ";
        for(int j = 0; j < m[i].size(); j++){
            if(m[i][j]){
                cout << j << " ";
            }
        }
       cout << endl;
    }
    cout << endl;

}

/// https://www.geeksforgeeks.org/detect-cycle-undirected-graph/

bool Graf::isCyclicUtil(int v,bool visited[], int parent, vector<int> &ciklus)
{
    visited[v] = true;
    list<int>::iterator i;

    for (i = lista_susjedstva[v].begin(); i !=
                       lista_susjedstva[v].end(); ++i)
    {

        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v, ciklus))
           {
              ciklus.push_back(*i);
              return true;
           }
        }

        else if (*i != parent) {
            ciklus.push_back(*i);
           return true;
        }
    }
    return false;
}


bool Graf::isCyclic(vector<int>& ciklus)
{
  bool uso = false;
  int n = lista_susjedstva.size();

  bool *visited = new bool[n];
  for (int i = 0; i < n; i++)
    visited[i] = false;

  for (int u = 0; u < n; u++){
        ciklus.clear();
        if (!visited[u])
          if (isCyclicUtil(u, visited, -1, ciklus)){
            return true;
          }
    }
    return false;
}



vector<int> Graf::PutIzmedjuDvaDodana(int zajednicka_regija, int R, int pocetni, int krajnji, vector<vector<bool>>& dodane_grane, vector<vector<bool>>& regije_cvorova, int velicina_puta) {
  int n = lista_susjedstva.size();
  vector<int> udaljenosti(n,-1);
  vector<int> roditelj(n,-1);
  queue<int> red;
  vector<int> put;
  red.push(pocetni);
  udaljenosti[pocetni] = 0;
  roditelj[pocetni] = -2;

  if(lista_susjedstva[pocetni].empty() || lista_susjedstva[krajnji].empty())
    return put;
  if(velicina_puta != 2){
      for(auto it = lista_susjedstva[pocetni].begin();it != lista_susjedstva[pocetni].end();it++){
         if(*it == krajnji){
            put.push_back(pocetni);
            put.push_back(krajnji);
            return put;
         }
      }
  }
  while(!red.empty()) {
    int trenutni = red.front();
    red.pop();
    for(auto it = lista_susjedstva[trenutni].begin();it != lista_susjedstva[trenutni].end();it++){
        if(udaljenosti[*it] == -1
           && dodane_grane[trenutni][*it]
           && BrojZajednickihRegija(R,*it, trenutni,regije_cvorova) == 2
           && regije_cvorova[zajednicka_regija][*it]) {
            red.push(*it);
            udaljenosti[*it] = udaljenosti[trenutni] + 1;
            roditelj[*it] = trenutni;
        }
    }
    if(udaljenosti[krajnji] != -1)
        break;
  }
  int trenutni = krajnji;
  while(roditelj[trenutni] != -2) {
    put.push_back(trenutni);
    trenutni = roditelj[trenutni];
  }
  put.push_back(pocetni);
  reverse(put.begin(), put.end());
  return put;
}

vector<int> Graf::PutIzmedjuDvaKojaNisuDodana(int pocetni, int krajnji, vector<vector<bool>>& dodane_grane) {
  int n = lista_susjedstva.size();
  vector<int> udaljenosti(n,-1);
  vector<int> roditelj(n,-1);
  queue<int> red;
  vector<int> put;
  red.push(pocetni);
  udaljenosti[pocetni] = 0;
  roditelj[pocetni] = -2;

  if(lista_susjedstva[pocetni].empty() || lista_susjedstva[krajnji].empty())
    return put;

  while(!red.empty()) {
    int trenutni = red.front();
    red.pop();
    for(auto it = lista_susjedstva[trenutni].begin();it != lista_susjedstva[trenutni].end();it++){
        if(udaljenosti[*it] == -1 && !dodane_grane[trenutni][*it]) {
            red.push(*it);
            udaljenosti[*it] = udaljenosti[trenutni] + 1;
            roditelj[*it] = trenutni;
        }
    }
    if(udaljenosti[krajnji] != -1)
        break;
  }

  if(udaljenosti[krajnji] == -1){
    return put;
  }
  int trenutni = krajnji;
  while(roditelj[trenutni] != -2) {
    put.push_back(trenutni);
    trenutni = roditelj[trenutni];
  }
  put.push_back(pocetni);
  reverse(put.begin(), put.end());
  return put;
}

int Graf::NadjiZajednickuRegiju(int R, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova){
    for(int i = 0 ; i < R; i++){
        if(regije_cvorova[i][pocetni] && regije_cvorova[i][krajnji])
            return i;
    }
    return -1;
}

bool Graf::JelBlokirano(int regija, int zajednicka_regija, int trenutni, vector<vector<bool>>& regije_cvorova){
    return !regije_cvorova[regija][trenutni] && !regije_cvorova[zajednicka_regija][trenutni];
}

void Graf::ModifikujPostojeciPut(vector<int> put, vector<vector<bool>>& regije_cvorova, int regija, int zajednicka_regija){
    for(int i = 1; i < put.size()-1; i++){
        if(regije_cvorova[zajednicka_regija][put[i]]){
            regije_cvorova[zajednicka_regija][put[i]] = false;
            regije_cvorova[regija][put[i]] = true;
        }
    }
}

void Graf::VratiModifikovanPostojeciPut(vector<int> put, vector<vector<bool>>& regije_cvorova, int regija, int zajednicka_regija){
    for(int i = 1; i < put.size()-1; i++){
        if(regije_cvorova[regija][put[i]]){
            regije_cvorova[zajednicka_regija][put[i]] = true;
            regije_cvorova[regija][put[i]] = false;
        }
    }
}


int Graf::BrojZajednickihRegija(int R, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova){
    int zbir = 0;
    for(int i = 0; i < R; i++){
        if(regije_cvorova[i][pocetni] && regije_cvorova[i][krajnji])
            zbir++;
    }
    return zbir;
}


void Graf::ModifikujDodaneGrane(vector<int>& put, vector<vector<bool>>& dodane_grane, vector<bool>& dodani_cvorovi){
    for(int i = 0; i < put.size()-1; i++){
        int trenutni = put[i];
        int naredni = put[i+1];
        dodane_grane[trenutni][naredni] = true;
        dodane_grane[naredni][trenutni] = true;
        dodani_cvorovi[trenutni] = true;
        dodani_cvorovi[naredni] = true;
  }
}

void Graf::VratiModifikovaneDodaneGrane(vector<int>& put, vector<vector<bool>>& dodane_grane, vector<bool>& dodani_cvorovi){
    for(int i = 0; i < put.size()-1; i++){
        int trenutni = put[i];
        int naredni = put[i+1];
        dodane_grane[trenutni][naredni] = false;
        dodane_grane[naredni][trenutni] = false;
        dodani_cvorovi[trenutni] = false;
        dodani_cvorovi[naredni] = false;
  }
}


bool Graf::DaLiCvorImaObjeRegije(int regija, int zajednicka_regija, int cvor, vector<vector<bool>>& regije_cvorova){
    if(regije_cvorova[regija][cvor] && regije_cvorova[zajednicka_regija][cvor]){
       return true;
    }
    if(!regije_cvorova[regija][cvor] && !regije_cvorova[zajednicka_regija][cvor]){
       return true;
    }
    return false;

}

void Graf::ModifikujRegije(int zajednicka_regija, int regija, vector<vector<bool>>& regije_cvorova, vector<int>& put, vector<int>& ciklus, vector<bool>& dodani_cvorovi){
    for(int i = 0; i < put.size(); i++){
         regije_cvorova[zajednicka_regija][put[i]] = true;
         regije_cvorova[regija][put[i]] = true;
    }
    for(int i = 0; i < put.size(); i++){
        if(!dodani_cvorovi[put[i]]){
            ciklus.push_back(put[i]);
        }
     }
}

void Graf::VratiModifikovanuRegije(int zajednicka_regija, int regija, vector<vector<bool>>& regije_cvorova, vector<int>& put, vector<int>& ciklus, vector<bool>& dodani_cvorovi){
    for(int i = 1; i < put.size() -1; i++){
         regije_cvorova[zajednicka_regija][put[i]] = false;
         regije_cvorova[regija][put[i]] = false;
    }
    for(int i = 0; i < put.size(); i++){
        if(!dodani_cvorovi[put[i]]){
            ciklus.pop_back();
        }
     }
}

int Graf::DaLiImajuZajednickuRegijuTriCvora(int ciklus, int pocetni, int krajnji, vector<vector<bool>>& regije_cvorova){
    for(int i = 0; i < regije_cvorova.size(); i++){
        if(regije_cvorova[i][ciklus] && regije_cvorova[i][pocetni] && regije_cvorova[i][krajnji])
            return i;
    }
    return -1;
}

void PostaviNizove(vector<vector<bool>>& dodane_grane, vector<vector<bool>>& regije_cvorova, vector<bool>& dodani_cvorovi, vector<int>& ciklus, int n, int R){
  for(int i = 0; i < dodane_grane.size(); i++){
    dodane_grane[i].resize(n);
  }
  for(int i = 0; i < regije_cvorova.size(); i++){
    regije_cvorova[i].resize(n);
  }

  for(int i = 0; i < R; i++){
    for(int j = 0; j < n; j++)
        regije_cvorova[i][j] = false;
  }

  for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++)
        dodane_grane[i][j] = false;
  }

  if(ciklus[0] != ciklus[ciklus.size() - 1])
    ciklus.push_back(ciklus[0]);

  for(int i = 0; i < ciklus.size()-1; i++){
    int trenutni = ciklus[i];
    int naredni = ciklus[i+1];
    dodane_grane[trenutni][naredni] = true;
    dodane_grane[naredni][trenutni] = true;
    regije_cvorova[0][trenutni] = true;
    regije_cvorova[1][trenutni] = true;
    regije_cvorova[1][naredni] = true;
    regije_cvorova[1][naredni] = true;

    dodani_cvorovi[trenutni] = true;
    dodani_cvorovi[naredni] = true;
  }

  if(ciklus[0] == ciklus[ciklus.size() - 1])
    ciklus.pop_back();
}



vector<int> Graf::DFSPut(int pocetni, vector<bool>& dodani_cvorovi, vector<vector<bool>>& dodane_grane) {
  int n = lista_susjedstva.size();
  vector<bool> posjecen(n,false);
  vector<int> put;
  bool nadjen = false;
  DFSRekPut(pocetni, pocetni, posjecen, put, dodani_cvorovi, dodane_grane, nadjen);
  return put;
}

void Graf::DFSRekPut(int pocetni, int cvor, vector<bool> &posjecen, vector<int>& put, vector<bool>& dodani_cvorovi, vector<vector<bool>>& dodane_grane, bool& nadjen) {
  posjecen[cvor] = true;
  if(!nadjen)
    put.push_back(cvor);
  for(auto it = lista_susjedstva[cvor].begin(); it!=lista_susjedstva[cvor].end();it++){
    if(nadjen)
        break;
    if(dodane_grane[cvor][*it]){
        continue;
    }
    if(dodani_cvorovi[*it] && *it != pocetni){
        cout << "DOSADASANJI PUT " << endl;
        for(int i = 0; i < put.size();i++)
            cout << put[i];
        cout << endl;
        nadjen = true;
        put.push_back(*it);
        break;
    }
    if(!posjecen[*it] && !nadjen){
      DFSRekPut(pocetni, *it, posjecen, put, dodani_cvorovi, dodane_grane, nadjen);
    }
  }

    if(!nadjen)
        put.pop_back();

}

bool Graf::TestPlanarnosti() {
  int n = lista_susjedstva.size();
  if(E > 3*n - 6)
    return false;

  int R = E - n + 2; /// Broj regija u planarnom grafu
  vector<bool> posjecen(n,false);
  vector<int> ciklus;
  vector<vector<bool>> dodane_grane(n);
  vector<bool> dodani_cvorovi(n, false);
  vector<vector<bool>> regije_cvorova(R);

  if(!isCyclic(ciklus)){
     return true;
  }

  PostaviNizove(dodane_grane, regije_cvorova, dodani_cvorovi, ciklus, n, R);

  int index = 0;
  int regija = 1;
  vector<int> put;
  vector<int> put2;
  vector<pair<int, int>> forsirani;
  vector<pair<int, int>> blokirani;
  int zajednicka_regija = 0;
  int forsirana_regija = -1;

  while(true){
     if(index > ciklus.size() - 1)
        break;
     if(regija > R - 1)
        return false;

     int trenutni = ciklus[index];
     cout << "Cvor koji se obradjuje " << trenutni << endl;

     cout << "DOSADASNJI CIKLUS" << endl;
     ispisiV(ciklus);
     if(!blokirani.empty()){
        //ispis
        vector<int> blokiran_put;
        cout << "Prolazim kroz potencijalin blokirani: " << blokirani[blokirani.size() - 1].first;
        cout << " " << blokirani[blokirani.size() - 1].second << endl;
        auto par = blokirani[blokirani.size()-1];
        blokirani.pop_back();
        blokiran_put = PutIzmedjuDvaKojaNisuDodana(par.first, par.second, dodane_grane);
        forsirana_regija = DaLiImajuZajednickuRegijuTriCvora(par.first, put[0], put[put.size() - 1], regije_cvorova);
        if(blokiran_put.empty()){
            forsirana_regija = -1;
            continue;
        }
        if(!blokiran_put.empty() && forsirana_regija == -1){
             return false;
        }
        if(!blokiran_put.empty()){
            cout << "PUT SE MOZE NAPARVITI KROZ REGIJU " << forsirana_regija << endl;
            VratiModifikovaneDodaneGrane(put, dodane_grane, dodani_cvorovi);
            VratiModifikovanPostojeciPut(put2, regije_cvorova, regija, zajednicka_regija);
            VratiModifikovanuRegije(zajednicka_regija, regija, regije_cvorova, put, ciklus, dodani_cvorovi);
            put2.clear();
            blokirani.clear();
            forsirani.clear();
        }
     }
     else if(!forsirani.empty()){
        //ispis
        cout << "Prolazim kroz potencijalin forsirani: " << forsirani[forsirani.size() - 1].first;
        cout << " " << forsirani[forsirani.size() - 1].second << endl;

        auto par = forsirani[forsirani.size()-1];
        forsirani.pop_back();
        put = PutIzmedjuDvaKojaNisuDodana(par.first, par.second, dodane_grane);
        if(put.empty()){
             continue;
        }
     }
     else
     put = DFSPut(trenutni, dodani_cvorovi, dodane_grane);

     //ispis
     cout << "Novo nadjeni put" << endl;
     ispisiV(put);

     if(put.empty()){
        index++;
        continue;
     }
     if(forsirana_regija == -1){
        regija++;
     // Zajednicka regija
        zajednicka_regija = NadjiZajednickuRegiju(R, put[0], put[put.size() - 1], regije_cvorova);
     }else{
        zajednicka_regija = forsirana_regija;
     }

     // Zaustavi ako je put blokiran
     if(zajednicka_regija == -1){
        return false;
     }

     //ispis
     cout << "STARE REGIJA" << endl;
     ispisiM(regije_cvorova);

     // Modifikujem regije dodam novu
     ModifikujRegije(zajednicka_regija, regija, regije_cvorova, put, ciklus, dodani_cvorovi);

     cout << "NOVO DODANA REGIJA" << endl;
     ispisiM(regije_cvorova);

     //Nalazim put od vec dodanih na ciklusu i pokrivam ga novom regijom ako postoji
     put2 = PutIzmedjuDvaDodana(zajednicka_regija, R, put[0], put[put.size()-1], dodane_grane, regije_cvorova, put.size());
     //ispis
     //ispis
     cout << "ISPISI PUT kojem moramo promjeniti regiju" << endl;
     ispisiV(put2);

     //modifikovanje puta koji mogu biti pokriven
     ModifikujPostojeciPut(put2, regije_cvorova, regija, zajednicka_regija);
     //modifikuj dodane grane i cvorove;
     ModifikujDodaneGrane(put, dodane_grane, dodani_cvorovi);

     //ispis
     cout <<"Regije PUTA 2"<< endl;
     ispisiM(regije_cvorova);

       for(int i = 0; i < ciklus.size(); i++){
            // funkcija  provjerava da li dva cvora imaju obbje regije
           if(!DaLiCvorImaObjeRegije(regija,zajednicka_regija,ciklus[i],regije_cvorova)){
                for(int j = 1; j < put.size()-1; j++){
                    forsirani.push_back({ciklus[i], put[j]});
                }

           }
       }

        if(forsirana_regija == -1){
            for(int i = 0; i < ciklus.size(); i++){
                // funkcija  provjerava da li dva cvora imaju obbje regije
            if(JelBlokirano(regija, zajednicka_regija, ciklus[i], regije_cvorova)){
               for(int j = 1; j < put.size()-1; j++){
                        blokirani.push_back({ciklus[i], put[j]});
                    }
               }
           }
        }
     if(blokirani.empty()){
        forsirana_regija = -1;
        put2.clear();
        put.clear();
     }
  }
  return true;
}


