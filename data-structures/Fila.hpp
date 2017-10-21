#ifndef FILA_H_
#define FILA_H_
#include "EstruturaLinear.hpp"

template <typename Tipo>
class Fila : public EstruturaLinear<Tipo> {

public:
	Fila() { }
	Tipo retirar() {

		if( this->vazia() )
			throw ERROESTRUTURAVAZIA;

		Tipo retorno = this->estruturaLinear[0];
		this->posicaoAtual--;

		for( int i = 0; i <= this->posicaoAtual; i++ )
			this->estruturaLinear[i] = this->estruturaLinear[i+1];

		return retorno;
	}
};

#endif
