#include "Dicionario.h"
#include <iostream>

Dicionario::Dicionario() {
	this->tabela = new TabelaHash<ObjetoDicionario>( 17 );
}

Dicionario::~Dicionario() {
	delete( tabela );
}

bool Dicionario::vazio() {
	return this->tabela->vazio();
}

void Dicionario::inserir( const char *chave, TipoObjeto tipo, void *dado ) {
	this->tabela->inserir( chave, new ObjetoDicionario( tipo, dado ) );
}

void Dicionario::imprimir( const char *chave ) {
	switch( this->tabela->get( chave )->getTipo() ) {

	case INTEGER:
		std::cout << "Tipo: INTEGER" << std::endl;
		break;
	case FLOAT:
		std::cout << "Tipo: FLOAT" << std::endl;
		break;
	default:
		std::cout << "Tipo: STRING" << std::endl;
		break;

	}
	std::cout << "Valor: " << this->tabela->get( chave )->toString() << std::endl;
}

void Dicionario::imprimirChaves() {
	std::cout << "Chaves do Dicionário:\n" << std::endl;
	this->tabela->imprimirChaves();
}
