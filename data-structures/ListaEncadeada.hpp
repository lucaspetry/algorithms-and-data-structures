#ifndef LISTAENCADEADA_HPP_
#define LISTAENCADEADA_HPP_
#include "CabecaLista.hpp"
#define ERROLISTAVAZIA -1
#define ERROLISTACHEIA -2
#define ERRODADOINEXISTENTE -3
#define ERROINDICEINVALIDO -4

template<typename Tipo>
class ListaEncadeada {

protected:
	CabecaLista<Tipo> *cabeca;

public:
	ListaEncadeada() {
		cabeca = new CabecaLista<Tipo>();
	}

	virtual ~ListaEncadeada() {
		destruir();
	}

	void destruir() {

		while( !vazia() )
			eliminaDaPosicao( 0 );

	}

	void adiciona( Tipo *dado ) {
		adicionaNaPosicao( tamanho(), dado );
	}

	void adicionaNoInicio( Tipo *dado ) {

		Elemento<Tipo> *novoElemento = new Elemento<Tipo>();

		if( novoElemento == 0 )
			throw ERROLISTACHEIA;
		
		(*cabeca).setTamanho( tamanho() + 1 );
		
		Elemento<Tipo> *proximo = (*cabeca).getInicio();
		(*novoElemento).setProximo( proximo );
		(*novoElemento).setDado( dado );
		(*cabeca).setInicio( novoElemento );

	}

	void adicionaNaPosicao( int posicao, Tipo *dado ) {

		Elemento<Tipo> *novoElemento = new Elemento<Tipo>();

		if( posicao > tamanho() )
			throw ERROINDICEINVALIDO;

		if( novoElemento == 0 )
			throw ERROLISTACHEIA;

		if( posicao == 0 ) {
			adicionaNoInicio( dado );
		} else {
			(*cabeca).setTamanho( tamanho() + 1 );
			Elemento<Tipo> *anterior = (*cabeca).getInicio();

			for( int i = 1; i < posicao; i++ ) {
				anterior = (*anterior).getProximo();
			}

			(*novoElemento).setProximo( (*anterior).getProximo() );
			(*novoElemento).setDado( dado );
			(*anterior).setProximo( novoElemento );
		}

	}

	void adicionaEmOrdem( Tipo *dado ) {
		/*
		int contador = 0;
		Elemento<Tipo> *aux = (*cabeca).getInicio();

		while( *dado > *( (*aux).getDado() ) && contador < tamanho() ) {
			contador++;
			aux = (*aux).getProximo();
		}

		adicionaNaPosicao( contador, dado );
	*/
	}

	Tipo* getElemento( int posicao ) {
		
		if( posicao >= tamanho() )
			throw ERROINDICEINVALIDO;

		Elemento<Tipo> *elemento = (*cabeca).getInicio();

		if( posicao == 0 )
			return (*elemento).getDado();

		for( int i = 1; i <= posicao; i++ )
			elemento = (*elemento).getProximo();

		return (*elemento).getDado();

	}

	Tipo* retira() {
		return retiraDaPosicao( tamanho() - 1 );
	}

	Tipo* retiraDoInicio() {

		if( vazia() )
			throw ERROLISTAVAZIA;

		(*cabeca).setTamanho( tamanho() - 1 );
		Elemento<Tipo> *retirado = (*cabeca).getInicio();
		(*cabeca).setInicio( (*retirado).getProximo() );

		Tipo *dado = (*retirado).getDado();
		(*retirado).setDado( 0 );
		delete( retirado );

		return dado;

	}

	Tipo* retiraDaPosicao( int posicao ) {

		if( posicao >= tamanho() )
			throw ERROINDICEINVALIDO;

		if( posicao == 0 )
			return retiraDoInicio();

		(*cabeca).setTamanho( tamanho() - 1 );
		Elemento<Tipo> *anterior = (*cabeca).getInicio();

		for( int i = 1; i < posicao; i++ )
			anterior = (*anterior).getProximo();

		Elemento<Tipo> *retirado = (*anterior).getProximo();
		Tipo *dado = (*retirado).getDado();
		(*retirado).setDado( 0 );
		(*anterior).setProximo( (*retirado).getProximo() );
		delete( retirado );

		return dado;

	}

	Tipo* retiraEspecifico( Tipo *dado ) {

		Elemento<Tipo> *anterior = (*cabeca).getInicio();

		if( *dado == *( (*anterior).getDado() ) )
			return retiraDoInicio();

		int posicao = 1;
		Elemento<Tipo> *proximo = (*anterior).getProximo();

		while( posicao < tamanho() && *( (*proximo).getDado() ) != *dado ) {
			posicao++;
			anterior = proximo;
			proximo = (*anterior).getProximo();
		}

		if( proximo == 0 )
			throw ERRODADOINEXISTENTE;

		(*anterior).setProximo( (*proximo).getProximo() );
		(*proximo).setDado( 0 );
		delete( proximo );

		return dado;
	}

	int tamanho() {
		return (*cabeca).getTamanho();
	}

	bool vazia() {
		return ( tamanho() == 0 );
	}

	void eliminaDaPosicao( int posicao ) {
		delete( retiraDaPosicao( posicao ) );
	}

};

#endif
