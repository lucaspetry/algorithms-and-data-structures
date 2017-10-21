#ifndef NODOAVL_H_
#define NODOAVL_H_

#include "Nodo.hpp"

/**
 * Nodo da Árvore AVL.
 */
template<typename Tipo>
class NodoAVL: public Nodo<Tipo> {

private:
	NodoAVL *esquerda;
	NodoAVL *direita;

public:
	/**
	 * Construtor.
	 */
	NodoAVL() {
		esquerda = 0;
		direita = 0;
	}

	/**
	 * Construtor.
	 * @param informacao Dado correspondente ao nodo.
	 */
	NodoAVL( Tipo *informacao ) {
		this->setInformacao(informacao);
		esquerda = 0;
		direita = 0;
	}

	/**
	 * Destrutor.
	 */
	virtual ~NodoAVL() {
		delete( esquerda );
		delete( direita );
	}

	/**
	 * Obter o nodo de nível maior em uma unidade (sub-árvore) da esquerda.
	 * @return O nodo da esquerda.
	 */
	NodoAVL* getEsquerda() {
		return esquerda;
	}

	/**
	 * Obter o nodo de nível maior em uma unidade (sub-árvore) da direita.
	 * @return O nodo da direita.
	 */
	NodoAVL* getDireita() {
		return direita;
	}

	/**
	 * Definir o nodo de nível maior em uma unidade (sub-árvore) da esquerda.
	 * @param nodo O novo nodo da esquerda.
	 */
	void setEsquerda( NodoAVL *nodo ) {
		this->esquerda = nodo;
	}

	/**
	 * Definir o nodo de nível maior em uma unidade (sub-árvore) da direta.
	 * @param nodo O novo nodo da direita.
	 */
	void setDireita( NodoAVL *nodo ) {
		this->direita = nodo;
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
