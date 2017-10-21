#ifndef DICIONARIO_H_
#define DICIONARIO_H_

#include "TabelaHash.hpp"
#include "ObjetoDicionario.h"

class Dicionario {

private:
	TabelaHash<ObjetoDicionario> *tabela;

public:
	/**
	 * Construtor.
	 */
	Dicionario();

	/**
	 * Destrutor.
	 */
	virtual ~Dicionario();

	/**
	 * @return true se o dicionário está vazio.
	 */
	bool vazio();

	/**
	 * Inserir um elemento.
	 * @param chave A chave correspondente ao elemento.
	 * @param TipoObjeto O tipo do elemento.
	 * @param dado O dado a ser inserido
	 */
	void inserir( const char *chave, TipoObjeto tipo, void *dado );

	/**
	 * Imprimir um elemento a partir da chave.
	 * @param chave A chave correspondente ao elemento.
	 */
	void imprimir( const char *chave );

	/**
	 * Imprimir todas as chaves.
	 */
	void imprimirChaves();

};

#endif
