/**
*@author Vitor Hugo
*@date 11/01/2013 
*@file CSV.h 
*Classe responsavel por importacoes e exportacoes CSV.*/ 

#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;
#include "Tarefa.h"
#include "Projecto.h"
#include "Utilizador.h"
#include "Informacao.h"
#include "Contexto.h"
#include "Nivel.h"
#include "Bdados.h"
#include "Lista.h"

class CSV
{

private:
public:
	int  importarInformacoes(string nomeFicheiro, int codUser);
	int  importarContextos(string nomeFicheiro, int codUser);
	int  importarEstados(string nomeFicheiro, int codUser);
	int  importarNiveis(string nomeFicheiro, int codUser);
	int  importarProjectos(string nomeFicheiro, int codUser);
	int  importarTarefas(string nomeFicheiro, int codUser);
	int  importarTarefaContexto(string nomeFicheiro, int codUser);
	int  importarTipos(string nomeFicheiro, int codUser);
	int  importarUtilizadores(string nomeFicheiro, int codUser);

	int  exportarInformacoes(string nomeFicheiro, int codUser);
	int  exportarContextos(string nomeFicheiro, int codUser);
	int  exportarEstados(string nomeFicheiro, int codUser);
	int  exportarNiveis(string nomeFicheiro, int codUser);
	int  exportarProjectos(string nomeFicheiro, int codUser);
	int  exportarTarefas(string nomeFicheiro, int codUser);
	int  exportarTarefaContexto(string nomeFicheiro, int codUser);
	int  exportarTipos(string nomeFicheiro, int codUser);
	int  exportarUtilizador(string nomeFicheiro, int codUser);
	string contToString(Lista<int> cont);
	void exportAssemb(int codUser);
};
/**
 * Converte uma lista de numero de contextos numa string a ser exportada para csv
 * @param  cont lista de contextos a ser tratada
 * @return      retorna a lista de bits a ser exportada
 */
string CSV::contToString(Lista<int> cont)
{
	string ret;
	stringstream out;
	int contexto;

	cont.encontra(1, contexto);
	if(cont.comprimento() == 1)
	{
		for(int i=0;i<contexto-1;i++)
			out << 0;
		out << 1;
	}
	else
	{
		int contMaior, tmp;

		cont.encontra(2, contMaior);
		if(contMaior < contexto)
		{
			tmp = contMaior;
			contMaior = contexto;
			contexto = tmp;
		}
		for(int i=0; i<contMaior-1;i++)
			if(contexto == (i+1))
				out << 1;
			else
				out << 0;
		out << 1;
	}
	ret = out.str();

	return ret;
}

/**
 * Exporta uma lista de tarefas de um determinado utilizador para ser lida pela aplicacao movel. 
 * Formato: codigoTarefa, nomeTarefa, prioridade, contexto
 * @param codUser codigo do utilizador que pede a exportacao
 */
void CSV::exportAssemb(int codUser)
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> list = conexao ->listarTarefasTodas(codUser);
		Tarefa auxTarefa;
		string contextos;

		ofstream ficheiro("FX.csv");

		if(ficheiro.is_open())
		{
			for(int i = 1; i< list.comprimento(); i++)
			{
				list.encontra(i, auxTarefa);
				Lista<int> cont = conexao ->listarCodContextos(auxTarefa.getCodTarefa());
				if(cont.comprimento() > 0)
				{
					string contStr = contToString(cont);
					ficheiro << auxTarefa.getCodTarefa() << "," << auxTarefa.getTitulo() << "," << auxTarefa.getNivelImportancia() << "," << contStr << "\n";
				}
			}
			ficheiro.close();
		}
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}

}

/**
 * Metodo responsavel pela importacao de informacoes atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarInformacoes(string nomeFicheiro, int codUser)
{
	int codInformacao;
	int codTarefa;
	int codUtilizador;
	string linha;
	string _nomeFicheiro;
	stringstream out;
	string desc;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cInf(linha.substr(comeca,pos-comeca));
			char* aux = &cInf[0];
			codInformacao = atoi(aux); // guarda codInformacao

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cTar(linha.substr(comeca,pos-comeca));
			aux = &cTar[0];
			codTarefa = atoi(aux); // guarda codTarefa

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cUti(linha.substr(comeca,pos-comeca));
			aux = &cUti[0];
			codUtilizador = atoi(aux); // guarda codUtilizador

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string descricao(linha.substr(comeca,pos-comeca)); // guarda descricao
			desc = descricao;
			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string dataInsercao(linha.substr(comeca,pos-comeca)); //guarda a data de insercao

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao -> inserirInfoCompleta(codUser, desc, codTarefa);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de tarefas atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarTarefas(string nomeFicheiro, int codUser)
{
	int codTarefa;
	int codProjecto;
	int codEstado;
	int codUtilizador;
	int nivelImportancia;
	int duracao;
	int codDependente;
	int nContextos;
	int delegado;
	string dataCriacao;
	string dataFim;
	string dataEstimada;
	string informacao;
	string titulo;
	string tipo;
	string linha;
	string _nomeFicheiro;
	stringstream out;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cTar(linha.substr(comeca,pos-comeca));
			char* aux = &cTar[0];
			codTarefa = atoi(aux); // guarda codTarefa

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cPro(linha.substr(comeca,pos-comeca));
			aux = &cPro[0];
			codProjecto = atoi(aux); // guarda codProjecto

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cEst(linha.substr(comeca,pos-comeca));
			aux = &cEst[0];
			codEstado = atoi(aux); // guarda codEstado

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cUti(linha.substr(comeca,pos-comeca));
			aux = &cUti[0];
			codUtilizador = atoi(aux); // guarda codUtilizador

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cNiv(linha.substr(comeca,pos-comeca));
			aux = &cNiv[0];
			nivelImportancia = atoi(aux); // guarda nivelImportancia

			pos++;                                                                                                                                                                                                                                                                                                                                                                                                  
			comeca = pos;
			pos = linha.find(',',comeca);

			string cDura(linha.substr(comeca,pos-comeca));
			aux = &cDura[0];
			duracao = atoi(aux); // guarda duracao

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cDepe(linha.substr(comeca,pos-comeca));
			aux = &cDepe[0];
			codDependente = atoi(aux); // guarda codDependente

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cCont(linha.substr(comeca,pos-comeca));
			aux = &cCont[0];
			nContextos = atoi(aux); // guarda nContextos

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cDel(linha.substr(comeca,pos-comeca));
			aux = &cDel[0];
			delegado = atoi(aux); // guarda delegado

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cCriacao(linha.substr(comeca,pos-comeca));
			dataCriacao = cCriacao; // guarda dataCriacao

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cFim(linha.substr(comeca,pos-comeca));
			if (cFim == "---")
				dataFim = "NULL";
			else
				dataFim = cFim; // guarda dataFim

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cEsti(linha.substr(comeca,pos-comeca));
			if (cEsti == "---")
				dataEstimada = "NULL";
			else
				dataEstimada = cEsti; // guarda dataEstimada

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cInf(linha.substr(comeca,pos-comeca));
			informacao = cInf; // guarda informacao

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cTitulo(linha.substr(comeca,pos-comeca));
			titulo = cTitulo; // guarda titulo

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cTipo(linha.substr(comeca,pos-comeca));
			tipo = cTipo; // guarda tipo

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao -> inserirTarefaCompleta(codTarefa, codProjecto, codEstado, nivelImportancia, dataCriacao, dataFim, informacao, dataEstimada, duracao, tipo, titulo, codDependente, codUtilizador, nContextos, delegado);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}
	
	return 0;
}

/**
 * Metodo responsavel pela importacao de projectos atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarProjectos(string nomeFicheiro, int codUser)
{
	int codProjecto;
	int codEstado;
	int codUtilizador;
	int nivelImportancia;
	string dataCriacao;
	string dataFim;
	string informacao;
	string nome;
	string linha;
	string _nomeFicheiro;
	stringstream out;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cPro(linha.substr(comeca,pos-comeca));
			char* aux = &cPro[0];
			codProjecto = atoi(aux); // guarda codProjecto

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cEs(linha.substr(comeca,pos-comeca));
			aux = &cEs[0];
			codEstado = atoi(aux); // guarda codEstado

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cUt(linha.substr(comeca,pos-comeca));
			aux = &cUt[0];
			codUtilizador = atoi(aux); // guarda codUtilizador

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string Niv(linha.substr(comeca,pos-comeca));
			aux = &Niv[0];
			nivelImportancia = atoi(aux); // guarda nivelImportancia

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cCriacao(linha.substr(comeca,pos-comeca));
			dataCriacao = cCriacao; // guarda dataCriacao

			pos++;                                                                                                                                                                                                                                                                                                                                                                                                  
			comeca = pos;
			pos = linha.find(',',comeca);

			string cFim(linha.substr(comeca,pos-comeca));
			if (cFim == "---")
				dataFim = "NULL";
			else
			dataFim = cFim; // guarda dataFim

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cInf(linha.substr(comeca,pos-comeca));
			informacao = cInf; // guarda informacao

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cNome(linha.substr(comeca,pos-comeca));
			nome = cNome; // guarda nome

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao -> inserirProjetoCompleto(codProjecto, codEstado, codUtilizador, nivelImportancia, dataCriacao, dataFim, informacao, nome);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}
	
	return 0;
}

/**
 * Metodo responsavel pela importacao de tipos atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarTipos(string nomeFicheiro, int codUser)
{
	int codTipo;
	string linha;
	string _nomeFicheiro;
	stringstream out;
	string desc;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cTip(linha.substr(comeca,pos-comeca));
			char* aux = &cTip[0];
			codTipo = atoi(aux); // guarda codTipo

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string descricao(linha.substr(comeca,pos-comeca)); // guarda descricao
			desc = descricao;

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->inserirTipo(desc);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de niveis atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarNiveis(string nomeFicheiro, int codUser)
{
	int nivelImportancia;
	string linha;
	string _nomeFicheiro;
	stringstream out;
	string desc;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cImp(linha.substr(comeca,pos-comeca));
			char* aux = &cImp[0];
			nivelImportancia = atoi(aux); // guarda nivelImportancia

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string descricao(linha.substr(comeca,pos-comeca)); // guarda descricao
			desc = descricao;

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->inserirNivel(nivelImportancia,desc);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de estados atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarEstados(string nomeFicheiro, int codUser)
{
	int codEstado;
	string linha;
	string _nomeFicheiro;
	stringstream out;
	string desc;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cEs(linha.substr(comeca,pos-comeca));
			char* aux = &cEs[0];
			codEstado = atoi(aux); // guarda codEstado

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string descricao(linha.substr(comeca,pos-comeca)); // guarda descricao
			desc = descricao;

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->inserirEstado(desc);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de contextos atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarContextos(string nomeFicheiro, int codUser)
{
	int codContexto;
	string linha;
	string _nomeFicheiro;
	stringstream out;
	string desc;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cCon(linha.substr(comeca,pos-comeca));
			char* aux = &cCon[0];
			codContexto = atoi(aux); // guarda codContexto

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string descricao(linha.substr(comeca,pos-comeca)); // guarda descricao
			desc = descricao;

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->inserirContexto(desc);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de tarefa contexto atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarTarefaContexto(string nomeFicheiro, int codUser)
{
	int codTarefa;
	int codContexto;
	string linha;
	string _nomeFicheiro;
	stringstream out;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cTar(linha.substr(comeca,pos-comeca));
			char* aux = &cTar[0];
			codTarefa = atoi(aux); // guarda codTarefa

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cCon(linha.substr(comeca,pos-comeca));
			aux = &cCon[0];
			codContexto = atoi(aux); // guarda codContexto

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->inserirTarefaContexto(codTarefa, codContexto);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	
	return 0;
}

/**
 * Metodo responsavel pela importacao de utilizadores atraves de ficheiro em formato csv.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador.
 * @return              retorna 0 se importar com sucesso, caso contrario retorna -1.
 */
int CSV::importarUtilizadores(string nomeFicheiro, int codUser)
{
	int codUtilizador;
	int telefone;
	string nome;
	string login;
	string pass;
	string linha;
	string _nomeFicheiro;
	stringstream out;

	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();

	ifstream ficheiro(_nomeFicheiro); // abre o ficheiro

	if(!ficheiro)
	{
		cout << _nomeFicheiro << "nao existe!" << endl;
		return -1;
	}

	while(!ficheiro.eof()) // enquanto nao chega ao final do ficheiro
	{
		getline(ficheiro,linha,'\n'); // grava o conteudo da linha
		if(linha.size() > 0)
		{
			int  comeca = 0;
			int pos = linha.find(',',comeca);

			string cUti(linha.substr(comeca,pos-comeca));
			char* aux = &cUti[0];
			codUtilizador = atoi(aux); // guarda codUtilizador

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string n(linha.substr(comeca,pos-comeca)); // guarda nome
			nome = n;

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string cTel(linha.substr(comeca,pos-comeca));
			aux = &cTel[0];
			telefone = atoi(aux); // guarda telefone

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string lo(linha.substr(comeca,pos-comeca)); // guarda login
			login = lo;

			pos++;
			comeca = pos;
			pos = linha.find(',',comeca);

			string pa(linha.substr(comeca,pos-comeca)); // guarda pass
			pass = pa;

			pos++;

			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao -> inserirUtilizador(nome,telefone,login,pass);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}
		}
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de tarefas da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarTarefas(string nomeFicheiro, int codUser)
{
	
	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Tarefa auxTarefa;
	Tarefa *apTarefa = &auxTarefa;
	Lista<Tarefa> tarefas;
	string dataEstimada;
	string dataFim;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				tarefas = conexao ->listarTarefasTodas(codUser);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< tarefas.comprimento()+1; i++)
		{
			
			tarefas.encontra(i, auxTarefa);	

			if(apTarefa->getDataFim().getAno() != 1900)
				dataFim = apTarefa->getDataFim().toSQL();
			else
				dataFim = "---";
			if(apTarefa->getDataEstimada().getAno() != 1900)
				dataEstimada = apTarefa->getDataEstimada().toSQL();
			else
				dataEstimada = "---";

			ficheiro << apTarefa->getCodTarefa() << "," << apTarefa->getCodProjecto() << "," << apTarefa->getCodEstado() << "," << apTarefa->getCodUtilizador() << "," << apTarefa->getNivelImportancia() << "," << apTarefa->getDuracao() << "," << apTarefa->getCodDependente() << "," << apTarefa->getNContextos() << "," << apTarefa->getDelegado() << "," << apTarefa->getDataCriacao().toSQL() << "," << dataFim << "," << dataEstimada << "," << apTarefa->getInformacao() << "," << apTarefa->getTitulo()<< "," << apTarefa->getTipo() << "\n";	
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de informacoes da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarInformacoes(string nomeFicheiro, int codUser)
{
	
	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Informacao auxInfo;
	Informacao *apInfo = &auxInfo;
	Lista<Informacao> informacoes;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				informacoes = conexao ->listaInformacao(codUser);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< informacoes.comprimento()+1; i++)
		{
			
			informacoes.encontra(i, auxInfo);	

			ficheiro << apInfo->getCodInformacao() << "," << apInfo->getCodTarefa() << "," << apInfo->getCodUtilizador() << "," << apInfo->getDescricao() << "," << apInfo->getDataInsercao().toSQL() << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de contextos da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarContextos(string nomeFicheiro, int codUser)
{
	
	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Contexto auxCon;
	Contexto *apCon = &auxCon;
	Lista<Contexto> contextos;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				contextos = conexao ->listarContextos();
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< contextos.comprimento()+1; i++)
		{
			
			contextos.encontra(i, auxCon);	

			ficheiro << apCon->getCodContexto() << "," << apCon->getDescricao() << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de niveis da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarNiveis(string nomeFicheiro, int codUser)
{
	
	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Nivel auxNiv;
	Nivel *apNiv = &auxNiv;
	Lista<Nivel> niveis;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				niveis = conexao ->listarNiveis();
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< niveis.comprimento()+1; i++)
		{
			
			niveis.encontra(i, auxNiv);	

			ficheiro << apNiv->getNivelImportancia() << "," << apNiv->getDescricao() << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de utilizadores da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarUtilizador(string nomeFicheiro, int codUser)
{

	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Utilizador auxUti;
	Utilizador *apUti = &auxUti;
	Lista<Utilizador> utilizadores;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				utilizadores = conexao ->listarUtilizadores();
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< utilizadores.comprimento()+1; i++)
		{
			
			utilizadores.encontra(i, auxUti);	

			ficheiro << apUti->getCodUtilizador() << "," << apUti->getNome()  << "," << apUti->getTelefone()  << "," << apUti->getLogin()  << "," << apUti->getPass() << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de projectos da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarProjectos(string nomeFicheiro, int codUser)
{
	
	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	Projecto auxProjecto;
	Projecto *apProjecto = &auxProjecto;
	Lista<Projecto> projectos;
	string dataFim;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				projectos = conexao ->listarProjectos(codUser);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< projectos.comprimento()+1; i++)
		{
			
			projectos.encontra(i, auxProjecto);	

			if(apProjecto->getDataFim().getAno() != 1900)
				dataFim = apProjecto->getDataFim().toSQL();
			else
				dataFim = "---";

			ficheiro << apProjecto->getCodProjecto() << "," << apProjecto->getCodEstado() << "," << apProjecto->getCodUtilizador() << "," << apProjecto->getNivelImportancia() << "," << apProjecto->getDataCriacao().toSQL() << "," << dataFim << "," << apProjecto->getInformacao() << "," << apProjecto->getNome() << "\n";	
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de tipos da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarTipos(string nomeFicheiro, int codUser)
{

	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	int codigo;
	Lista<int> codigos;
	Lista<string> descricoes;
	Lista<int> *apCodigos = &codigos;
	Lista<string> *apDescricoes = &descricoes;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->listaTipos(apCodigos, apDescricoes);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< codigos.comprimento()+1; i++)
		{
			
			codigos.encontra(i, codigo);	
			descricoes.encontra(i, desc);

			ficheiro << codigo << "," << desc << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de estados da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarEstados(string nomeFicheiro, int codUser)
{

	string linha;
	string desc;
	string _nomeFicheiro;
	stringstream out;
	int codigo;
	Lista<int> codigos;
	Lista<string> descricoes;
	Lista<int> *apCodigos = &codigos;
	Lista<string> *apDescricoes = &descricoes;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->listaEstados(apCodigos, apDescricoes);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< codigos.comprimento()+1; i++)
		{
			
			codigos.encontra(i, codigo);	
			descricoes.encontra(i, desc);

			ficheiro << codigo << "," << desc << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

/**
 * Metodo responsavel pela exportacao de tarefa contexto da base de dados para sql.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilziador.
 * @return              retorna 0 se exportar com sucesso, caso contrario retorna -1.
 */
int CSV::exportarTarefaContexto(string nomeFicheiro, int codUser)
{

	string linha;
	string _nomeFicheiro;
	stringstream out;
	int codigoTarefa;
	int codigoContexto;
	Lista<int> codigosTarefa;
	Lista<int> codigosContexto;
	Lista<int> *apCTarefa = &codigosTarefa;
	Lista<int> *apCContexto = &codigosContexto;


	out << nomeFicheiro << ".csv";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				conexao ->listaTarefaContexto(apCTarefa, apCContexto);
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		for(int i = 1; i< codigosTarefa.comprimento()+1; i++)
		{
			
			codigosTarefa.encontra(i, codigoTarefa);	
			codigosContexto.encontra(i, codigoContexto);

			ficheiro << codigoTarefa << "," << codigoContexto << "\n";
		}
		ficheiro.close();
	}

	return 0;
}

#endif
