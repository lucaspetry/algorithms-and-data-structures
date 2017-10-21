#ifndef NODORB_H_
#define NODORB_H_

#define RUBRO 0
#define NEGRO 1

#include "Nodo.hpp"

/**
 * Nodo da Árvore Red-Black.
 */
template <typename Tipo>
class NodoRB : public Nodo<Tipo> {

private:
	int cor;
	NodoRB *pai;
	NodoRB *esquerda;
	NodoRB *direita;

public:
	/**
	 * Construtor.
	 */
	NodoRB() {
		pai = 0;
		cor = RUBRO;
		esquerda = 0;
		direita = 0;
	}

	/**
	 * Construtor.
	 * @param informacao Dado correspondente ao nodo.
	 */
	NodoRB( Tipo *informacao ) {
		this->setInformacao(informacao);
		pai = 0;
		cor = RUBRO;
		esquerda = 0;
		direita = 0;
	}

	/**
	 * Destrutor.
	 */
	virtual ~NodoRB() {
		delete( esquerda );
		delete( direita );
	}

	/**
	 * Obter o nodo de nível maior em uma unidade (sub-árvore) da esquerda.
	 * @return O nodo da esquerda.
	 */
	NodoRB* getEsquerda() {
		return esquerda;
	}

	/**
	 * Obter o nodo de nível maior em uma unidade (sub-árvore) da direita.
	 * @return O nodo da direita.
	 */
	NodoRB* getDireita() {
		return direita;
	}

	/**
	 * Obter o nodo de nível menor em uma unidade desse nodo.
	 * @return O nodo pai.
	 */
	NodoRB* getPai() {
		return pai;
	}


	/**
	 * Obter o único nodo de mesmo nível diferente do nodo atual da sub-árvore correspondente ao pai desse nodo.
	 * @return O nodo irmão.
	 */
	NodoRB* getIrmao() {

		if( this->getPai() != 0 ) {
			if( this->getPai()->getEsquerda() == this )
				return this->getPai()->getDireita();

			return this->getPai()->getEsquerda();
		}
		return 0;

	}

	/**
	 * Obter o único nodo de mesmo nível do nodo pai e diferente dele da sub-árvore correspondente ao avô desse nodo.
	 * @return O nodo tio.
	 */
	NodoRB* getTio() {

		if( this->getAvo() == 0 )
			return 0;

		NodoRB *tio = this->getAvo()->getEsquerda();
		if( this->getAvo()->getEsquerda() == this->getPai() )
			tio = this->getAvo()->getDireita();

		return tio;

	}

	/**
	 * Obter o nodo de nível menor em duas unidades desse nodo.
	 * @return O nodo avô.
	 */
	NodoRB* getAvo() {

		if( this->getPai() != 0 )
			return this->getPai()->getPai();
		return 0;

	}

	/**
	 * Obter a cor do nodo.
	 * @return A cor do nodo.
	 */
	int getCor() {
		return cor;
	}

	/**
	 * Definir o nodo de nível maior em uma unidade (sub-árvore) da esquerda.
	 * @param nodo O novo nodo da esquerda.
	 */
	void setEsquerda( NodoRB *nodo ) {
		this->esquerda = nodo;
	}

	/**
	 * Definir o nodo de nível maior em uma unidade (sub-árvore) da direta.
	 * @param nodo O novo nodo da direita.
	 */
	void setDireita( NodoRB *nodo ) {
		this->direita = nodo;
	}

	/**
	 * Definir o nodo de nível menor em uma unidade desse nodo.
	 * @param pai O novo nodo pai.
	 */
	void setPai( NodoRB *pai ) {
		this->pai = pai;
	}

	/**
	 * Definir a cor do nodo.
	 * @param cor A nova cor do nodo.
	 */
	void setCor( int cor ) {
		this->cor = cor;
	}

	/**
	 * Atualizar a altura do nodo pela altura dos nodos filhos.
	 */
	void atualizarAlturaPorFilhos() {

		int altE = -1;
		int altD = -1;

		if( this->getDireita() != 0 )
			altD = this->getDireita()->getAltura();

		if( this->getEsquerda() != 0 )
			altE = this->getEsquerda()->getAltura();

		this->setAltura( max(altE, altD) + 1 );

	}

	/**
	 * Obter o fator de balanceamento do nodo.
	 * @return O balanceamento do nodo.
	 */
	int getBalanceamento() {

		int altE = -1;
		int altD = -1;

		if( this->getEsquerda() != 0 )
			altE = this->getEsquerda()->getAltura();

		if( this->getDireita() != 0 )
			altD = this->getDireita()->getAltura();

		return altE - altD;

	}

};

#endif
