#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int codUser = -1;

#include "bdados.h"
#include "Projecto.h"
#include "Data.h"
#include "CSV.h"
#include "Calendario.h"

/**
 * Metodo para efectuar a listagem das tarefas do dia
 */
void lembrete()
{
	try
	{
		BDados *conexao = new BDados("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> list = conexao->listarLembrete(codUser);
		if(list.comprimento() > 0)
		{
			cout << "Tarefas de hoje:" << endl;
			cout << list;
		}
		delete (conexao);
	}
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}

}

/**
 * Metodo para listar o historico das informacoes, tarefas e projectos
 */
void listarHistorico()
{
		try
	{
		BDados *conexao = new BDados("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<HistoricoInformacao> list = conexao->listarHistoricoInformacao(codUser);
		cout << "----------------Historico de informacoes-------------------" << endl;
		cout << list;
		cin.get();
		Lista<HistoricoTarefa> list2 = conexao->listarHistoricoTarefa(codUser);
		cout << "----------------Historico de Tarefas-----------------------" << endl;
		cout << list2;
		cin.get();
		cout << "----------------Historico de Projectos---------------------" << endl;
		Lista<HistoricoProjecto> list3 = conexao->listarHistoricoProjecto(codUser);
		cout << list3;
		cin.get();

		delete (conexao);
	}
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * Metodo para eliminar o projecto
 */
void eliminaProjeto()
{
	try
	{
		BDados *conexao = new BDados("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Projecto> list = conexao->listarProjetosTodos(codUser);
		cout << list;
		cout << "Projeto a eliminar?" << endl;
		int codProjeto;
		cin >> codProjeto;
		conexao->eliminarProjeto(codUser, codProjeto);
		cout << "Projeto eliminado com sucesso" << endl;
		delete (conexao);
	}
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * Metodo para alterar o projecto
 */
void alteraProjeto()
{
	int codPro;
	int codestado=0, nivelimportancia=0;
	string datafim="", informacao="",titulo="",dataInicio="";


	char resposta='n';
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Projecto> list = conexao ->listarProjetosTodos(codUser);

		cout << list;
		cout << "**********************************************************************" << endl;
		cout << "Codigo do Projeto a alterar?" << endl;


		cin >> codPro;
		cout << "Pretende alterar o estado do Projeto? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Estado?" << endl;
			cin >> codestado;
		}
		cout << "Pretende alterar o nivel de importancia? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Nivel de importancia?" << endl;
			cin >> nivelimportancia;
		} 
		cout << "Pretende alterar a data de inicio? (S/N)" << endl;
		cin >> resposta;
		if(resposta =='S' || resposta == 's')
		{
			cout << "Data de Inicio?" << endl;
			cin >> dataInicio;
		}
		cout << "Pretende alterar a data de fim de Projeto? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Data de fim de tarefa?" << endl;
			fflush(stdin);
			getline(cin, datafim);
		}
		cout << "Pretende alterar a informacao? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Informacao?" << endl;
			fflush(stdin);
			getline(cin, informacao);
		}
		cout << "Pretende alterar o titulo? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Titulo?" << endl;
			fflush(stdin);
			getline(cin, titulo);
		}
		conexao->alterarProjeto(codPro, codestado, nivelimportancia, dataInicio, datafim, informacao, titulo);

		cout << "Alteracoes efetuadas com sucesso!" << endl;
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}

}


/**
 * associa informacao a uma tarefa, com base nos codigo de informacao e tarefa
 * pedidos ao utilizador
 */
void associarInfo(){
    // variaveis para guardar codigo de tarefa e codigo de informacao
    int codTar = 0;
    int codInf = 0;
    // inicio de try-catch para verificar conexao a  base de dados
    try
	{
        // conexao a base de dados
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
        // pede ao utilizador qual a tarefa que pretende associar
        cout << "Indique qual a tarefa que pretende associar:" << endl;
        // lista as tarefas (com base na variavel global)
        Lista<Tarefa> list = conexao ->listarTarefasTodas(codUser);
		cout << list;
        // guarda codigo tarefa na variavel respectiva
        cin >> codTar;
        // pede ao utilizador qual a informacao que pretende associar
        cout << "Indique qual a informaÃ§Ã£o que prentende associar" << endl;
        // lista informacao com base na variavel global
        Lista<Informacao> listInf = conexao ->listaInformacao(codUser);
        cout << listInf;
        cin >> codInf;
        // associa informacao
        conexao->associarInformacao(codInf, codTar);
        // termina ligacao
        delete(conexao);
	} // end try
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	} // end catch
}

/**
 * eliminar um contexto
 */
void eliminaContexto()
{
	int contexto;
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		cout << "Codigo do contexto a eliminar?" << endl;
		cin >> contexto;
		conexao -> eliminarContexto(contexto);
		
		
		
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * alterar um contexto
 */
void alterarContexto()
{
	string descricao;
	int contexto;
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		cout << "Codigo do contexto?" << endl;
		cin >> contexto;
		cout << "Descricao do contexto?" << endl;
		fflush(stdin);
		getline(cin, descricao);
		conexao -> alterarContexto(contexto, descricao);
		
		
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * criar um contexto
 */
void criarContexto()
{
	string descricao;
				try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		cout << "Descricao do contexto?" << endl;
		fflush(stdin);
		getline(cin, descricao);
		conexao -> criarContexto(descricao);
		cout << "Contexto criado com sucesso!!!" << endl;
		
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar os contextos
 */
void listaContextos()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Contexto> contextos= conexao -> listaContextos();
		cout << "Lista de Contextos:" << endl;
		cout << contextos;
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * remover uma delegacao
 */
void removerDelegacao()
{
	try
	{
		int tarefa;
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		cout << "Tarefa a remover delegacao?" << endl;
		cin >> tarefa;
		conexao->removerDelegacao(codUser, tarefa);
		delete(conexao);
		
		
		
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * alterar uma delegacao
 */
void alterarDelegacao()
{
	try
	{
		int cod, tarefa;
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		cout << "Tarefa a alterar delegacao?" << endl;
		cin >> tarefa;
		
		cout << "Utilizador a delegar? " << endl;
		cin >> cod;
		conexao->delegarTarefa(codUser, tarefa, cod);
		delete(conexao);
		
		
		
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * delegar uma tarefa
 */
void delegarTarefa()
{
	try
	{
		int cod, tarefa;
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		cout << "Tarefa para delegar?" << endl;
		cin >> tarefa;
		
		cout << "Utilizador a delegar? " << endl;
		cin >> cod;
		conexao->delegarTarefa(codUser, tarefa, cod);
		delete(conexao);
		
		
		
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar as tarefas delegadas
 */
void listarTarefasDelegadas()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> verTarefasDelegadas(codUser);
		cout << "Tarefas delegadas:" << endl;
		cout << tarefas;
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * associar um nivel a uma tarefa
 */
void associaTarefaNivel()
{
	try
	{
		int nivel, tarefa;
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		cout << "Tarefa para associar nivel?" << endl;
		cin >> tarefa;
		do{
		cout << "Nivel a associar? Introduza um numero entre 1 e 5!!! " << endl;
		cin >> nivel;
		if(nivel <1 || nivel > 5)
			cout << "Nivel invalido!!!" << endl;
		else
			conexao->associarTarefaNivel(codUser, tarefa, nivel);
		delete(conexao);
		}while(nivel <1 || nivel >5);
		
		
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * ordenar uma tarefa por contexto
 */
void ordenaTarefaContexto()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> ordenarTarefasContexto(codUser);
		cout << "Tarefas ordenadas por contexto:" << endl;
		cout << tarefas;
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * ordenar uma tarefa pela estimativa
 */
void ordenarTarefaEstimativa()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> taref= conexao -> ordenarTarefasEstimativa(codUser);
		cout << "Tarefas ordenadas por estimativa de tempo:" << endl;
		cout << taref;
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * ordenar tarefas por prioridade
 */
void ordenarTarefasPrioridade()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> ordenarPrioridade(codUser);
		cout << "Tarefas ordenadas por prioridade:" << endl;
		cout << tarefas;
		
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * eliminar uma tarefa
 */
void eliminaTarefa()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> listarTarefasTodas(codUser);
		cout << tarefas;
		cout << "Tarefa a eliminar? " << endl;
		int codtarefa;
		cin >> codtarefa;
		conexao->eliminarTarefa(codUser, codtarefa);
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * associar uma duracao a uma tarefa
 */
void associaDuracao()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> listarTarefasPorRealizar(codUser);
		cout << tarefas;
		cout << "Tarefa para associar duracao? " << endl;
		int resposta, duracao;
		cin >> resposta;
		cout << "Duracao?" << endl;
		cin >> duracao;
		conexao->associarDuracao(codUser, resposta, duracao);
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * marcar tarefa como realizada
 */
void realizaTarefa()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefas= conexao -> listarTarefasPorRealizar(codUser);
		cout << tarefas;
		cout << "Tarefa a marcar como realizada? " << endl;
		int resposta;
		cin >> resposta;
		conexao->realizarTarefa(codUser, resposta);
		
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar as tarefas realizadas
 */
void listarTarefasRealizadas()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefasrealizadas= conexao -> listarTarefasRealizadas(codUser);
		cout << tarefasrealizadas;
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar as tarefas por realizar
 */
void listarTarefasPorRealizar()
{
	
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> tarefasporrealizar= conexao -> listarTarefasPorRealizar(codUser);
		cout << tarefasporrealizar;
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * inserir informacao
 */
void inserirInfo()
{
	string info;
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		cout << "Inserir descricao da informacao" << endl;
		fflush(stdin);
		getline(cin, info);
		conexao -> inserirInfo(codUser, info);
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * alterar informacao
 */
void alteraInformacao()
{
	int codinfo;
	string descricao;
	
	char resposta='n';
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Informacao> list=conexao->listaInformacao(codUser);	
		cout << list;
		cout << "Codigo da informacao?" << endl;
		cin >> codinfo;
		cout << "Nova descricao?" << endl;
		fflush(stdin);
		getline(cin, descricao);
		conexao->alterarInformacao(codinfo,descricao);
		
	
		delete(conexao);
	} 

	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * alterar tarefa
 */
void alteraTarefa()
{
	int codTar;
	int codestado=0, nivelimportancia=0, duracao=0, coddependente=0, delegado=0;
	string datafim="", dataestimada="",informacao="",titulo="",tipo="", dataInicio="";

	char resposta='n';
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> list = conexao ->listarTarefasTodas(codUser);
	
		
		cout << list;
		cout << "**********************************************************************" << endl;
		cout << "Codigo da Tarefa a alterar?" << endl;
		
		cin >> codTar;
		cout << "Pretende alterar o estado da tarefa? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Estado?" << endl;
			cin >> codestado;
		}
		cout << "Pretende alterar o nivel de importancia? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Nivel de importancia?" << endl;
			cin >> nivelimportancia;
		}
		cout << "Pretende alterar a data de inicio? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S' || resposta == 's')
		{
			cout << "Data Inicio?" << endl;
			fflush(stdin);
			getline(cin, dataInicio);
		}
		cout << "Pretende alterar a duracao? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Duracao?" << endl;
			cin >> duracao;
		}
			cout << "Pretende alterar a dependencia? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Dependencia?" << endl;
			cin >> coddependente;
		}
		cout << "Pretende alterar o estado delegado? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Nova delegacao?" << endl;
			cin >> delegado;
		}
		cout << "Pretende alterar a data de fim de tarefa? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Data de fim de tarefa?" << endl;
			fflush(stdin);
			getline(cin, datafim);
			
		}
		cout << "Pretende alterar a data estimada? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Data estimada?" << endl;
				fflush(stdin);
			getline(cin, dataestimada);
		
		}
		cout << "Pretende alterar a informacao? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Informacao?" << endl;
				fflush(stdin);
			getline(cin, informacao);
			
		}
		cout << "Pretende alterar o titulo? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Titulo?" << endl;
				fflush(stdin);
			getline(cin, titulo);
		}
		cout << "Pretende alterar o tipo da tarefa? (S/N) " << endl;
		cin >> resposta;
		if(resposta=='S'|| resposta=='s')
		{
			cout << "Tipo?" << endl;
				fflush(stdin);
			getline(cin, tipo);
		}
		conexao->alterarTarefa(codTar, codestado, nivelimportancia, dataInicio, duracao,coddependente,delegado,datafim,dataestimada,informacao,titulo,tipo);
		
		
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar tarefas
 */
void listarTarefas()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Tarefa> list = conexao ->listarTarefasTodas(codUser);
		cout << list;
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * listar os projectos
 */
void listarProjetos()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Projecto> list = conexao ->listarProjetosTodos(codUser);
		cout << list;
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * inserir uma tarefa
 */
void inserirTarefa()
{
	int nivelImportancia;
	int duracao;
	string dataInicio;
	string informacao;
	string titulo;
	string tipo;
	string dataEstimada;
	char opc;

	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		int codTarefa, codInfo;
		char opcao = 's';
		
		cout << "Inserir nivel de importancia da tarefa" << endl;
		cin >> nivelImportancia;
		cout << "Deseja inserir uma data de inicio?(s/n)" << endl;
		cin >> opc;
		if(opc == 's' || opc == 'S')
		{
			cout << "Insira a data de inicio" << endl;
			cin >> dataInicio;
		}else
			dataInicio = "";
		cout << "Inserir informacao" << endl;
		fflush(stdin);
		getline(cin, informacao);
		cout << "Insira a data estimada (AA.MM.DD)" << endl;
		fflush(stdin);
		getline(cin, dataEstimada);
		cout << "Insira a duracao" << endl;
		cin >> duracao;
		cout << "Insira o tipo" << endl;
		fflush(stdin);
		getline(cin, tipo);
		cout << "Insira o titulo" << endl;
		fflush(stdin);
		getline(cin, titulo);
		conexao -> inserirTarefa(nivelImportancia, dataInicio, informacao, dataEstimada, duracao, tipo, titulo, NULL, codUser);
		codTarefa = conexao->ultimaTarefa(codUser);
		while(opcao == 's' || opcao == 'S')
		{
			Lista<Informacao> list = conexao->listaInfoSemTarefa(codUser);
			cout << list;
			cout << "Quer associar alguma informacao listada?" << endl;
			cout << "Para criar nova informacao insira -1" << endl;
			cin >> codInfo;
			if(codInfo == -1)
			{
				inserirInfo();
				codInfo = conexao->ultimaInfo(codUser);
			}	
			conexao->associarInformacao(codTarefa, codInfo);
			cout << "Deseja inserir mais informacao? (S/N)" << endl;
			cin >> opcao;
		}
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * Metodo para nao mostrar a password
 * @param get password nao-encriptada
 */
void getPassword(string &get)
{
	get.erase();
	char key;

	do
	{
		key = getch();

		switch (key)
		{
		case '\b': //backspace pressionado
			if(get.length() > 0)
			{
				get.erase(get.length() - 1, 1);
				//apaga o ultimo carater na password
				cout << '\b' << " " << '\b';
			}

			break;

		default:
			if(key > 31 && key < 127) 
			{
				get.push_back(key);
				cout << "*";
			}
		}
	} while(key != '\r'); //sai se o enter e pressionado
	cout << endl;
}

/**
 * Metodo para verificar o login de um utilizador
 */
void login()
{
	try 
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		cout << "Nome de Utilizador?\nPara sair escreva sair" << endl;
		string user;
		getline(cin, user);
		if(user != "sair"){
			cout << "Pass?" << endl;
			string pass;
			getPassword(pass);
			codUser = conexao -> login(user, pass);
			delete(conexao);
		}
		else
		{
			codUser = -2;
		}
	}
	catch (SQLException erro) 
	{
		cerr << "Erro: " << erro.getMessage () << endl;
	}
}

/**
 * listar informacao
 */
void listarInfo()
{
	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		Lista<Informacao> list = conexao ->listaInformacao(codUser);
		cout << list;
		delete(conexao);
	} 
	catch(SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * inserir um projecto
 */
void inserirProjeto()
{
	int nivelImportancia;
	string dataInicio;
	string dataFim;
	string informacao;
	string nome;
	int codEstado;
	char resposta = 'n';

	try
	{
		BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
		
		int codProjeto, codTarefa;
		char opcao = 's';
		

		cout << "Inserir nivel de importancia do projeto" << endl;
		cin >> nivelImportancia;
		cout << "Deseja inserir uma data de inicio? (S/N) " << endl;
		cin >> resposta;
		if(resposta == 's' || resposta == 'S')
		{
			cout << "Inserir Data de Inicio(AA.MM.DD)" << endl;
			cin >> dataInicio;
		}else
			dataInicio="";
		cout << "Inserir informacao" << endl;
		fflush(stdin);
		getline(cin, informacao);
		cout << "Insira a data de fim (AA.MM.DD)" << endl;
		fflush(stdin);
		getline(cin, dataFim);
		cout << "Insira o estado" << endl;
		cin >> codEstado;
		cout << "Insira o nome" << endl;
		fflush(stdin);
		getline(cin, nome);
		conexao -> inserirProjeto(codUser, nivelImportancia, dataInicio, dataFim, informacao, nome, codEstado);
		codProjeto = conexao->ultimoProjeto(codUser);
		
		while(opcao == 's' || opcao == 'S')
		{
			Lista<Tarefa> list = conexao->listaTarefaSemProjecto(codUser);
			cout << list;
			cout << "Quer associar alguma tarefa listada?" << endl;
			cout << "Para criar nova tarefa insira -1" << endl;
			cin >> codTarefa;
			
			if(codTarefa == -1)
			{
				inserirTarefa();
				codTarefa = conexao->ultimaTarefa(codUser);
			}
			conexao->associarTarefa(codTarefa, codProjeto);
			cout << "Deseja inserir mais tarefas? (S/N)" << endl;
			cin >> opcao;
		}
		delete(conexao);
	}
	catch (SQLException erro)
	{
		cerr << "Erro: " << erro.getMessage() << endl;
	}
}

/**
 * Submenu de dependencias
 */
void menuDependencias()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Dependencias                            *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Criar dependencias                          *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 2:
					sair=true;
					break;

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * Submenu de duracao de tarefa
 */
void menuDuracaoTarefa()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Duracao da tarefa                       *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Calcular estimativa                         *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu do historico de tarefas
 */
void menuHistoricoTarefas()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Consultar historico de tarefas          *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Visualizar historico                        *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					listarHistorico();
					sair=true;
					break;
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para editar contextos
 */
void menuEditarContextos()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Editar Contextos                        *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Adicionar Contexto                          *\n";
				cout << "*        2 - Alterar Contexto                            *\n";
				cout << "*        3 - Remover Contexto                            *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					criarContexto();
					sair=true;
					break;
				case 2:
					alterarContexto();
					sair=true;
					break;
				case 3:
					eliminaContexto();
					sair=true;
					break;

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu de contextos
 */
void menuContextoTarefas()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Contexto de tarefas                     *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Consultar lista de Contextos                *\n";
				cout << "*        2 - Editar contextos                            *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					listaContextos();
					sair=true;
					break;
				case 2:
					menuEditarContextos();
					sair=true;
					break;
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu de referencias
 */
void menuReferencias()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "***********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******             Referencias                     *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Criar referencias                           *\n";
				cout << "*        2 - Anexar documento                            *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 2:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para deferir tarefas
 */
void menuDeferirTarefa()
{
			
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Deferir tarefa                          *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Definir datas                               *\n";
				cout << "*        2 - Criar lembrete                              *\n";
				cout << "*        3 - Associar a calendario                       *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 2:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 3:
						Calendario *calendario;
					calendario->exportar("calendario",codUser);
					sair=true;
					break;
				

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para partilha em cloud
 */
void menuPartilhar()
{
		
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "***********************************************************" << endl;
				cout << "******                                              *******" << endl;
				cout << "******     Partilhar na cloud                       *******" << endl;
				cout << "******                                              *******" << endl;
				cout << "***********************************************************" << endl;
				cout << "*     Menu:                                               *\n" ;
				cout << "*        1 - Definir grau visibilidade                    *\n";
				cout << "*        2 - Encriptar                                    *\n";
				cout << "*        0 - Menu anterior                                *\n" ;
				cout << "*---------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                    *\n";
				cout << "*                                                         *" << endl;
				cout << "*                                                         *" << endl;
				cout << "***********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					
					sair=true;
					break;
				case 2:
					sair=true;
					break;
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para tarefas delegadas
 */
void menuTarefasDelegadas()
{
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "***********************************************************" << endl;
				cout << "******                                              *******" << endl;
				cout << "******         Tarefas Delegadas                    *******" << endl;
				cout << "******                                              *******" << endl;
				cout << "***********************************************************" << endl;
				cout << "*     Menu:                                               *\n" ;
				cout << "*        1 - Ver tarefas delegadas                        *\n";
				cout << "*        2 - Delegar tarefa                               *\n";
				cout << "*        3 - Alterar delegacao                            *\n";
				cout << "*        4 - Remover delegacao                            *\n";
				cout << "*        5 - Partilhar na cloud                           *\n";
				cout << "*        0 - Menu anterior                                *\n" ;
				cout << "*---------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                    *\n";
				cout << "*                                                         *" << endl;
				cout << "*                                                         *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					listarTarefasDelegadas();
					sair=true;
					break;
				case 2:
					delegarTarefa();
					sair=true;
					break;
				case 3:
					alterarDelegacao();
					sair=true;
					break;
				case 4:
					removerDelegacao();
					sair=true;
					break;
				case 5:
					menuPartilhar();
					sair=true;
					break;
					
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para as prioridades de tarefas
 */
void menuPrioridadeTarefa()
{
	
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******         Prioridades de tarefas              *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Atribuir prioridade                         *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					associaTarefaNivel();
					sair=true;
					break;
			
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
	}
}

/**
 * submenu para a informacao
 */
void menuInformacao()
{
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**************************************************************" << endl;
				cout << "******                                                 *******" << endl;
				cout << "******          Menu Informacao                        *******" << endl;
				cout << "******                                                 *******" << endl;
				cout << "**************************************************************" << endl;
				cout << "*     Menu:                                                  *\n" ;
				cout << "*        1 - Inserir Informacao                              *\n";
				cout << "*        2 - Listar Informacao                               *\n" ;
				cout << "*        3 - Alterar Informacao                              *\n";
				cout << "*        4 - Associar Informacao                              *\n";
				cout << "*        0 - Menu Anterior                                   *\n" ;
				cout << "*------------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                       *\n";
				cout << "*                                                            *" << endl;
				cout << "*                                                            *" << endl;
				cout << "**************************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					inserirInfo();
					sair=true;
					break;
				case 2:
					listarInfo();
					sair=true;
					break;
                case 4:
                    associarInfo();
                    sair = true;
                    break;
				case 3:
					alteraInformacao();
					sair=true;
					break;
			
				case 0:
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		
	}
}

/**
* submenu para a listagem ordenada
*/
void menuCriterioOrdenacao()
{
		
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******         Criterio de ordenacao               *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Ordenar por prioridade                      *\n";
				cout << "*        2 - Ordenar por estimativa de tempo             *\n";
				cout << "*        3 - Ordenar por contexto                        *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					ordenarTarefasPrioridade();
					sair=true;
					break;
				case 2:
					ordenarTarefaEstimativa();
					sair=true;
					break;
				case 3:
					ordenaTarefaContexto();
					sair=true;
					break;
				case 0:
				
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
	}
}

/**
 * submenu para a listagem de tarefas
 */
void menuListarTarefas()
{
	
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******          Listar Tarefas                     *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Ver todas as tarefas                        *\n";
				cout << "*        2 - Ver tarefas realizadas                      *\n" ;
				cout << "*        3 - Ver tarefas por realizar                    *\n" ;
				cout << "*        4 - Marcar tarefa como realizada                *\n" ;
				cout << "*        5 - Associar duracao                            *\n" ;
				cout << "*        6 - Alterar criterio ordenacao                  *\n" ;
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					listarTarefas();
					sair=true;
					break;
				case 2:
					listarTarefasRealizadas();
					sair=true;
					break;
				case 3:
					listarTarefasPorRealizar();
					sair=true;
					break;
				case 4:
					realizaTarefa();
					sair =true;
					break;
				case 5:
					associaDuracao();
					sair=true;
					break;
			
				case 6: 
					menuCriterioOrdenacao();
					sair=true;
					break;
				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
	}
}

/**
 * submenu para as tarefas
 */
void menuTarefas()
{
	bool sair=false;
	int op=1;
	while (!sair){
				cout << endl;
				cout << endl;
				cout << "**********************************************************" << endl;
				cout << "*******                                            *******" << endl;
				cout << "*******         Menu Tarefas                       *******" << endl;
				cout << "*******                                            *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Criar Tarefa                                *\n";
				cout << "*        2 - Alterar Tarefa                              *\n" ;
				cout << "*        3 - Converter tarefa para projecto              *\n" ;
				cout << "*        4 - Listar tarefas                              *\n" ;
				cout << "*        5 - Eliminar Tarefa                             *\n" ;
				cout << "*        6 - Marcar tarefa como 'algum dia'              *\n" ;
				cout << "*        7 - Tarefas Delegadas                           *\n" ;
				cout << "*        8 - Deferir tarefa                              *\n" ;
				cout << "*        9 - Prioridades de tarefas                      *\n" ;
				cout << "*        10 - Referencias                                *\n" ;
				cout << "*        11 - Contexto de tarefas                        *\n" ;
				cout << "*        12 - Consultar historico de tarefas             *\n" ;
				cout << "*        13 - Duracao de tarefas                         *\n" ;
				cout << "*        14 - Dependencias                               *\n" ;
				cout << "*        15 - Importar tarefas                           *\n" ;
				cout << "*        16 - Exportar tarefas                           *\n" ;
				cout << "*        17 - Adicionar notas                            *\n" ;
				cout << "*        0 - Menu Anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					inserirTarefa();
					sair=true;
					break;
				case 2:
				    alteraTarefa();
					sair=true;
					break;
				case 3:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;

				case 4:
					menuListarTarefas();
					sair=true;
					break;
				case 5:
					eliminaTarefa();
					sair=true;
					break;
				case 6:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 7:
					menuTarefasDelegadas();
					sair=true;
					break;
				case 8:
					menuDeferirTarefa();
					sair=true;
					break;
				case 9:
					menuPrioridadeTarefa();
					sair=true;
					false;
				case 10:
					menuReferencias();
					sair=true;
					break;
				case 11:
					menuContextoTarefas();
					sair=true;
					break;
				case 12:
					menuHistoricoTarefas();
					sair=true;
					break;
				case 13:
					menuDuracaoTarefa();
					sair=true;
					break;
				case 14:
					menuDependencias();
					sair=true;
					break;
				case 15:
					CSV csv;
					csv.importarTarefas("tarefas", codUser);
					sair=true;
					break;
				case 16:
					csv.exportarTarefas("tarefas", codUser);
					sair=true;
					break;
				case 17:
					sair=true;
					break;
				case 0:
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
			break;}
}

/**
 * submenu para as dependencias do projecto
 */
void menuDependenciasProjecto()
{
				
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******     Dependencias                            *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Visualizar dependencias de um projeto       *\n";
				cout << "*        2 - Visualizar dependencias entre projetos      *\n";
				cout << "*        3 - Associar a calendario                       *\n";
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 2:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 3:
					Calendario *calendario;
					calendario->exportar("calendario",codUser);
					sair=true;
					break;

				case 0:
					
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
						
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				
		break;
			}
}

/**
 * submenu para os projectos
 */
void menuProjetos()
{

	int op;
	bool sair=false;
	

	while (!sair){
				cout << "**********************************************************" << endl;
				cout << "******                                             *******" << endl;
				cout << "******          Menu Projectos                     *******" << endl;
				cout << "******                                             *******" << endl;
				cout << "**********************************************************" << endl;
				cout << "*     Menu:                                              *\n" ;
				cout << "*        1 - Criar Projecto                              *\n";
				cout << "*        2 - Editar projecto                             *\n" ;
				cout << "*        3 - Eliminar Projecto                           *\n" ;
				cout << "*        4 - Listar Projectos                            *\n" ;
				cout << "*        5 - Converter para tarefa                       *\n" ;
				cout << "*        6 - Prioridades de tarefas                      *\n" ;
				cout << "*        7 - Dependencias                                *\n" ;
				cout << "*        0 - Menu anterior                               *\n" ;
				cout << "*--------------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                   *\n";
				cout << "*                                                        *" << endl;
				cout << "*                                                        *" << endl;
				cout << "**********************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					inserirProjeto();
					sair=true;
					break;
				case 2:
					alteraProjeto();
					sair=true;
					break;
				case 3:
					eliminaProjeto();
					sair=true;
					break;
				case 4:
					listarProjetos();
					sair=true;
					break;
				case 5:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 6:
					menuPrioridadeTarefa();
					sair=true;
					break;
				case 7:
					menuDependenciasProjecto();
					sair=true;
					break;

				case 0:
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
			break;
	}
}

/**
 * submenu para a sincronizacao
 */
void menuSincronizar()
{
	
	int op;
	bool sair=false;
	

	while (!sair){
				cout << "*******************************************************" << endl;
				cout << "******                                          *******" << endl;
				cout << "******          Menu Sincronizar                *******" << endl;
				cout << "******                                          *******" << endl;
				cout << "*******************************************************" << endl;
				cout << "*     Menu:                                           *\n" ;
				cout << "*        1 - Sincronizar com servidor                 *\n";
				cout << "*        2 - Integrar com outra lista de tarefas      *\n" ;
				cout << "*        0 - Menu anterior                            *\n" ;
				cout << "*-----------------------------------------------------*" << endl;
				cout << "*     Escolha a opcao:                                *\n";
				cout << "*                                                     *" << endl;
				cout << "*                                                     *" << endl;
				cout << "*******************************************************" << endl;
				cin >> op;
				switch(op){
				case 1:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 2:
					cout << "Funcao indisponivel!!!" << endl;
					sair=true;
					break;
				case 0:
					cout << "A sair..." << endl;
					sair=true;
					break;
				default:
					cout << "A sair..." << endl;
					sair=true;
					break;
				}
				break;
	}
}

/**
 * Menu principal do programa
 */
void menu()
{   
	bool sair=false;
	int op = 1;
	while(!sair)
	{	
		cout << endl;
		cout << endl;
		cout << "**************************************************************" << endl;
		cout << "******                                                 *******" << endl;
		cout << "******          GESTAO PESSOAL                         *******" << endl;
		cout << "******                                                 *******" << endl;
		cout << "**************************************************************" << endl;
		cout << "*     Menu:                                                  *\n" ;
		cout << "*        1 - Informacao                                      *\n";
		cout << "*        2 - Tarefas                                         *\n" ;
		cout << "*        3 - Projectos                                       *\n" ;
		cout << "*        4 - Historico                                       *\n" ;
		cout << "*        5 - Sincronizar                                     *\n";
		cout << "*        6 - Importar CSV                                    *\n";
		cout << "*        7 - Exportar CSV                                    *\n";
		cout << "*        0 - Sair                                            *\n" ;
		cout << "*------------------------------------------------------------*" << endl;
		cout << "*     Escolha a opcao:                                       *\n";
		cout << "*                                                            *" << endl;
		cout << "*                                                            *" << endl;
		cout << "**************************************************************" << endl;
		
		
		cin >> op;

		switch(op)
		{
		case 1:
			
		menuInformacao();
		break;
		case 2:
			
			menuTarefas();
			
			break;
		case 3:
			menuProjetos();
			
			break;
		case 4:
			listarHistorico();
			break;
		case 5:
			menuSincronizar();
			break;
		case 6:
			CSV csv2;
			csv2.importarInformacoes("informacoes",codUser);
			csv2.importarTarefas("tarefas", codUser);
			csv2.importarTipos("tipos", codUser);
			csv2.importarNiveis("niveis", codUser);
			csv2.importarEstados("estados", codUser);
			csv2.importarContextos("contextos", codUser);
			csv2.importarTarefaContexto("tarefa_contexto", codUser);
			csv2.importarProjectos("projectos", codUser);
			csv2.importarUtilizadores("utilizadores", codUser);
			break;
		case 7:
			CSV csv;
			csv.exportarInformacoes("informacoes", codUser);
			csv.exportarContextos("contextos", codUser);
			csv.exportarTarefas("tarefas",codUser);
			csv.exportarNiveis("niveis",codUser);
			csv.exportarUtilizador("utilizadores",codUser);
			csv.exportarProjectos("projectos", codUser);
			csv.exportarTipos("tipos",codUser);
			csv.exportarEstados("estados", codUser);
			csv.exportarTarefaContexto("tarefa_contexto", codUser);
			break;
		case 0:
			sair=true;
			break;
		
		
		}
		
	}
}

/**
 * Metodo principal do programa
 * @return 0 caso o programa corra sem qualquer erro
 */
int main ()
{
	while(codUser == -1)
		login();
	if(codUser > 0)
	{
		lembrete();
		menu();
		
	}


	return 0;
}