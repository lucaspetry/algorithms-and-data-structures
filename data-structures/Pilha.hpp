#ifndef PILHA_H_
#define PILHA_H_
#include "EstruturaLinear.hpp"

template <typename Tipo>
class Pilha : public EstruturaLinear<Tipo> {

public:

	Pilha() { };

	Tipo retirar() {

		if( this->vazia() )
			throw ERROESTRUTURAVAZIA;

		Tipo retorno = this->getUltimo();
		this->posicaoAtual--;

		return retorno;
	}
};

#endif
