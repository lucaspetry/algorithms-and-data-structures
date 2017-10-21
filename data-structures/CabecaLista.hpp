#ifndef CABECALISTA_HPP_
#define CABECALISTA_HPP_
#include "Elemento.hpp"

template <typename Tipo>
class CabecaLista {

protected:
	Elemento<Tipo> *inicio;
	int tamanho;

public:

	CabecaLista(){
		tamanho = 0;
		inicio = 0;
	}

	virtual ~CabecaLista(){
		delete( inicio );
	}


	void setInicio( Elemento<Tipo>* ini ){
		inicio = ini;
	}

	Elemento<Tipo>* getInicio(){
		return inicio;
	}

	int getTamanho(){
		return tamanho;
	}

	void setTamanho(int tam){
		tamanho = tam;
	}

};

#endif
