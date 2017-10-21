#ifndef TABELAHASH_HPP_
#define TABELAHASH_HPP_

#define ERRODADOINEXISTENTE -1
#define ERROMEMORIAINSUFICIENTE -2
#define ERROCHAVEDUPLICADA -3
#define ERROCHAVEINVALIDA -4

#include "LinhaHash.hpp"
#include <string.h>

using namespace std;

template <typename Tipo>
class TabelaHash {

private:
	LinhaHash<Tipo> **tabela;
	int altura;
	int numElementos;

public:
	TabelaHash() {
		this->altura = 10;
		this->tabela = new LinhaHash<Tipo>*[10];
		this->numElementos = 0;
		this->inicilizarTabela();
	}

	TabelaHash( int altura ) {
		this->altura = altura;
		this->tabela = new LinhaHash<Tipo>*[altura];
		this->numElementos = 0;
		this->inicilizarTabela();
	}

	virtual ~TabelaHash() {
		delete( tabela );
	}

	void inicilizarTabela() {
		for( int i = 0; i < this->altura; i++ )
			tabela[i] = new LinhaHash<Tipo>();
	}

	bool vazio() {
		return numElementos == 0;
	}

	void inserir( const char *chave, Tipo *dado ) {
		if( *chave == 0 )
			throw ERROCHAVEINVALIDA;

		AssociacaoHash<Tipo> *obj = new AssociacaoHash<Tipo>( chave, dado );

		if( obj == 0 )
			throw ERROMEMORIAINSUFICIENTE;

		int indiceLinha = this->hash( chave );
		AssociacaoHash<Tipo> *linha = this->tabela[indiceLinha]->getInicio();

		if( linha != 0 ) {
			while( strcmp( linha->getChave(), chave ) != 0 && linha->getProximo() != 0 )
				linha = linha->getProximo();

			if( strcmp( linha->getChave(), chave ) == 0 )
				throw ERROCHAVEDUPLICADA;

			linha->setProximo( obj );
		} else {
			this->tabela[indiceLinha]->setInicio( obj );
		}
		this->tabela[indiceLinha]->increaseNumElementos();
		this->numElementos++;
	}

	Tipo* remover( const char *chave ) {
		if( *chave == 0 )
			throw ERROCHAVEINVALIDA;

		int indiceLinha = this->hash( chave );
		AssociacaoHash<Tipo> *anterior = 0;
		AssociacaoHash<Tipo> *obj = this->tabela[indiceLinha]->getInicio();

		while( obj != 0 && strcmp( obj->getChave(), chave ) != 0 ) {
			anterior = obj;
			obj = obj->getProximo();
		}

		if( obj == 0 )
			throw ERRODADOINEXISTENTE;

		if( anterior != 0 )
			anterior->setProximo( obj->getProximo() );
		else
			this->tabela[indiceLinha]->setInicio( 0 );

		Tipo *dado = obj->getDado();
		obj->setProximo(0);
		obj->setDado(0);
		delete(obj);
		this->tabela[indiceLinha]->increaseNumElementos();
		this->numElementos--;
		return dado;
	}

	void imprimirChaves() {
		for( int i = 0; i < this->altura; i++ ) {
			AssociacaoHash<Tipo> *e = this->tabela[i]->getInicio();
			while( e != 0 ) {
				const char *chave = e->getChave();
				std::cout << std::string( chave ) << std::endl;
				e = e->getProximo();
			}
		}
	}

	Tipo* get( const char *chave ) {
		if( *chave == 0 )
			throw ERROCHAVEINVALIDA;

		int indiceLinha = this->hash( chave );
		AssociacaoHash<Tipo> *obj = this->tabela[indiceLinha]->getInicio();

		while( obj != 0 && strcmp( obj->getChave(), chave ) != 0 )
			obj = obj->getProximo();

		if( obj == 0 )
			throw ERRODADOINEXISTENTE;

		return obj->getDado();
	}

private:
	int hash( const char *chave ) {
		int soma = 0;
		int i = 0;

		while( *(chave+i) != 0 ) {
			soma += *(chave+i);
			i++;
		}

		return (soma % this->altura);
	}

};

#endif
