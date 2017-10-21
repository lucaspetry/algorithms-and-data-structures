#ifndef IARVORE_HPP_
#define IARVORE_HPP_

#define interface class

#include <string>

/**
 * Interface de uma Árvore.
 */
template <typename Tipo>
interface IArvore {

public:
	/**
	 * Destrutor.
	 */
	virtual ~IArvore() { }

	/**
	 * Inserir um dado na árvore.
	 * @param dado O dado a ser inserido.
	 * @return O dado inserido.
	 */
	virtual Tipo* inserir( Tipo *dado ) = 0;

	/**
	 * Remover um dado na árvore.
	 * @param dado O dado a ser removido.
	 * @return O dado removido.
	 */
	virtual Tipo* remover( Tipo *dado ) = 0;

	/**
	 * Exibir os elementos da árvore em ordem.
	 */
	virtual void exibirEmOrdem() = 0;

	/**
	 * Exibir os elementos da árvore em pré-ordem.
	 */
	virtual void exibirPreOrdem() = 0;

	/**
	 * Exibir os elementos da árvore em pós-ordem.
	 */
	virtual void exibirPosOrdem() = 0;

	/**
	 * Verificar se a árvore está vazia.
	 * @return true se a árvore não possui nenhum elemento.
	 */
	virtual bool vazia() = 0;

	/**
	 * Obter o nome do arquivo de logs da árvore.
	 * @return O nome do arquivo.
	 */
	virtual std::string getArquivoLog() = 0;

};

#endif
