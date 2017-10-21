#include "Menu.h"
#include <iostream>
#include <sstream>

using namespace std;

Menu::Menu() {
	dicionario = new Dicionario();
}

Menu::~Menu() {
	delete( dicionario );
}

void Menu::executar() {
	bool executar = true;
	while( executar ) {

		cout << ":: Dicionário ::\n" << endl
			 << "Neste dicionário você pode armazenar inteiros, números de "
			 << "ponto flutuante e textos. Selecione uma das opções abaixo:"<< endl
			 << "(1) Inserir um objeto." << endl
			 << "(2) Imprimir objeto a partir da chave." << endl
			 << "(3) Imprimir todas as chaves do dicionário." << endl
			 << "(4) Encerrar o aplicativo.\n" << endl
			 << "Opção: ";

		string opcao;
		int op = 0;
		getline( cin, opcao );
		cin.ignore(0);
		stringstream stream( opcao );
		std::cout << "\n";

		if( stream >> op && op <= 4 && op >= 1 ) {

			switch( op ) {

			case 1:
				this->inserirObjeto();
				break;
			case 2:
				this->imprimirObjeto();
				break;
			case 3:
				this->imprimirChaves();
				break;
			default:
				executar = false;
				cout << "O aplicativo será finalizado!" << endl;
			}

		} else {
			cout << "Opção inválida!\n" << endl;
		}

	}
}

void Menu::inserirObjeto() {
	string chave;
	TipoObjeto tipo;
	void *objeto;

	cout << "Inserção de Novo Objeto" << endl
		 << "Chave do objeto: ";

	getline( cin, chave );
	cin.ignore(0);

	bool tipoValido = false;

	while( !tipoValido ) {
		cout << "\nTipo do objeto (0 - Inteiro, 1 - Float, 2 - String): ";

		string tipoObj;
		cin >> tipoObj;
		cin.ignore( INT_MAX, '\n' );
		stringstream stream( tipoObj );
		int tipoInt;

		if( stream >> tipoInt && tipoInt >= 0 && tipoInt <= 2 ) {
			tipoValido = true;
			switch( tipoInt ) {
			case 1:
				tipo = INTEGER;
				break;
			case 2:
				tipo = FLOAT;
				break;
			default:
				tipo = STRING;
			}
		} else {
			cout << "\nTipo inválido!" << endl;
		}
	}

	cout << "\nObjeto: ";

	string dado;
	getline( cin, dado );
	cin.ignore(0);

}

void Menu::imprimirObjeto() {
	cout << "Digite a chave do objeto a ser impresso: ";

	string opcao;
	getline( cin, opcao );
	cin.ignore(0);
	std::cout << "\n";

	try {
		this->dicionario->imprimir( opcao.c_str() );
	} catch( int exc ) {
		if( exc == ERROCHAVEINVALIDA )
			cout << "Chave inválida!\n" << endl;
		else
			cout << "Objeto não encontrado!\n" << endl;
	}
}

void Menu::imprimirChaves() {
	if( this->dicionario->vazio() )
		cout << "O dicionário está vazio!\n" << endl;
	else
		this->dicionario->imprimirChaves();
}

