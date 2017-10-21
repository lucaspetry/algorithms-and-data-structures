#ifndef ELEMENTO_HPP_
#define ELEMENTO_HPP_

template <typename Tipo>
class Elemento {

protected:
	Elemento<Tipo> *proximo;
	Tipo *dado;

public:

	Elemento(){
		proximo = 0;
		dado = 0;
	}

	~Elemento(){

	}

	void setProximo( Elemento<Tipo>* prox ) {
		proximo = prox;
	}

	Elemento<Tipo>* getProximo(){
		return proximo;
	}

	void setDado(Tipo* d){
		dado = d;
	}

	Tipo* getDado(){
		return dado;
	}

};

#endif
