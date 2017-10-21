#ifndef ARVOREAVL_HPP_
#define ARVOREAVL_HPP_

#include "ArvoreBinaria.hpp"
#include "NodoAVL.hpp"

/**
 * Árvore AVL é uma árvore de busca binária autobalanceada, onde as alturas
 * de duas sub-árvores a partir de um nodo diferem de no máximo uma unidade.
 */
template <typename Tipo>
class ArvoreAVL: public ArvoreBinaria< Tipo, NodoAVL<Tipo> > {

public:
	/**
	 * Construtor.
	 */
	ArvoreAVL() {
		this->setArquivoLog( "avl.dat" );
	}

	/**
	 * Destrutor.
	 */
	virtual ~ArvoreAVL() { }

	/**
	 * Inserir um dado na árvore.
	 * @param dado O dado a ser inserido.
	 * @return O dado inserido.
	 */
	Tipo* inserir(Tipo *dado) {

		timeval inicio = this->tempo();
		NodoAVL<Tipo> *novaRaiz = this->inserir(this->getRaiz(), dado);
		timeval fim = this->tempo();
		this->setNumElementos( this->getNumElementos() + 1 );
		this->setRaiz( novaRaiz );
		this->escreverLogArquivo( this->diferencaDeTempo( inicio, fim ) );
		return dado;

	}

	/**
	 * Remover um dado na árvore.
	 * @param dado O dado a ser removido.
	 * @return O dado removido.
	 */
	Tipo* remover(Tipo *dado) {

		timeval inicio = this->tempo();
		Tipo *dadoRemovido = new Tipo();
		(*dadoRemovido) = (*dado);
		NodoAVL<Tipo> *novaRaiz = this->remover(this->getRaiz(), dado);
		timeval fim = this->tempo();
		this->setNumElementos( this->getNumElementos() - 1 );
		this->setRaiz( novaRaiz );
		this->escreverLogArquivo( this->diferencaDeTempo( inicio, fim ) );
		return dadoRemovido;

	}

private:
	NodoAVL<Tipo>* inserir(NodoAVL<Tipo> *raizAtual, Tipo *dado) {

		if ( raizAtual == 0 )
			raizAtual = new NodoAVL<Tipo>(dado);

		else if ( *(*raizAtual).getInformacao() > (*dado) )
			(*raizAtual).setEsquerda( inserir( (*raizAtual).getEsquerda(), dado ) );

		else if ( *(*raizAtual).getInformacao() < (*dado) )
			(*raizAtual).setDireita( inserir( (*raizAtual).getDireita(), dado ) );

		else
			throw ERRODADODUPLICADO;

		return atualizarNodo( raizAtual );

	}

	NodoAVL<Tipo>* remover(NodoAVL<Tipo> *raizAtual, Tipo *dado) {

		if ( raizAtual == 0 )
			throw ERRODADOINEXISTENTE;

		else if ( *(*raizAtual).getInformacao() > (*dado) )
			(*raizAtual).setEsquerda( remover( (*raizAtual).getEsquerda(), dado ) );

		else if ( *(*raizAtual).getInformacao() < (*dado) )
			(*raizAtual).setDireita( remover( (*raizAtual).getDireita(), dado ) );

		else {

			if( (*raizAtual).getDireita() != 0 && (*raizAtual).getEsquerda() != 0 ) {
				NodoAVL<Tipo> *temp = getMenorFolha( raizAtual->getDireita() );
				delete( raizAtual->getInformacao() );
				Tipo *novoDado = new Tipo();
				(*novoDado) = *temp->getInformacao();
				(*raizAtual).setInformacao( novoDado );
				(*raizAtual).setDireita( remover( raizAtual->getDireita(), temp->getInformacao() ) );
			} else {
				if( (*raizAtual).getDireita() != 0 ) {
					NodoAVL<Tipo> *temp = (*raizAtual).getDireita();
					raizAtual->setDireita(0);
					delete( raizAtual );
					return temp;

				} else if( (*raizAtual).getEsquerda() != 0 ) {
					NodoAVL<Tipo> *temp = (*raizAtual).getEsquerda();
					raizAtual->setEsquerda(0);
					delete( raizAtual );
					return temp;

				} else {
					delete( raizAtual );
					return 0;
				}
			}

		}

		return atualizarNodo( raizAtual );

	}

	NodoAVL<Tipo>* getMenorFolha( NodoAVL<Tipo> *nodo ) {

		while( nodo->getEsquerda() != 0 ) {
			nodo = nodo->getEsquerda();
		}

		return nodo;

	}

	NodoAVL<Tipo>* atualizarNodo( NodoAVL<Tipo> *nodo ) {

		if ( (*nodo).getBalanceamento() == 2) {

			if ( (*nodo).getEsquerda()->getBalanceamento() > 0)
				nodo = rotacaoSimplesDireita(nodo);
			else
				nodo = rotacaoDuplaDireita(nodo);

		} else if ( (*nodo).getBalanceamento() == -2) {

			if ( (*nodo).getDireita()->getBalanceamento() < 0 )
				nodo = rotacaoSimplesEsquerda(nodo);
			else
				nodo = rotacaoDuplaEsquerda(nodo);

		}
		(*nodo).atualizarAlturaPorFilhos();

		return nodo;

	}

	NodoAVL<Tipo>* rotacaoDuplaEsquerda(NodoAVL<Tipo> *nodo) {
		(*nodo).setDireita( rotacaoSimplesDireita((*nodo).getDireita()) );
		return rotacaoSimplesEsquerda(nodo);
	}

	NodoAVL<Tipo>* rotacaoDuplaDireita(NodoAVL<Tipo> *nodo) {
		(*nodo).setEsquerda(rotacaoSimplesEsquerda((*nodo).getEsquerda()));
		return rotacaoSimplesDireita(nodo);
	}

	NodoAVL<Tipo>* rotacaoSimplesDireita(NodoAVL<Tipo> *nodo) {

		NodoAVL<Tipo> *novaRaiz;

		novaRaiz = (*nodo).getEsquerda();
		(*nodo).setEsquerda( (*novaRaiz).getDireita() );
		(*novaRaiz).setDireita(nodo);

		(*nodo).atualizarAlturaPorFilhos();
		(*novaRaiz).atualizarAlturaPorFilhos();

		return novaRaiz; // Retorna a nova raiz da sub-árvore

	}

	NodoAVL<Tipo>* rotacaoSimplesEsquerda(NodoAVL<Tipo> *nodo) {

		NodoAVL<Tipo> *novaRaiz;

		novaRaiz = (*nodo).getDireita();
		(*nodo).setDireita( (*novaRaiz).getEsquerda() );
		(*novaRaiz).setEsquerda(nodo);

		(*nodo).atualizarAlturaPorFilhos();
		(*novaRaiz).atualizarAlturaPorFilhos();

		return novaRaiz; // Retorna a nova raiz da sub-árvore

	}

protected:
	NodoAVL<Tipo>* emOrdem(NodoAVL<Tipo> *raizAtual) {
		if (raizAtual != 0) {
			emOrdem( (*raizAtual).getEsquerda() );
			std::cout << *(*raizAtual).getInformacao() << endl;
			emOrdem( (*raizAtual).getDireita() );
		}
		return raizAtual;
	}

	NodoAVL<Tipo>* posOrdem( NodoAVL<Tipo> *raizAtual ) {
		if (raizAtual != 0) {
			posOrdem( (*raizAtual).getEsquerda() );
			posOrdem( (*raizAtual).getDireita() );
			std::cout << *(*raizAtual).getInformacao() << endl;
		}
		return raizAtual;
	}

	NodoAVL<Tipo>* preOrdem( NodoAVL<Tipo> *raizAtual ) {
		if (raizAtual != 0) {
			std::cout << *(*raizAtual).getInformacao() << endl;
			preOrdem( (*raizAtual).getEsquerda() );
			preOrdem( (*raizAtual).getDireita() );
		}
		return raizAtual;
	}

};
#endif
