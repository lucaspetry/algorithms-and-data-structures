#ifndef ARVORERB_HPP_
#define ARVORERB_HPP_

#include "ArvoreBinaria.hpp"
#include "NodoRB.hpp"
#include <iostream>

/**
 * Árvore Red-Black é uma árvore de busca binária balanceada que segue as seguintes regras:
 * 1. Todo nodo é rubro ou negro;
 * 2. A raiz da árvore é negra;
 * 3. Toda folha (nodo vazio) é negra;
 * 4. Se um nodo for rubro, então ambos os filhos são negros;
 * 5. Para todo nodo, todos os caminhos até uma folha contém o mesmo número de nodos negros.
 */
template <typename Tipo>
class ArvoreRB: public ArvoreBinaria< Tipo, NodoRB<Tipo> > {

private:
	NodoRB<Tipo> *folhaNegra;

public:
	/**
	 * Construtor.
	 */
	ArvoreRB() {
		this->setArquivoLog( "rb.dat" );
		folhaNegra = new NodoRB<Tipo>( 0 );
		folhaNegra->setCor( NEGRO );
		this->setRaiz( folhaNegra );
	}

	/**
	 * Destrutor.
	 */
	virtual ~ArvoreRB() { }

	/**
	 * Inserir um dado na árvore.
	 * @param dado O dado a ser inserido.
	 * @return O dado inserido.
	 */
	Tipo* inserir(Tipo *dado) {

		timeval inicio = this->tempo();
		NodoRB<Tipo> *novoNodo = new NodoRB<Tipo>( dado );
		this->setRaiz( this->inserir( this->getRaiz(), novoNodo ) );
		verificarAtualizarInsercao( novoNodo );
		timeval fim = this->tempo();
		this->setNumElementos( this->getNumElementos() + 1 );
		this->escreverLogArquivo( this->diferencaDeTempo( inicio, fim ) );
		return dado;

	}

	/**
	 * Remover um dado na árvore.
	 * @param dado O dado a ser removido.
	 * @return O dado removido.
	 */
	Tipo* remover(Tipo *dado) {

		//timeval inicio = this->tempo();
		NodoRB<Tipo> *nodo = this->getNodoRemocao( this->getRaiz(), dado );
		delete( dado );
		dado = nodo->getInformacao();
		removerAtualizar( nodo );
		//timeval fim = this->tempo();
		this->setNumElementos( this->getNumElementos() - 1 );
		//this->escreverLogArquivo( this->diferencaDeTempo( inicio, fim ) );
		return dado;

	}

private:
	NodoRB<Tipo>* inserir(NodoRB<Tipo> *raizAtual, NodoRB<Tipo> *dado) {

		if ( raizAtual == folhaNegra ) {
			raizAtual = dado;
			raizAtual->setDireita( folhaNegra );
			raizAtual->setEsquerda( folhaNegra );

		} else if ( *(*raizAtual).getInformacao() > *(*dado).getInformacao() ) {
			(*raizAtual).setEsquerda( inserir( (*raizAtual).getEsquerda(), dado ) );
			(*raizAtual).getEsquerda()->setPai( raizAtual );

		} else if ( *(*raizAtual).getInformacao() < *(*dado).getInformacao() ) {
			(*raizAtual).setDireita( inserir( (*raizAtual).getDireita(), dado ) );
			(*raizAtual).getDireita()->setPai( raizAtual );

		} else {
			delete( dado );
			throw ERRODADODUPLICADO;
		}

		return raizAtual;

	}

	NodoRB<Tipo>* getNodoRemocao(NodoRB<Tipo> *raizAtual, Tipo *dado) {

		if ( raizAtual == folhaNegra )
			throw ERRODADOINEXISTENTE;

		else if ( *(*raizAtual).getInformacao() > (*dado) )
			return getNodoRemocao( (*raizAtual).getEsquerda(), dado );

		else if ( *(*raizAtual).getInformacao() < (*dado) )
			return getNodoRemocao( (*raizAtual).getDireita(), dado );

		else
			return raizAtual;

	}

	NodoRB<Tipo>* getMenorFolha( NodoRB<Tipo> *nodo ) {

		while( nodo->getEsquerda() != folhaNegra ) {
			nodo = nodo->getEsquerda();
		}

		return nodo;

	}

	void atualizarRaizAtual( NodoRB<Tipo> *nodo ) {

		while( nodo->getPai() != 0 ) {
			nodo = nodo->getPai();
		}
		this->setRaiz( nodo );
		this->getRaiz()->setCor( NEGRO );

	}

	NodoRB<Tipo>* verificarAtualizarInsercao( NodoRB<Tipo> *nodo ) {

		if( nodo != 0 && nodo->getAvo() != 0 ) {
			while( nodo != this->getRaiz() && (*nodo).getPai()->getCor() == RUBRO ) {

				if( (*nodo).getAvo()->getEsquerda() == (*nodo).getPai() )
					nodo = correcaoElevacaoEsquerda( nodo );
				else
					nodo = correcaoElevacaoDireita( nodo );

				atualizarRaizAtual( nodo );
			}
		}

		return nodo;

	}

	NodoRB<Tipo>* removerAtualizar( NodoRB<Tipo> *nodo ) {

		if( (*nodo).getDireita() != folhaNegra && (*nodo).getEsquerda() != folhaNegra ) {
			NodoRB<Tipo> *temp = getMenorFolha( nodo->getDireita() );
			delete( raizAtual->getInformacao() );
			Tipo *novoDado = new Tipo();
			(*novoDado) = *temp->getInformacao();
			(*nodo).setInformacao( novoDado );
			NodoRB<Tipo> *nodoRem = getNodoRemocao( nodo->getDireita(), temp->getInformacao() );
			NodoRB<Tipo> *nodoPai = nodoRem->getPai();
			nodoRem->setPai( 0 );
			nodoRem->setDireita( 0 );
			nodoRem->setEsquerda( 0 );

			if( nodoPai->getEsquerda() == nodoRem )
				nodoPai->setEsquerda( folhaNegra );
			else
				nodoPai->setDireita( folhaNegra );

			delete( nodoRem );
			nodo = nodoPai;

		} else {
			if( (*nodo).getDireita() != folhaNegra ) {
				NodoRB<Tipo> *nodoPai = nodo->getPai();
				NodoRB<Tipo> *novaRaizAtual = nodo->getDireita();

				novaRaizAtual->setPai( nodoPai );
				if( nodoPai->getEsquerda() == nodo )
					nodoPai->setEsquerda( novaRaizAtual );
				else
					nodoPai->setDireita( novaRaizAtual );

				nodo->setPai( 0 );
				nodo->setEsquerda( 0 );
				nodo->setDireita( 0 );
				delete( nodo );
				nodo = novaRaizAtual;

			} else if( (*nodo).getEsquerda() != folhaNegra ) {
				NodoRB<Tipo> *nodoPai = nodo->getPai();
				NodoRB<Tipo> *novaRaizAtual = nodo->getEsquerda();

				novaRaizAtual->setPai( nodoPai );
				if( nodoPai->getEsquerda() == nodo )
					nodoPai->setEsquerda( novaRaizAtual );
				else
					nodoPai->setDireita( novaRaizAtual );

				nodo->setPai( 0 );
				nodo->setEsquerda( 0 );
				nodo->setDireita( 0 );
				delete( nodo );
				nodo = novaRaizAtual;

			} else {
				NodoRB<Tipo> *nodoPai = nodo->getPai();

				if( nodoPai->getEsquerda() == nodo )
					nodoPai->setEsquerda( folhaNegra );
				else
					nodoPai->setDireita( folhaNegra );

				nodo->setPai( 0 );
				nodo->setDireita( 0 );
				nodo->setEsquerda( 0 );
				delete( nodo );
				nodo = nodoPai;
			}
		}
		
		while( nodo != this->getRaiz() ) {
			if( nodo == nodo->getPai()->getEsquerda() )
				nodo = correcaoElevacaoDelEsquerda( nodo );
			else
				nodo = correcaoElevacaoDelDireita( nodo );

			atualizarRaizAtual( nodo );
		}
		this->getRaiz()->setCor( NEGRO );
		return nodo;

	}

	NodoRB<Tipo>* correcaoElevacaoDelEsquerda( NodoRB<Tipo> *nodo ) {

		NodoRB<Tipo> *temp = nodo->getIrmao();
		if( temp->getCor() == RUBRO ) {
			temp->setCor( NEGRO );
			nodo->getPai()->setCor( RUBRO );
			rotacaoSimplesEsquerda( nodo->getPai() );
			temp = nodo->getIrmao();
		}

		if( temp->getEsquerda()->getCor() == NEGRO && temp->getDireita()->getCor() == NEGRO ) {
			temp->setCor( RUBRO );
			nodo = nodo->getPai();
		} else {

			if( temp->getDireita()->getCor() == NEGRO ) {
				temp->getEsquerda()->setCor( NEGRO );
				temp->setCor( RUBRO );
				rotacaoSimplesDireita( temp );
				temp = nodo->getIrmao();
			}
			temp->setCor( nodo->getPai()->getCor() );
			nodo->getPai()->setCor( NEGRO );
			temp->getDireita()->setCor( NEGRO );
			rotacaoSimplesEsquerda( nodo->getPai() );
			nodo = this->getRaiz();
		}

		return nodo;

	}

	NodoRB<Tipo>* correcaoElevacaoDelDireita( NodoRB<Tipo> *nodo ) {

		NodoRB<Tipo> *temp = nodo->getIrmao();
		if( temp->getCor() == RUBRO ) {
			temp->setCor( NEGRO );
			nodo->getPai()->setCor( RUBRO );
			rotacaoSimplesDireita( nodo->getPai() );
			temp = nodo->getIrmao();
		}

		if( temp->getEsquerda()->getCor() == NEGRO && temp->getDireita()->getCor() == NEGRO ) {
			temp->setCor( RUBRO );
			nodo = nodo->getPai();
		} else {

			if( temp->getEsquerda()->getCor() == NEGRO ) {
				temp->getDireita()->setCor( NEGRO );
				temp->setCor( RUBRO );
				rotacaoSimplesEsquerda( temp );
				temp = nodo->getIrmao();
			}
			temp->setCor( nodo->getPai()->getCor() );
			nodo->getPai()->setCor( NEGRO );
			temp->getEsquerda()->setCor( NEGRO );
			rotacaoSimplesDireita( nodo->getPai() );
			nodo = this->getRaiz();
		}

		return nodo;

	}

	NodoRB<Tipo>* correcaoElevacaoEsquerda( NodoRB<Tipo> *nodo ) {

		if( nodo->getTio()->getCor() == RUBRO ) { // Caso 1
			nodo->getPai()->setCor( NEGRO );
			nodo->getAvo()->setCor( RUBRO );
			nodo->getTio()->setCor( NEGRO );
			nodo = nodo->getAvo();
		} else { // Caso 2
			if( nodo->getPai()->getDireita() == nodo ) {
				nodo = rotacaoSimplesEsquerda( nodo->getPai() );
				nodo = nodo->getEsquerda();
			}
			// Caso 3
			nodo->getPai()->setCor( NEGRO );
			nodo->getAvo()->setCor( RUBRO );
			nodo = rotacaoSimplesDireita( nodo->getAvo() );
		}
		return nodo;

	}

	NodoRB<Tipo>* correcaoElevacaoDireita( NodoRB<Tipo> *nodo ) {

		if( nodo->getTio()->getCor() == RUBRO ) { // Caso 1
			nodo->getPai()->setCor( NEGRO );
			nodo->getAvo()->setCor( RUBRO );
			nodo->getTio()->setCor( NEGRO );
			nodo = nodo->getAvo();
		} else { // Caso 2
			if( nodo->getPai()->getEsquerda() == nodo ) {
				nodo = rotacaoSimplesDireita( nodo->getPai() );
				nodo = nodo->getDireita();
			}
			// Caso 3
			nodo->getPai()->setCor( NEGRO );
			nodo->getAvo()->setCor( RUBRO );
			nodo = rotacaoSimplesEsquerda( nodo->getAvo() );
		}
		return nodo;

	}

	NodoRB<Tipo>* rotacaoSimplesDireita(NodoRB<Tipo> *nodo) {

		NodoRB<Tipo> *novaRaiz;

		novaRaiz = (*nodo).getEsquerda();
		novaRaiz->setPai( nodo->getPai() );

		if( nodo->getPai() != 0 && nodo->getPai()->getEsquerda() == nodo )
			nodo->getPai()->setEsquerda( novaRaiz );
		else if( nodo->getPai() != 0 && nodo->getPai()->getDireita() == nodo )
			nodo->getPai()->setDireita( novaRaiz );

		(*nodo).setEsquerda( (*novaRaiz).getDireita() );
		(*nodo).getEsquerda()->setPai( nodo );
		(*novaRaiz).setDireita(nodo);
		(*nodo).setPai( novaRaiz );

		(*nodo).atualizarAlturaPorFilhos();
		(*novaRaiz).atualizarAlturaPorFilhos();

		return novaRaiz; // Retorna a nova raiz da sub-árvore

	}

	NodoRB<Tipo>* rotacaoSimplesEsquerda(NodoRB<Tipo> *nodo) {

		NodoRB<Tipo> *novaRaiz;

		novaRaiz = (*nodo).getDireita();
		novaRaiz->setPai( nodo->getPai() );

		if( nodo->getPai() != 0 && nodo->getPai()->getEsquerda() == nodo )
			nodo->getPai()->setEsquerda( novaRaiz );
		else if( nodo->getPai() != 0 && nodo->getPai()->getDireita() == nodo )
			nodo->getPai()->setDireita( novaRaiz );

		(*nodo).setDireita( (*novaRaiz).getEsquerda() );
		(*nodo).getDireita()->setPai( nodo );
		(*novaRaiz).setEsquerda( nodo );
		(*nodo).setPai( novaRaiz );

		(*nodo).atualizarAlturaPorFilhos();
		(*novaRaiz).atualizarAlturaPorFilhos();

		return novaRaiz; // Retorna a nova raiz da sub-árvore

	}

protected:
	NodoRB<Tipo> *preOrdem(NodoRB<Tipo> *raizAtual) {
		if (raizAtual != folhaNegra) {
			std::cout << *(*raizAtual).getInformacao() << endl;
			preOrdem((*raizAtual).getEsquerda());
			preOrdem((*raizAtual).getDireita());
		}
		return raizAtual;
	}

	NodoRB<Tipo>* emOrdem(NodoRB<Tipo> *raizAtual) {
		if (raizAtual != folhaNegra) {
			emOrdem((*raizAtual).getEsquerda());
			std::cout << *(*raizAtual).getInformacao() << endl;
			emOrdem((*raizAtual).getDireita());
		}
		return raizAtual;
	}

	NodoRB<Tipo> *posOrdem(NodoRB<Tipo> *raizAtual) {
		if (raizAtual != folhaNegra) {
			posOrdem((*raizAtual).getEsquerda());
			posOrdem((*raizAtual).getDireita());
			std::cout << *(*raizAtual).getInformacao() << endl;
		}
		return raizAtual;
	}

};

#endif
