#ifndef NODO_H_
#define NODO_H_

/**
 * Nodo de uma Árvore de Busca Binária.
 */
template <typename Tipo>
class Nodo {

private:
	int altura;
	Tipo *informacao;

public:
	/**
	 * Construtor.
	 */
	Nodo() {
		altura = 0;
		informacao = 0;
	}

	/**
	 * Destrutor.
	 */
	virtual ~Nodo() {
		delete( informacao );
	}

	/**
	 * Obter a altura do nodo.
	 * @return O tamanho do maior caminho desse nodo até a folha mais longínqua.
	 */
	int getAltura() {
		return altura;
	}

	/**
	 * Obter o dado correspondente ao nodo.
	 * @return O dado.
	 */
	Tipo* getInformacao() {
		return informacao;
	}

	/**
	 * Definir a altura do nodo.
	 * @param altura O tamanho do maior caminho desse nodo até a folha mais longínqua.
	 */
	void setAltura( int altura ) {
		this->altura = altura;
	}

	/**
	 * Definir o dado correspondente ao nodo.
	 * @param informacao O dado.
	 */
	void setInformacao( Tipo *informacao ) {
		this->informacao = informacao;
	}

};

#endif
