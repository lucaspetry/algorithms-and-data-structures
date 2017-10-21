#ifndef ARVOREBINARIA_H_
#define ARVOREBINARIA_H_

#define ERRODADODUPLICADO -1
#define ERRODADOINEXISTENTE -2
#include "IArvore.hpp"
#include "LeitorArquivo.h"
#include <sys/time.h>

/**
 * Árvore de Busca Binária.
 */
template<typename Tipo, typename Nodo>
class ArvoreBinaria: public IArvore<Tipo> {

private:
	Nodo *raiz;
	int numElementos;
	std::string arquivoLog;

protected:
	virtual Nodo* emOrdem(Nodo *raizAtual) = 0;
	virtual Nodo* preOrdem(Nodo *raizAtual) = 0;
	virtual Nodo* posOrdem(Nodo *raizAtual) = 0;

	long diferencaDeTempo( timeval inicio, timeval fim ) {
		long diferenca, segundos, usegundos;

		segundos = fim.tv_sec - inicio.tv_sec;
		usegundos = fim.tv_usec - inicio.tv_usec;

		diferenca = segundos * 1000000 + usegundos;
		return diferenca;
	}

	timeval tempo() {
		timeval tempo;
		gettimeofday(&tempo, NULL);
		return tempo;
	}
	
public:
	/**
	 * Construtor.
	 */
	ArvoreBinaria() {
		raiz = 0;
		numElementos = 0;
	}

	/**
	 * Destrutor.
	 */
	virtual ~ArvoreBinaria() {	}

	/**
	 * Obter o nome do arquivo de logs da árvore.
	 * @return O nome do arquivo.
	 */
	std::string getArquivoLog() {
		return this->arquivoLog;
	}

	/**
	 * Definir o nome do arquivo de logs da árvore.
	 * @param name O nome do arquivo.
	 */
	void setArquivoLog( std::string name ) {
		this->arquivoLog = name;
	}

	/**
	 * Verificar se a árvore está vazia.
	 * @return true se a árvore não possui nenhum elemento.
	 */
	bool vazia() {
		return (this->getNumElementos() == 0);
	}
	
	/**
	 * Obter o número de elementos da árvore.
	 * @return O número de elementos.
	 */
	int getNumElementos() {
		return numElementos;
	}

	/**
	 * Definir o número de elementos da árvore.
	 * @param numElementos O número de elementos.
	 */
	void setNumElementos(int numElementos) {
		this->numElementos = numElementos;
	}

	/**
	 * Obter a raiz da árvore.
	 * @return A raiz da árvore.
	 */
	Nodo* getRaiz() {
		return raiz;
	}

	/**
	 * Definir a raiz da árvore.
	 * @param raiz A raiz da árvore.
	 */
	void setRaiz(Nodo *raiz) {
		this->raiz = raiz;
	}

	/**
	 * Adicionar um novo log ao arquivo de logs.
	 * @param tempoSeg O tempo da operação.
	 */
	void escreverLogArquivo( int tempoSeg ) {
		LeitorArquivo leitor;
		leitor.escreverLogOperacao(getArquivoLog(), getNumElementos(), tempoSeg);
	}

	/**
	 * Exibir os elementos da árvore em ordem.
	 */
	void exibirEmOrdem() {
		this->emOrdem(this->raiz);
	}

	/**
	 * Exibir os elementos da árvore em pré-ordem.
	 */
	void exibirPreOrdem() {
		this->preOrdem(this->raiz);
	}

	/**
	 * Exibir os elementos da árvore em pós-ordem.
	 */
	void exibirPosOrdem() {
		this->posOrdem(this->raiz);
	}

};

#endif
