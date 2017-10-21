#include "ObjetoDicionario.h"
#include <sstream>

ObjetoDicionario::ObjetoDicionario() {
	this->tipo = INTEGER;
	this->dado = 0;
}

ObjetoDicionario::ObjetoDicionario( TipoObjeto tipo, void *dado ) {
	this->tipo = tipo;
	this->dado = dado;
}

ObjetoDicionario::~ObjetoDicionario() {
	if( this->dado != 0 )
		delete( dado );
}

void* ObjetoDicionario::getDado() {
	return this->dado;
}

TipoObjeto ObjetoDicionario::getTipo() {
	return this->tipo;
}

std::string ObjetoDicionario::toString() {
	std::ostringstream stream;
	switch( this->getTipo() ) {

	case INTEGER:
		stream << *(int*)this->dado;
		return stream.str();

	case FLOAT:
		stream << *(float*)this->dado;
		return stream.str();

	case STRING:
		return *(std::string*)this->dado;

	default:
		return "";

	}
}
