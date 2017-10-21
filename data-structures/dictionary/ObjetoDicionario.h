#ifndef OBJETODICIONARIO_H_
#define OBJETODICIONARIO_H_

#include "TipoObjeto.h"
#include <string>

class ObjetoDicionario {

private:
	TipoObjeto tipo;
	void *dado;

public:
	ObjetoDicionario();
	ObjetoDicionario( TipoObjeto tipo, void *dado );
	virtual ~ObjetoDicionario();
	void* getDado();
	TipoObjeto getTipo();
	std::string toString();

};

#endif
