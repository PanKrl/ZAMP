#include "Set4LibInterfaces.hh"
#include <iostream>
#include <vector>



using namespace std;


Set4LibInterfaces::Set4LibInterfaces(map < string, MobileObj * > & _Object_List) {
  this -> scena = new Scena(_Object_List);
  LoadLibrary("libs/libInterp4Move.so");
  LoadLibrary("libs/libInterp4Set.so");
  LoadLibrary("libs/libInterp4Rotate.so");
  LoadLibrary("libs/libInterp4Pause.so");
}

Set4LibInterfaces::~Set4LibInterfaces() {
  _Lib_List.clear();
  if (nullptr != scena)
    delete scena;
}

void Set4LibInterfaces::LoadLibrary(string path) {
  LibInterface * pLibrary = new LibInterface(path);
  _Lib_List.insert({
    pLibrary -> _Lib_Name,
    pLibrary
  });
}

bool Set4LibInterfaces::ExecPreprocessor(const char * NazwaPliku, istringstream & IStrm4Cmds) {
  string Cmd4Preproc = "cpp -P ";
  char Line[500];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE * pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
    return false;

  while (fgets(Line, 500, pProc)) {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

bool Set4LibInterfaces::ReadCommands(istringstream & iStrm, int socket) {
  string _Com_Name, _Obj_Name;
  bool flag;
  string message = "Clear\n";

  vector < MobileObj * > _objectsList = this -> getScena() -> getObjects();


  for (MobileObj * _objectPtr: _objectsList) {
    message += "AddObj " + _objectPtr -> returnParameters();
  }
  const char * sConfigCmds = message.c_str();
  Send(socket, sConfigCmds);

  while (iStrm >> _Com_Name)
  {
    vector < thread * > _THREAD_list;

    while (_Com_Name != "End_Parallel_Actions") {

      if (_Com_Name != "Pause" && _Com_Name != "Begin_Parallel_Actions")
        iStrm >> _Obj_Name;
      flag = true;
      map < string, LibInterface * > ::iterator Iter = this -> _Lib_List.find(_Com_Name);
      if (Iter == this -> _Lib_List.end()) {
        if (_Com_Name != "Begin_Parallel_Actions")
          cerr << "Komenda " << _Com_Name << " nie zosta³a odnaleziona" << endl;

        flag = false;
      }

      // Tworzy komendê na podstawie funkcji wtyczki

      if (flag) {
        Interp4Command * pCommand = Iter -> second -> pCreateCmd();
        if (!pCommand -> ReadParams(iStrm)) {
          cerr << "!!! Nieporawne parametry dla komendy '" << _Com_Name << endl;
          delete pCommand;
          return false;
        }
        MobileObj * _Obj = this -> scena -> FindMobileObj(_Obj_Name);
        if (_Obj == nullptr) {
          cerr << "!!! Obiekt " << _Obj_Name << " nie istnieje" << endl;
          delete pCommand;
          return false;
        } else {

          pCommand -> PrintCmd();
          thread * new_thread = new thread( & Interp4Command::ExecCmd, pCommand, _Obj, this -> scena);
          _THREAD_list.push_back(new_thread);
        }
      }

      iStrm >> _Com_Name;
    }
    for (thread * thread_object: _THREAD_list) // czekaj na zakoñczenie wszystkich zadañ
    {
      thread_object -> join();
      delete thread_object;
    }
  }
  return true;
}
