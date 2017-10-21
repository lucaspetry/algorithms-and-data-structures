#ifndef LISTA_H_
#define LISTA_H_
#define TAMANHOMAX 100
#define ERRODADONULO -1
#define ERRODADOINEXISTENTE -2
#define ERROLISTACHEIA -3
#define ERROLISTAVAZIA -4
#define ERROINDICEINVALIDO -5
#include <iostream>
#include <stdio.h>

template <typename Tipo>
class Lista {

protected:
	int posicaoAtual;
	Tipo dados[TAMANHOMAX];

public:
	Lista() {
		inicializa();
	}

	virtual ~Lista() {
		inicializa();
	}

	bool vazia(){
		return ( posicaoAtual == -1 );
	}

	bool cheia(){
		return ( posicaoAtual == TAMANHOMAX - 1 );
	}

	void inicializa() {
		posicaoAtual = -1;
	}

	Tipo getElemento( int posicao ) {
		return dados[posicao];
	}

	void adiciona( Tipo dado ){
		adicionaNaPosicao( dado, posicaoAtual + 1 );
	}

	void adicionaNoInicio( Tipo dado ){
		adicionaNaPosicao( dado, 0 );
	}

	void adicionaNaPosicao( Tipo dado, int posicao ){
		if ( cheia() )
			throw ERROLISTACHEIA;

		if( posicao > posicaoAtual + 1 || posicao < 0 )
			throw ERROINDICEINVALIDO;

		posicaoAtual++;
		for( int i = posicaoAtual; i > posicao; i-- )
			dados[i] = dados[i-1];

		dados[posicao] = dado;
	}

	void adicionaEmOrdem( Tipo dado ){

		int contador = 0;

		while( dado > dados[contador] && contador <= posicaoAtual )
			contador++;

		adicionaNaPosicao( dado, contador );

	}

	Tipo retira(){
		if( vazia() )
			throw ERROLISTAVAZIA;

		return retiraDaPosicao( posicaoAtual );
	}

	Tipo retiraDoInicio(){
		if( vazia() )
			throw ERROLISTAVAZIA;

		return retiraDaPosicao( 0 );
	}

	Tipo retiraDaPosicao( int posicao ){
		if( posicao > posicaoAtual + 1 || posicao < 0 )
			throw ERROINDICEINVALIDO;

		Tipo dado = dados[posicao];
		posicaoAtual--;
		for(int i = posicao; i <= posicaoAtual; i++ )
			dados[i] = dados[i+1];

		return dado;
	}

	Tipo retiraEspecifico( Tipo dado ){

		if( vazia() )
			throw ERROLISTAVAZIA;

		int contador = 0;

		while( dados[contador] != dado && contador <= posicaoAtual )
			contador++;

		if( contador > posicaoAtual )
			throw ERRODADOINEXISTENTE;

		int indice = contador;

		retiraDaPosicao( indice );

		return dado;
	}

	int tamanho() {
		return posicaoAtual + 1;
	}

	void imprimir() {
		printf("Imprimindo lista:\n\n");

		if( vazia() ) {
			printf("Lista vazia!\n");
		} else {
			for(int i = 0; i < tamanho(); i++)
			{
				printf("%d",i);
				printf("> %s", getElemento( i ) );
				printf("\n");
			}
			printf("\n");
		}
	}

};

#endif
