#include "Scena.hh"

#include <vector>

Scena::Scena() {}

Scena::Scena(map <string, MobileObj*> & List): _Object_List(List) {
  cout << "Utworzono scene z " << _Object_List.size() << " obiektami" << endl;
}

MobileObj * Scena::FindMobileObj(string sName) {
  map <string, MobileObj*> ::iterator Iter = this -> _Object_List.find(sName);

  if (Iter == this -> _Object_List.end()) return nullptr;

  else return Iter -> second;
}

void Scena::AddMobileObj(string sName) {
  MobileObj * pMobObj = new MobileObj;
  this -> _Object_List.insert({
    sName,
    pMobObj
  });
}

vector <MobileObj*> Scena::getObjects() {
  vector <MobileObj*> result;
  map <string, MobileObj*> ::iterator Iter;

  for (Iter = _Object_List.begin(); Iter != _Object_List.end(); Iter++) {
    result.push_back(Iter -> second);
  }

  return result;
}
