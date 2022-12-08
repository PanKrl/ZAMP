#include "LibInterface.hh"


LibInterface::LibInterface(string path) {
	handler = dlopen(path.c_str(), RTLD_LAZY);

	if (!handler) {
		cerr << "!!! Brak biblioteki: " << path << endl;
	}

	void * pFun = dlsym(handler, "CreateCmd");

	if (!pFun)
		cerr << "!!! Nie znaleziono funkcji CreateCmd " << path << endl;

	pCreateCmd = * reinterpret_cast < Interp4Command * ( * )(void) > (pFun);
	Interp4Command * interp_cmd = pCreateCmd();
	_Lib_Name = interp_cmd -> GetCmdName();

	delete interp_cmd;
}

LibInterface::~LibInterface() {
	dlclose(handler);
}
