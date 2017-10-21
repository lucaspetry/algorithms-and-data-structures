#ifndef MENU_H_
#define MENU_H_

#include "Dicionario.h"

class Menu {

private:
	Dicionario *dicionario;

public:
	Menu();
	virtual ~Menu();
	void executar();

private:
	void inserirObjeto();
	void imprimirObjeto();
	void imprimirChaves();

};

#endif
