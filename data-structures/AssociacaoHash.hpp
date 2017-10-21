#ifndef ASSOCIACAOHASH_HPP_
#define ASSOCIACAOHASH_HPP_

template <typename Tipo>
class AssociacaoHash {

private:
	const char *chave;
	Tipo *dado;
	AssociacaoHash<Tipo> *proximoDado;

public:
	AssociacaoHash() {
		chave = 0;
		dado = 0;
		proximoDado = 0;
	}

	AssociacaoHash( const char *chave, Tipo *dado ) {
		this->chave = chave;
		this->dado = dado;
		this->proximoDado = 0;
	}

	AssociacaoHash( const char *chave, Tipo *dado, AssociacaoHash<Tipo> *proximoDado ) {
		this->chave = chave;
		this->dado = dado;
		this->proximoDado = proximoDado;
	}

	virtual ~AssociacaoHash() {
		if( proximoDado != 0 )
			delete( proximoDado );
	}

	void setProximo( AssociacaoHash<Tipo> *dado ) {
		this->proximoDado = dado;
	}

	AssociacaoHash<Tipo>* getProximo() {
		return this->proximoDado;
	}

	void setDado( Tipo *dado ) {
		this->dado = dado;
	}

	Tipo* getDado() {
		return this->dado;
	}

	const char* getChave() {
		return this->chave;
	}

};

#endif
