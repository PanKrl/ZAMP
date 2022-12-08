#include <iostream>
#include <cstdio>
#include <sstream>
#include <map>
#include <string>
#include <iterator>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>


#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Configuration.hh"
#include "Port.hh"
#include "xmlinterp.hh"
#include "klient.hh"

using namespace std;

#define LINE_SIZE 500







int main(){

	  istringstream iStrm; // strumieñ danych wejœciowych komend
	  Configuration config;

	  cout << "Po³¹czenie na porcie: " << PORT << endl;

	  int Socket4Sending;

	  if (false == ReadFile("config/config.xml", config)) {
	    cerr << "!!! B³¹d podczas odczytu config.xml" << endl;
	    return 1;
	  }

	  map <string, MobileObj*> objectsList = config.getObjectList();
	  Set4LibInterfaces * LibraryList = new Set4LibInterfaces(objectsList);

	  if (!OpenConnection(Socket4Sending)) {
	    return 1;
	  } else cout << "Nawi¹zano po³¹czenie z serwerem." << endl;
	  Sender * _Sender = new Sender(Socket4Sending, LibraryList -> getScena());

	  //thread Thread4Sending(Fun_CommunicationThread, &_Sender);
	  LibraryList -> ExecPreprocessor("program.cmd", iStrm);
	  LibraryList -> ReadCommands(iStrm, Socket4Sending);

	  //close(Socket4Sending, _Sender, move(Thread4Sending));

	  return 0;

}




