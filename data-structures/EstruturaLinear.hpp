
#ifndef ESTRUTURALINEAR_H_
#define ESTRUTURALINEAR_H_
#define TAMANHOMAX 30
#define ERROESTRUTURACHEIA -1
#define ERROESTRUTURAVAZIA -2
#include <iostream>

template <typename Tipo>
class EstruturaLinear {

protected:
	int posicaoAtual;
	Tipo estruturaLinear[ TAMANHOMAX ];

public:
	EstruturaLinear() {
		inicializa();
	}

	virtual ~EstruturaLinear() {
		inicializa();
	}

	bool vazia(){
		return (posicaoAtual == -1);
	}

	bool cheia(){
		return ( posicaoAtual == TAMANHOMAX - 1 );
	}

	void inicializa() {
		posicaoAtual = -1;
	}

	Tipo getUltimo() {
		if ( this->vazia() )
			throw ERROESTRUTURAVAZIA;
		return this->estruturaLinear[ this->posicaoAtual ];
	}

	void incluir( Tipo dado ) {
		if( cheia() )
			throw ERROESTRUTURACHEIA;
    
		estruturaLinear[++posicaoAtual] = dado;
	}

	void imprimir() {

		using namespace std;

		if ( vazia() )
			throw ERROESTRUTURAVAZIA;

		for( int i = 0; i <= posicaoAtual; i++ )
			cout << i << " " << estruturaLinear[ i ] << "\n";

	}

	virtual Tipo retirar() = 0;

};

#endif
