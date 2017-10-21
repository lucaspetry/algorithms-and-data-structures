#ifndef LINHAHASH_HPP_
#define LINHAHASH_HPP_

#include "AssociacaoHash.hpp"

template <typename Tipo>
class LinhaHash {

private:
	AssociacaoHash<Tipo> *inicio;
	int elementosLinha;

public:
	LinhaHash() {
		inicio = 0;
		elementosLinha = 0;
	}

	virtual ~LinhaHash() {
		if( inicio != 0 )
			delete( inicio );
	}

	AssociacaoHash<Tipo>* getInicio() {
		return this->inicio;
	}

	void setInicio( AssociacaoHash<Tipo> *inicio ) {
		this->inicio = inicio;
	}

	void increaseNumElementos() {
		elementosLinha++;
	}

	void decreaseNumElementos() {
		elementosLinha--;
		if( elementosLinha < 0 )
			elementosLinha = 0;
	}

	int getNumElementos() {
		return this->elementosLinha;
	}

};

#endif
