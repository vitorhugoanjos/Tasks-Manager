/**
 * Classe que contem todos os metodos de interaccao com a base de dados
 * @author 	Andre Silva
 * @date 	07/01/2013
 * @file	BDados.h
 */

#ifndef BDados_
#define BDados_
#include <iostream>
#include <iomanip>
#include <occi.h>
#include "HistoricoProjecto.h"
#include "HistoricoTarefa.h"
#include "HistoricoInformacao.h"
#include "Lista.h"
using namespace oracle::occi;
#include "Informacao.h"
#include "Tarefa.h"
#include "Utilizador.h"
#include "Nivel.h"
#include "Projecto.h"
#include <sstream>
#include <string>

class BDados
{
private:
	Environment *env;
	Connection *ligacao;
	Statement *instrucao;
public:
	BDados(string user, string passwd, string db);
	~ BDados();
	Lista<Informacao> listaInformacao(int user);
	Lista<HistoricoProjecto> listaHistoricoProjecto(int user);
	Lista<HistoricoTarefa> listaHistoricoTarefa(int user);
	Lista<HistoricoInformacao> listaHistoricoInformacao(int user);
	Lista<Tarefa> listarTarefasTodas(int codUser);
	Lista<Contexto> listarContextos();
	Lista<Nivel> listarNiveis();
	Lista<Utilizador> listarUtilizadores();
	Lista<Projecto> listarProjectos(int codUser);
	void listaTipos(Lista<int> *codigos, Lista<string> *descricoes);
	void listaEstados(Lista<int> *codigos, Lista<string> *descricoes);
	void listaTarefaContexto(Lista<int> *codigoTarefa, Lista<int> *codigoContexto);
	int login(string user, string pass);
	void inserirInfo(int codUser, string info);
	void inserirInfoCompleta(int codUser, string info, int codTarefa);
	Data convertData(string date);
	void inserirUtilizador(string nome, int telefone, string login, string pass);
	void inserirProjetoCompleto(int codProjecto,int codEstado,int codUtilizador,int nivelImportancia, string dataCriacao, string dataFim, string informacao, string nome);
	void inserirTarefaContexto(int codTarefa, int codContexto);
	void inserirContexto(string desc);
	void inserirEstado(string desc);
	void inserirTipo(string descricao);
	void inserirNivel(int nivelImportancia, string desc);
	void inserirTarefa(int nivelImportancia, string dataInicio, string informacao, string dataEstimada, int duracao, string tipo, string titulo, int tarefaDependente, int codUtilizador);
	void inserirTarefaCompleta(int codTarefa, int codProjecto, int codEstado, int nivelImportancia, string dataCriacao, string dataFim, string informacao, string dataEstimada, int duracao, string tipo, string titulo, int dependente, int codUtilizador, int nContexto, int delegado);
	bool associarInformacao(int codTarefa, int codInformacao);
	bool podeAssociarInfo(int codInformacao);
    void inserirData(string data, string tabela, string campo);
	int ultimaTarefa(int codUser);
	Lista<Informacao> listaInfoSemTarefa(int codUser);
	int ultimaInfo(int codUser);
	void alterarInformacao(int codinformacao, string descricao);
	void inserirProjeto(int codUser, int nivelImportancia, string dataInicio, string dataFim, string informacao, string nome, int codEstado);
	int ultimoProjeto(int codUser);
	Lista<Tarefa> listaTarefaSemProjecto(int codUser);
	bool associarTarefa(int codTarefa, int codProjeto);
	bool podeAssociarTare(int codTarefa);
	Lista<int> listarCodContextos(int codTarefa);
	Lista<Projecto> listarProjetosTodos(int codUser);
	void eliminarProjeto(int codUser, int codProjeto);
	void alterarProjeto(int codPro, int codestado, int nivelimportancia, string dataInicio,string datafim,string informacao,string titulo);
	Lista<Tarefa> listarTarefasRealizadas(int codUser);
	Lista<Tarefa> listarTarefasPorRealizar(int codUser);
	void realizarTarefa(int codUser, int codtarefa);
	void associarDuracao(int codUser, int codTarefa, int duracao);
	void eliminarTarefa(int codUser, int codTarefa);
	Lista<Tarefa> ordenarPrioridade(int codUser);
	Lista<Tarefa> ordenarTarefasEstimativa(int codUser);
	Lista<Tarefa> ordenarTarefasContexto(int codUser);
	void associarTarefaNivel(int codUser, int codTarefa, int nivel);
	Lista<Tarefa> verTarefasDelegadas(int codUser);
	void delegarTarefa(int codUser, int codTarefa, int codUtil);
	void alterarDelegacao(int codUser, int codTarefa, int codUtil);
	void removerDelegacao(int codUser, int codTarefa);
	Lista<Contexto> listaContextos();
	void criarContexto(string descricao);
	void alterarContexto(int codContexto, string descricao);
	void eliminarContexto(int codContexto);
	void associarTarefaContexto(int codContexto, int codTarefa);
	string getEstado(int codEstado);
	string getUser(int codUser);
	void alterarTarefa(int codTare, int codestado, int nivelimportancia, string dataInicio, int duracao, int coddependente, int delegado, string datafim, string dataestimada, string info, string titulo, string tipo);
	Lista<Tarefa> listarLembrete(int codUser);
	Lista<HistoricoInformacao> listarHistoricoInformacao(int codUser);
	Lista<HistoricoTarefa> listarHistoricoTarefa(int codUser);
	Lista<HistoricoProjecto> listarHistoricoProjecto(int codUser);
};


/**
 * construtor de um objecto do tipo BDados que permite a ligacao a base de dados
 * @param	user 	string correspondente ao nome de utilizador
 * @param	passwd 	string correspondente à palavra-passe do utilizador
 * @param	db 		endereço da base de dados
 */
BDados::BDados(string user, string passwd, string db)
{
	env = Environment::createEnvironment (Environment::DEFAULT);
	ligacao = env->createConnection (user, passwd, db);
}


/**
 * destrutor do objecto BDados
 */
BDados::~BDados()
{
	env->terminateConnection (ligacao);
	Environment::terminateEnvironment (env);
}


/**
 * converte uma data presente numa string (no formato AA.MM.DD) para um objecto
 * do tipo Data
 * @param	data 	string com data no formato AA.MM.DD
 * @return 	temp	objecto do tipo Data
 */
Data BDados::convertData(string date)
{
	//DATE: AA.MM.DD
	string diaS, mesS, anoS;
	int dia = 1, mes = 1, ano = 1900;

	anoS = date.substr(0,2);
	mesS = date.substr(3,2);
	diaS = date.substr(6,2);
	stringstream(diaS) >> dia;
	stringstream(mesS) >> mes;
	stringstream(anoS) >> ano;
	ano += 2000;
	Data temp(ano, mes, dia);

	return temp;
}


/**
 * metodo que retorna descricao do estado, para um dado codigo de estado
 * @param 	codEstado 	codigo de estado
 * @return 	descricao do estado
 */
string BDados::getEstado(int codEstado)
{
	stringstream out;
	string operacao;
	string estado;

	out << "SELECT * FROM ESTADO WHERE COD_ESTADO = " << codEstado;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		estado = rset->getString(2);
	}
	instrucao->closeResultSet (rset);

	return estado;
}


/**
 * retorna nome do utilizador, para um dado codigo de utilzador
 * @param 	codUser 	codigo de utilizador
 * @return 	nome do utilizador
 */
string BDados::getUser(int codUser)
{
	stringstream out;
	string operacao;
	string estado;

	out << "SELECT * FROM UTILIZADOR WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		estado = rset->getString(2);
	}
	instrucao->closeResultSet (rset);

	return estado;
}


/**
 * preenche listas de Tarefa_Contexto e lista de Codigo_Contexto
 * @param 	*codigoTarefa 	apontador para Lista de codigos de tarefas
 * @param 	*codigoContxto 	apontador para lista de codigo de contextos
 */
void BDados::listaTarefaContexto(Lista<int> *codigoTarefa, Lista<int> *codigoContexto)
{
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA_CONTEXTO";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		codigoTarefa->insere(codigoTarefa->comprimento()+1, rset->getInt(1));
		codigoContexto->insere(codigoContexto->comprimento()+1, rset->getInt(2));
	}
	instrucao->closeResultSet (rset);

}


/**
 * preenche lista de codigos de estados e lista de descricoes de estados
 * @param 	*codigos 		apontador para lista de codigos de estados
 * @param 	*descricoes 	apontador para lista de descricoes de estados
 */
void BDados::listaEstados(Lista<int> *codigos, Lista<string> *descricoes)
{
	stringstream out;
	string operacao;

	out << "SELECT * FROM ESTADO";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		codigos->insere(codigos->comprimento()+1, rset->getInt(1));
		descricoes->insere(descricoes->comprimento()+1, rset->getString(2));
	}
	instrucao->closeResultSet (rset);

}


/**
 * preenche listas de codigos de tipo e lista de descricoes de tipo
 * @param 	*codigos 		apontador para lista de codigos de tipo
 * @param 	*descricoes 	apontador para lista de descricoes de tipo
 * @return
 */
void BDados::listaTipos(Lista<int> *codigos, Lista<string> *descricoes)
{
	stringstream out;
	string operacao;

	out << "SELECT * FROM TIPO";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		codigos->insere(codigos->comprimento()+1, rset->getInt(1));
		descricoes->insere(descricoes->comprimento()+1, rset->getString(2));
	}
	instrucao->closeResultSet (rset);

}


/**
 * lista todos os projectos do utilizador
 * @param 	codUser			codigo do utilizador
 * @return 	Lista<Projecto> 	objecto do tipo Lista com todos os registos da tabela projecto
 */
Lista<Projecto> BDados::listarProjectos(int codUser)
{
	Lista<Projecto> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM PROJECTO WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dcria, dfim;
		if(!rset->isNull(3))
			dcria = convertData(rset->getString(3));
		if(!rset->isNull(4))
			dfim = convertData(rset->getString(4));

		Projecto pro(rset->getInt(1), rset->getInt(7),rset->getInt(8), rset->getInt(2), dcria, dfim, rset->getString(5), rset->getString(6));
		ret.insere(ret.comprimento() + 1, pro);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * guarda numa lista todos os utlizadores da tabela Utilizador da base de dados
 * @return 	devolve lista com todos os utilizadors
 */
Lista<Utilizador> BDados::listarUtilizadores()
{
	Lista<Utilizador> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM UTILIZADOR ";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Utilizador uti(rset->getInt(1), rset->getString(2), rset->getInt(3), rset->getString(4), rset->getString(5));
		ret.insere(ret.comprimento() + 1, uti);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * guarda numa lista todos os nives de importancia da tabela Nivel da base de dados
 * @return 	devolve lista com todos os niveis de importancia
 */
Lista<Nivel> BDados::listarNiveis()
{
	Lista<Nivel> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM NIVEL ";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Nivel niv(rset->getInt(1), rset->getString(2));
		ret.insere(ret.comprimento() + 1, niv);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * guarda numa lista todos os contextos da tabela Contexto da base de dados
 * @return 	devolve lista com todos os contextos
 */
Lista<Contexto> BDados::listarContextos()
{
	Lista<Contexto> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM CONTEXTO ";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Contexto cont(rset->getInt(1), rset->getString(2));
		ret.insere(ret.comprimento() + 1, cont);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * lista toda a informação de um dado utilizador
 * @param 	user 				codigo do utilizador
 * @return 	Lista<Informacao> 	objecto do tipo Lista com todos os registos da tabela Informacao
 */
Lista<Informacao> BDados::listaInformacao(int user)
{
	Lista<Informacao> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM INFORMACAO WHERE COD_UTILIZADOR = " << user;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data tmp = convertData(rset->getString(4));
		Informacao inf(rset->getInt(1), rset->getInt(2), rset->getString(3), tmp, rset->getInt(5));
		ret.insere(ret.comprimento() + 1, inf);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * lista todas as tarefas do utilizador
 * @param 	codUser			codigo do utilizador
 * @return 	Lista<Tarefa> 	objecto do tipo Lista com todos os registos da tabela tarefa
 */
Lista<Tarefa> BDados::listarTarefasTodas(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery();
	while (rset->next ())
	{
		Data dcria, dfim, dest;
		if(!rset->isNull(5))
			dcria = convertData(rset->getString(5));
		if(!rset->isNull(6))
			dfim = convertData(rset->getString(6));
		if(!rset->isNull(8))
			dest = convertData(rset ->getString(8));
		Tarefa tar(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dcria, dfim, rset->getString(7),dest, rset->getInt(9), rset->getString(10),rset->getString(11), rset->getInt(12), rset->getInt(13), rset->getInt(14), rset->getInt(15));
		ret.insere(ret.comprimento() + 1, tar);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * metodo que faz a autenticacao do utilizador na aplicacao
 * @param 	user 	nome da conta do utilizador na aplicacao
 * @param 	pass 	palavra-passe do utilizador
 * @return	codigo do utilizador caso acesso seja autenticado,
 * 			ou -1 caso caso a autenticao falhe
 */
int BDados::login(string user, string pass)
{
	stringstream out;
	out << "SELECT * FROM UTILIZADOR WHERE LOGIN = '" << user << "'";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao -> executeQuery();
	rset->next();
	Utilizador uti(rset->getInt(1), rset->getString(2), rset->getInt(3), rset->getString(4), rset->getString(5));
	if(uti.getPass() == pass)
	{
		instrucao->closeResultSet(rset);
		return uti.getCodUtilizador();	
	}
	else
	{
		instrucao->closeResultSet(rset);
		return -1;
	}
}


/**
 * inicia procedimento PL-SQL para insercao de novo utilizador na base de dados
 * @param 	nome 		nome do utilizador
 * @param 	telefone 	telefone do utilizador
 * @param 	login 		nome de login
 * @param 	pass 		password do utilizador
 */
void BDados::inserirUtilizador(string nome, int telefone, string login, string pass)
{
	stringstream out;
	out << "BEGIN\nIUTILIZADOR('" << nome << "', " << telefone << ", '" << login << "', '" << pass << "' );\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * insere novo registo na tabela Projecto da base de dados
 * @param 	codProjecto 		codigo do projecto
 * @param 	codEstado 			codigo do estado do projecto
 * @param 	codUtilizador 		codigo do utilizador a que diz respeito o projecto
 * @param 	nivelImportancia 	nivel de importancia do projecto
 * @param 	dataInicio 			data de inicio do projecto
 * @param 	dataFim 			data de fim do projecto
 * @param 	informacao 			informacao associada ao projecto
 * @param 	nome 				nome do projecto
 */
void BDados::inserirProjetoCompleto(int codProjecto,int codEstado,int codUtilizador,int nivelImportancia, string dataInicio, string dataFim, string informacao, string nome)
{
	stringstream out;

	if(dataFim == "NULL")
		out << "INSERT INTO Projecto(cod_projecto, nivel_importancia, data_inicio, data_fim, informacao, nome, cod_estado, cod_utilizador) VALUES(seq_projecto.NEXTVAL," << nivelImportancia << ", '" << dataInicio <<"', null, '" << informacao << "', '" << nome << "', " << codEstado << ", " << codUtilizador << ")";
	else	
		out << "INSERT INTO Projecto(cod_projecto, nivel_importancia, data_inicio, data_fim, informacao, nome, cod_estado, cod_utilizador) VALUES(seq_projecto.NEXTVAL," << nivelImportancia << ", '" << dataInicio <<"', '"<< dataFim << "', '" << informacao << "', '" << nome << "', " << codEstado << ", " << codUtilizador << ")";

	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * inicia procedimento PL-SQL para inserir registo na tabela Tarefa_Contexto
 * @param 	codTarefa 		codigo da tarefa
 * @param 	codContexto 	codigo do contexto
 */
void BDados::inserirTarefaContexto(int codTarefa, int codContexto)
{
	stringstream out;
	out << "BEGIN\nITAREFA_CONTEXTO(" << codTarefa << "," << codContexto << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * inicia procedimento PL-SQL para inserir registo na tabela Contexto
 * @param 	descricao 	descricao do contexto
 */
void BDados::inserirContexto(string descricao)
{
	stringstream out;
	out << "BEGIN\nICONTEXTO('" << descricao << "');\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * inicia procedimento PL-SQL para inserir estado na tabela Estado
 * @param 	descricao 	descricao do estado
 */
void BDados::inserirEstado(string descricao)
{
	stringstream out;
	out << "BEGIN\nIESTADO('" << descricao << "');\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * inicia procedimento PL-SQL para inserir registo na tabela Nivel
 * @param 	nivelImportancia 	nivel de importancia
 * @param 	desc 				descricao do nivel de importancia
 */
void BDados::inserirNivel(int nivelImportancia, string desc)
{
	stringstream out;
	out << "BEGIN\niNivel('" << desc << "');\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * inicia procedimento PL-SQL para inserir registo na tabela tipo
 * @param 	descricao 	descricao do tipo
 * @return
 */
void BDados::inserirTipo(string descricao)
{
	stringstream out;
	out << "BEGIN\nITIPO('" << descricao << "');\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * insere informacao na base de dados
 * @param 	codUser 	codigo do utilizador
 * @param 	info 		informacao na forma de texto
 */
void BDados::inserirInfo(int codUser, string info)
{
	stringstream out;
	out << "BEGIN\nIINFORMACAO(NULL, '" << info << "', " << codUser << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * insere dados na tabela Informacao
 * @param 	codUser 	codigo de utilizador
 * @param 	info 		descricao, em texto, da informacao
 * @param 	codTarefa 	codigo da tarefa associada a esta informacao
 */
void BDados::inserirInfoCompleta(int codUser, string info, int codTarefa)
{
	stringstream out;
	out << "BEGIN\nIINFORMACAO("<< codTarefa << ", '" << info << "', " << codUser << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * insere tarefa na base de dados
 * @param 	nivelImportancia	inteiro que corresponde ao nivel de importancia da tarefa
 								(0: mais importante; 9: menos importante)
 * @param 	Informacao 			texto com informacao que vai ser usada para criar tarefa
 * @param 	dataEstimada 		texto com data estimada de duracao da tarefa
 * @param 	dataInicio 			texto com a data de inicio da tarefa
 * @param 	duracao 			inteiro com duracao da terefa (em minutos)
 * @param 	tipo 				texto que indica qual o tipo da tarefa
 * @param 	titulo 				texto com titulo a atribuir a tarefa
 * @param 	tarefaDependente 	inteiro que indica se existe dependencia na tarefa a ser criada
 * @param 	codUtilizador 		codigo do utilizador assoicado a tarefa a ser criada
 */
void BDados::inserirTarefa(int nivelImportancia, string dataInicio, string informacao, string dataEstimada, int duracao, string tipo, string titulo, int tarefaDependente, int codUtilizador)
{
	stringstream out;
	if(dataInicio != "")
		out << "BEGIN\nITAREFA(" << nivelImportancia << ",'" << dataInicio << "', '" << informacao << "', '" << dataEstimada << "'," << duracao << ",'" << tipo << "', '" << titulo << "', " << tarefaDependente << ", " << codUtilizador << ");\nEND;";
	else
		out << "BEGIN\nITAREFA(" << nivelImportancia << ", null, '" << informacao << "', '" << dataEstimada << "'," << duracao << ",'" << tipo << "', '" << titulo << "', " << tarefaDependente << ", " << codUtilizador << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * insere dados para todos os campos da tabela tarefa
 * @param 	codTarefa 			codigo da tarefa
 * @param 	codProjecto 		codigo do projecto ao qual pertence a tarefa
 * @param 	codEstado 			codigo de estado da tarefa
 * @param 	nivelImportancia 	nivel de importancia da tarefa
 * @param 	dataCriacao 		data de criacao da tarefa
 * @param 	dataFim 			data de fim da tarefa
 * @param 	informacao 			informacao sobre a tarefa
 * @param 	dataEstimada 		data estimada de fim da tarefa
 * @param 	duracao 			duracao da tarefa, em minutos
 * @param 	tipo 				tipo da tarefa
 * @param 	titulo 				titulo da tarefa
 * @param 	dependente 			codigo da tarefa da qual depende
 * @param 	codUtilizador 		codigo do utilizador ao qual corresponde a tarefa
 * @param 	nContexto 			contexto ao qual esta associada a tarefa
 * @param 	delegado 			codigo do utilizador a quem a tarefa foi delegada
 */
void BDados::inserirTarefaCompleta(int codTarefa, int codProjecto, int codEstado, int nivelImportancia, string dataInicio, string dataFim, string informacao, string dataEstimada, int duracao, string tipo, string titulo, int dependente, int codUtilizador, int nContexto, int delegado)
{
	stringstream out;
	if(dataFim == "NULL" && dataEstimada == "NULL")
		out << "INSERT INTO TAREFA(cod_tarefa, cod_projecto, cod_estado, nivel_importancia,	data_inicio, data_fim, informacao, estimativa, duracao, tipo, titulo, dependente, cod_utilizador, ncontexto, delegado) VALUES( seq_tarefa.NEXTVAL, null, " << codEstado << ", " << nivelImportancia <<", '" << dataInicio << "', null, '" << informacao << "', null, " << duracao <<	", '" << tipo << "', '" << titulo << "', " << dependente << ", " << codUtilizador <<", " << 0 << ", NULL)";
	else if (dataFim == "NULL" && dataEstimada != "NULL")
		out << "INSERT INTO TAREFA(cod_tarefa, cod_projecto, cod_estado, nivel_importancia,	data_inicio, data_fim, informacao, estimativa, duracao, tipo, titulo, dependente, cod_utilizador, ncontexto, delegado) VALUES( seq_tarefa.NEXTVAL, null, " << codEstado << ", " << nivelImportancia <<", '" << dataInicio << "', null, '" << informacao << "', '" << dataEstimada << "', " << duracao <<	", '" << tipo << "', '" << titulo << "', " << dependente << ", " << codUtilizador <<", " << 0 << ", NULL)";
	else if (dataFim != "NULL" && dataEstimada == "NULL")
		out << "INSERT INTO TAREFA(cod_tarefa, cod_projecto, cod_estado, nivel_importancia,	data_inicio, data_fim, informacao, estimativa, duracao, tipo, titulo, dependente, cod_utilizador, ncontexto, delegado) VALUES( seq_tarefa.NEXTVAL, null, " << codEstado << ", " << nivelImportancia <<", '" << dataInicio << "', '"<<dataFim << "', '"<< informacao << "', '" << dataEstimada << "', " << duracao <<	", '" << tipo << "', '" << titulo << "', " << dependente << ", " << codUtilizador <<", " << 0 << ", NULL)";
	else
		out << "INSERT INTO TAREFA(cod_tarefa, cod_projecto, cod_estado, nivel_importancia,	data_inicio, data_fim, informacao, estimativa, duracao, tipo, titulo, dependente, cod_utilizador, ncontexto, delegado) VALUES( seq_tarefa.NEXTVAL, null, " << codEstado << ", " << nivelImportancia <<", '" << dataInicio << "', '"<<dataFim << "', '"<< informacao << "', null, " << duracao <<	", '" << tipo << "', '" << titulo << "', " << dependente << ", " << codUtilizador <<", " << 0 << ", NULL)";

	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * associa informacao presente no sistema a uma dada tarefa
 * @param 	codTarefa 	codigo
 * @return
 */
bool BDados::associarInformacao(int codTarefa, int codInformacao)
{
	stringstream out;
	if(podeAssociarInfo(codInformacao))
	{
		out << "UPDATE Informacao SET cod_tarefa=" << codTarefa << " WHERE cod_informacao=" << codInformacao;
		string comando = out.str();
		instrucao = ligacao->createStatement(comando);
		instrucao->executeUpdate();
		ligacao->commit();
		ligacao->terminateStatement(instrucao);

		return true;
	}else
		return false;
}


/**
 * verifica se e possivel associar informacao a uma tarefa
 * @param 	codInformacao 	codigo da informacao
 * @return 	true se for possivel associar informacao, false no caso oposto
 */
bool BDados::podeAssociarInfo(int codInformacao)
{
	stringstream out;
	bool ret;

	out << "select * from informacao where cod_informacao=" << codInformacao;
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao->executeQuery ();
	rset->next();
	if(rset->isNull(2))
		ret = true;
	else
		ret = false;
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * devolve o codigo da ultima tarefa da tabela de tarefas de um dado utilizador
 * @param 	codUser 	codigo do utilizador
 * @return 	devolve o codigo da ultima tarefa, caso nao exista nenhuma devolve -1
 */
int BDados::ultimaTarefa(int codUser)
{
	int ret = -1;
	stringstream out;
	string comando;

	out << "SELECT COD_TAREFA FROM TAREFA WHERE COD_UTILIZADOR =" << codUser << "ORDER BY COD_TAREFA DESC";
	comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao -> executeQuery();
	rset->next();
	ret = rset->getInt(1);
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * devolve o codigo da ultima informacao da tabela de informacao de um dado utilizador
 * @param 	codUser 	codigo do utilizador
 * @return 	devolve o codigo da ultima informacao, caso nao exista devolve -1
 */
int BDados::ultimaInfo(int codUser)
{
	int ret = -1;
	stringstream out;
	string comando;

	out << "SELECT COD_INFORMACAO FROM INFORMACAO WHERE COD_UTILIZADOR =" << codUser << "ORDER BY COD_INFORMACAO DESC";
	comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao -> executeQuery();
	rset->next();
	ret = rset->getInt(1);
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * lista todos os registos de informacao que nao estejam associados a uma tarefa
 * para um dado utilizador 
 * @param 	codUser 	codigo do utilizador
 * @return 	objecto do tipo lista com as informacoes sem tarefas associadas
 */
Lista<Informacao> BDados::listaInfoSemTarefa(int codUser)
{
	Lista<Informacao> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM INFORMACAO WHERE COD_TAREFA IS NULL AND COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data tmp = convertData(rset->getString(4));
		Informacao inf(rset->getInt(1), rset->getInt(2), rset->getString(3), tmp, rset->getInt(5));
		if(rset->isNull(2))
			ret.insere(ret.comprimento() + 1, inf);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * altera os varios campos de um registo da tabela Tarefa
 * @param 	codTarefa 			codigo da tarefa
 * @param 	codestado 			codigo do estado da tarefa
 * @param 	nivelimportancia 	nivel de importancia da tarefa
 * @param 	durancao			duracao da tarefa, em minutos
 * @param 	coddependente 		codigo da tarefa da qual a presente tarefa esta dependente
 * @param 	delegado 			codigo de utilizador ao qual foi delegada a tarefa
 * @param 	datafim 			data de fim da tarefa
 * @param 	dataestimada 		data estimada de fim da tarefa
 * @param 	info 				informacao sobre a tarefa
 * @param 	titulo 				titulo da tarefa
 * @param 	tipo 				tipo de tarefa
 */
void BDados::alterarInformacao(int codinformacao, string descricao)
{
	    string operacao;
		stringstream out;
		out << "UPDATE INFORMACAO SET DESCRICAO = '" << descricao << "'WHERE COD_INFORMACAO = " << codinformacao;
		operacao=out.str();
		cout << operacao << endl;
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		ligacao->terminateStatement(instrucao);
		
}


/**
 * Permite modificar os valores de uma tarefa
 * @param codTarefa        codigo da tarefa
 * @param codestado        codigo de estado
 * @param nivelimportancia nivel de importancia da tarefa
 * @param dataInicio       data de inicio da tarefa
 * @param duracao          duracao da tarefa
 * @param coddependente    codigo da tarefa dependente
 * @param delegado         codigo do utilizador delegado
 * @param datafim          data de fim da tarefa
 * @param dataestimada     data estimada
 * @param info             informacao da tarefa
 * @param titulo           titulo da tarefa
 * @param tipo             tipo da tarefa
 */
void BDados::alterarTarefa(int codTarefa, int codestado, int nivelimportancia, string dataInicio, int duracao, int coddependente, int delegado, string datafim, string dataestimada, string info, string titulo, string tipo)
{
	string operacao;
	if(codestado!=0)
	{
		stringstream out;
		out << "UPDATE TAREFA SET COD_ESTADO = " << codestado << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		
	}
	if(nivelimportancia!=0)
	{
		stringstream out;
		out << "UPDATE TAREFA SET NIVEL_IMPORTANCIA = " << nivelimportancia << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(dataInicio!="")
	{
		stringstream out;
		out << "UPDATE TAREFA SET DATA_INICIO = " << dataInicio << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(duracao!=0)
	{
		stringstream out;
		out << "UPDATE TAREFA SET DURACAO = " << duracao << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(coddependente!=0)
	{
		stringstream out;
		out << "UPDATE TAREFA SET DEPENDENTE = " << coddependente << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(delegado!=0)
	{
		stringstream out;
		out << "UPDATE TAREFA SET DELEGADO = " << delegado << "WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(datafim!="")
	{
		stringstream out;
		
		out << "UPDATE TAREFA SET DATA_FIM ='" << datafim << "'WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(dataestimada!="")
	{
		stringstream out;
		
		out << "UPDATE TAREFA SET ESTIMATIVA ='" << dataestimada << "'WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	if(info!="")
	{
		stringstream out;
				
		out << "UPDATE TAREFA SET INFORMACAO ='" << info << "'WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	if(titulo!="")
	{
		stringstream out;
		out << "UPDATE TAREFA SET TITULO ='" << titulo << "'WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	if(tipo!="")
	{
		stringstream out;
				
		out << "UPDATE TAREFA SET TIPO ='" << tipo << "'WHERE COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite inserir um projeto na base de dados
 * @param codUser          codigo utilizador
 * @param nivelImportancia nivel de importacia do projeto
 * @param dataInicio       data de inicio do projeto
 * @param dataFim          data de fim do projeto
 * @param informacao       informacao do projeto
 * @param nome             nome do projeto
 * @param codEstado        codigo estado
 */
void BDados::inserirProjeto(int codUser, int nivelImportancia, string dataInicio,string dataFim, string informacao, string nome, int codEstado)
{
	stringstream out;
	if(dataInicio != "")
		out << "BEGIN\nIPROJECTO("<< nivelImportancia <<",'" << dataInicio << "', '" << informacao << "', '" << nome << "'," <<codUser << ");\nEND;";
	else
		out << "BEGIN\nIPROJECTO("<< nivelImportancia <<", null, '" << informacao << "', '" << nome << "'," <<codUser << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite obter o codigo do ultimo projeto inserido
 * @param  codUser codigo utilizador
 * @return         codigo do ultimo projeto inserido
 */
int BDados::ultimoProjeto(int codUser)
{
	int ret = -1;
	stringstream out;
	string comando;

	out << "SELECT COD_PROJECTO FROM PROJECTO WHERE COD_UTILIZADOR =" << codUser << "ORDER BY COD_PROJECTO DESC";
	comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao -> executeQuery();
	rset->next();
	ret = rset->getInt(1);
	instrucao->closeResultSet (rset);

	return ret;
}


Lista<Tarefa> BDados::listaTarefaSemProjecto(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_PROJECTO IS NULL AND COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data tmpCria = convertData(rset->getString(5));
		Data tmpFim;
		if(!rset->isNull(6))
			tmpFim = convertData(rset->getString(6));
		else{
			Data tmp(1900, 1, 1);
			tmpFim = tmp;
		}
		Data tmpEst;
		if(!rset->isNull(8))
			tmpEst = convertData(rset->getString(8));
		else
		{
			Data tmp(1900, 1, 1);
			tmpEst = tmp;
		}		
		Tarefa tar(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), tmpCria, tmpFim, rset->getString(7), tmpEst, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12), rset->getInt(13), rset->getInt(14), rset->getInt(15));
		if(rset->isNull(2))
			ret.insere(ret.comprimento() + 1, tar);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Permite associar uma tarefa a um projeto
 * @param  codTarefa  codigo da tarefa
 * @param  codProjeto codigo do projeto
 * @return            verdadeiro caso consiga associar uma tarefa
 */
bool BDados::associarTarefa(int codTarefa, int codProjeto)
{
	stringstream out;
	if(podeAssociarTare(codTarefa))
	{
		out << "UPDATE TAREFA SET COD_PROJECTO=" << codProjeto << " WHERE COD_TAREFA=" << codTarefa;
		string comando = out.str();
		instrucao = ligacao->createStatement(comando);
		instrucao->executeUpdate();
		ligacao->commit();
		ligacao->terminateStatement(instrucao);

		return true;
	}else
		return false;
}


/**
 * Verifica se pode associar uma tarefa a um determinado projeto
 * @param  codTarefa codigo da tarefa
 * @return           verdadeiro a associacao seja possivel
 */
bool BDados::podeAssociarTare(int codTarefa)
{
	stringstream out;
	bool ret;

	out << "select * from tarefa where cod_tarefa=" << codTarefa;
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao->executeQuery ();
	rset->next();
	if(rset->isNull(2))
		ret = true;
	else
		ret = false;
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * adiciona a lista o registo da tabela tarefa_contexto com um dado codigo de tarefa
 * @param 	codTarefa 	codigo da tarefa
 */
Lista<int> BDados::listarCodContextos(int codTarefa)
{
	Lista<int> ret;
	stringstream out;
	out << "select * from tarefa_contexto where cod_tarefa=" << codTarefa;
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	ResultSet *rset = instrucao->executeQuery ();
	while(rset->next())
	{
		ret.insere(ret.comprimento() + 1, rset->getInt(2));
	}

	return ret;
}


/**
 * insere numa lista todos os projecto de um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo Projecto 	
 */
Lista<Projecto> BDados::listarProjetosTodos(int codUser)
{

	Lista<Projecto> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM PROJECTO WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery();
	while (rset->next ())
	{
		Data dcria, dfim;
		if(!rset->isNull(3))
			dcria = convertData(rset->getString(3));
		if(!rset->isNull(4))
			dfim = convertData(rset->getString(4));
		cout << rset->getInt(7);
		Projecto pro(rset->getInt(1),rset->getInt(7),rset->getInt(8), rset->getInt(2), dcria, dfim, rset->getString(5), rset->getString(6));
		ret.insere(ret.comprimento() + 1, pro);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Permite eliminar um projeto da base de dados
 * @param codUser    codigo utilizador
 * @param codProjeto codigo projecto
 */
void BDados::eliminarProjeto(int codUser, int codProjeto)
{
	string operacao;
	stringstream out, out2;

	out << "UPDATE TAREFA SET COD_PROJECTO = NULL WHERE COD_PROJECTO = " << codProjeto << " AND COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);

	out2 << "DELETE FROM PROJECTO WHERE COD_PROJECTO = " << codProjeto << " AND COD_UTILIZADOR = " << codUser;
	operacao = out2.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite alterar os atributos de um projeto na base de dados
 * @param codPro           codigo projeto
 * @param codestado        codigo estado
 * @param nivelimportancia nivel importancia
 * @param dataInicio       data de inicio do projecto
 * @param datafim          data de fim do projecto
 * @param informacao       informacao do projecto
 * @param titulo           titulo do projecto
 */
void BDados::alterarProjeto(int codPro, int codestado, int nivelimportancia,string dataInicio, string datafim,string informacao,string titulo)
{
		string operacao;
	if(codestado!=0)
	{
		stringstream out;
		out << "UPDATE PROJECTO SET COD_ESTADO = " << codestado << "WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();


	}
	if(nivelimportancia!=0)
	{
		stringstream out;
		out << "UPDATE PROJECTO SET NIVEL_IMPORTANCIA = " << nivelimportancia << "WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(dataInicio!="")
	{
		stringstream out;
		out << "UPDATE PROJECTO SET DATA_INICIO = " << dataInicio << "WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(datafim!="")
	{
		stringstream out;


		out << "UPDATE PROJECTO SET DATA_FIM ='" << datafim << "'WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
		instrucao->executeUpdate();
		ligacao->commit();
		out.flush();
	}
	if(informacao!="")
	{
		stringstream out;


		out << "UPDATE PROJECTO SET INFORMACAO ='" << informacao << "'WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	if(titulo!="")
	{
		stringstream out;
		out << "UPDATE PROJECTO SET NOME ='" << titulo << "'WHERE COD_PROJECTO = " << codPro;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		out.flush();
	}
	
	ligacao->terminateStatement(instrucao);
}


/**
 * lista todas as tarefas realizadas de um utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo Tarefa
 */
Lista<Tarefa> BDados::listarTarefasRealizadas(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << " AND COD_ESTADO = 2";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * lista todas as tarefas por realizar de um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo Tarefa
 */
Lista<Tarefa> BDados::listarTarefasPorRealizar(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << " AND COD_ESTADO = 1";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Altera o estado de uma tarefa para realizada
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 */
void BDados::realizarTarefa(int codUser, int codTarefa)
{
		string operacao;
		stringstream out;
				
		out << "UPDATE TAREFA SET COD_ESTADO = 2 WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = " << codTarefa;
		operacao=out.str();
		instrucao = ligacao->createStatement(operacao);
	    instrucao->executeUpdate();
	    ligacao->commit();
		cout << "Processo realizado com sucesso!!!" << endl;
	
	ligacao->terminateStatement(instrucao);
}


/**
 * Associa uma duracao a uma tarefa
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 * @param duracao   duracao
 */
void BDados::associarDuracao(int codUser, int codTarefa, int duracao)
{
	string operacao;
	stringstream out;
	out << "UPDATE TAREFA SET DURACAO = " << duracao << "WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = "<< codTarefa;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Processo realizado com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite eliminar uma tarefa da base de dados
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 */
void BDados::eliminarTarefa(int codUser, int codTarefa)
{
	string operacao;
	stringstream out, out2, out3;
	
	out << "UPDATE INFORMACAO SET COD_TAREFA = NULL WHERE COD_TAREFA = " << codTarefa << " AND COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	
	ligacao->commit();
	ligacao->terminateStatement(instrucao);

	
	out2 << "DELETE FROM TAREFA_CONTEXTO WHERE COD_TAREFA = " << codTarefa;
	operacao = out2.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
		
	out3 << "DELETE FROM TAREFA WHERE COD_TAREFA = " << codTarefa << " AND COD_UTILIZADOR= " << codUser;
	operacao = out3.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
	cout << "Tarefa eliminada com sucesso" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * ordena tarefas por prioridade para um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo Tarefa
 */
Lista<Tarefa> BDados::ordenarPrioridade(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << " ORDER BY NIVEL_IMPORTANCIA";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * ordena tarefa por estimativa de tempo para um dado utilizador
 * @param 	codUser	codigo de utilizador
 * @return	devolve lista do tipo Tarefa
 */
Lista<Tarefa> BDados::ordenarTarefasEstimativa(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << " AND ESTIMATIVA IS NOT NULL ORDER BY ESTIMATIVA DESC";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}	
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
	
	    
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		if(taref.getDataEstimada().getAno()!=1900)
			ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * ordena tarefas pelo seu contexto
 * @param 	codUser 	codigo do utilizador
 * @return 	devolve lista do tipo Tarefa
 */
Lista<Tarefa> BDados::ordenarTarefasContexto(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << " ORDER BY NCONTEXTO";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Permite associar uma tarefa com um nivel
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 * @param nivel     codigo nivel
 */
void BDados::associarTarefaNivel(int codUser, int codTarefa, int nivel)
{
	string operacao;
	stringstream out;
	out << "UPDATE TAREFA SET NIVEL_IMPORTANCIA = " << nivel << "WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = "<< codTarefa;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Processo realizado com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * permite ver todas as tarefas delegadas por um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	lista do tipo Tarefa
 */
Lista<Tarefa> BDados::verTarefasDelegadas(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM TAREFA WHERE COD_UTILIZADOR = " << codUser << "AND DELEGADO IS NOT NULL";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));
		
		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Permite delegar uma tarefa a um utilizador
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 * @param codUtil   codigo utilizador a sofrer a delegacao
 */
void BDados::delegarTarefa(int codUser, int codTarefa, int codUtil)
{
	string operacao;
	stringstream out;
	out << "UPDATE TAREFA SET DELEGADO = " << codUtil << "WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = "<< codTarefa;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Tarefa delegada com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite alterar a delegacao de um utilizador
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 * @param codUtil   codigo utilizador a sofrer a delegacao
 */
void BDados::alterarDelegacao(int codUser, int codTarefa, int codUtil)
{
	string operacao;
	stringstream out;
	out << "UPDATE TAREFA SET DELEGADO = " << codUtil << "WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = "<< codTarefa;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Delegacao alterada com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite remover a delegacao de um utilizador
 * @param codUser   codigo utilizador
 * @param codTarefa codigo tarefa
 */
void BDados::removerDelegacao(int codUser, int codTarefa)
{
	string operacao;
	stringstream out;
	out << "UPDATE TAREFA SET DELEGADO = NULL WHERE COD_UTILIZADOR = " << codUser << " AND COD_TAREFA = "<< codTarefa;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Delegacao removida com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * lista todos os contextos
 * @return 	lista do tipo Contexto
 */
Lista<Contexto> BDados::listaContextos()
{
	Lista<Contexto> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM CONTEXTO";
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Contexto cont(rset->getInt(1), rset->getString(2));
		ret.insere(ret.comprimento() + 1, cont);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * Permite criar um contexto
 * @param descricao descricao de um contexto
 */
void BDados::criarContexto(string descricao)
{
	stringstream out;
	out << "BEGIN\niContexto('" << descricao << "');\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite alterar a descricao de um contexto
 * @param codContexto codigo contexto
 * @param descricao   descricao do contexto
 */
void BDados::alterarContexto(int codContexto, string descricao)
{
	string operacao;
	stringstream out;
	out << "UPDATE CONTEXTO SET DESCRICAO = '" << descricao << "' WHERE COD_CONTEXTO = "<< codContexto;
	operacao=out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
    cout << "Contexto alterado com sucesso!!!" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite eliminar um contexto da base de dados
 * @param codContexto codigo contexto
 */
void BDados::eliminarContexto(int codContexto)
{
	string operacao;
	stringstream out, out2;
	
	out << "DELETE FROM TAREFA_CONTEXTO WHERE COD_CONTEXTO = " << codContexto;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
	
		
	out2 << "DELETE FROM CONTEXTO WHERE COD_CONTEXTO = " << codContexto;
	operacao = out2.str();
	instrucao = ligacao->createStatement(operacao);
	instrucao->executeUpdate();
	ligacao->commit();
	cout << "Contexto eliminado com sucesso" << endl;
	ligacao->terminateStatement(instrucao);
}


/**
 * Permite associar uma tarefa a um contexto
 * @param codContexto codigo contexto
 * @param codTarefa   codigo tarefa
 */
void BDados::associarTarefaContexto(int codContexto, int codTarefa)
{
	stringstream out;
	out << "BEGIN\nITAREFA_CONTEXTO('" << codTarefa << "', " << codContexto << ");\nEND;";
	string comando = out.str();
	instrucao = ligacao->createStatement(comando);
	instrucao->executeUpdate();
	ligacao->commit();
	ligacao->terminateStatement(instrucao);
}


/**
 * lista todo o historico de informacao de um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	lista do tipo HistoricoInformacao
 */
Lista<HistoricoInformacao> BDados::listarHistoricoInformacao(int codUser)
{
	Lista<HistoricoInformacao> ret;
	stringstream out;
	string operacao;

	out << "SELECT * FROM INFORMACAO_HISTORICO WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataInsercao = convertData(rset->getString(6));
		HistoricoInformacao hi(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getString(4), rset->getInt(5),dataInsercao, rset->getInt(7), rset->getString(8));		
		ret.insere(ret.comprimento() + 1, hi);
	}
	instrucao->closeResultSet (rset);

	return ret;
}


/**
 * lista todos os lembretes de um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	lista do tipo tarefa
 */
Lista<Tarefa> BDados::listarLembrete(int codUser)
{
	Lista<Tarefa> ret;
	stringstream out;
	string operacao;


	out << "SELECT * FROM TAREFA WHERE DATA_INICIO = to_date(sysdate, 'YY.MM.DD') AND COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		Data dataCria = convertData(rset->getString(5));
		Data dataFim;
		if(!rset->isNull(6))
			dataFim=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
		Data estimativa;
		if(!rset->isNull(8))
			estimativa=convertData(rset->getString(8));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Tarefa taref(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), dataCria, dataFim, rset->getString(7), estimativa, rset->getInt(9), rset->getString(10), rset->getString(11), rset->getInt(12),rset->getInt(13), rset->getInt(14), rset->getInt(15));


		ret.insere(ret.comprimento() + 1, taref);
	}
	instrucao->closeResultSet (rset);


	return ret;
}


/**
 * lista o historico de tarefas de um dado utilizador
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo HistoricoTarefa
 */
Lista<HistoricoTarefa> BDados::listarHistoricoTarefa(int codUser)
{
	Lista<HistoricoTarefa> ret;
	stringstream out;
	string operacao;
	Data dataInicio, dataFim, dataInsercao, estimativa;
	out << "SELECT * FROM TAREFA_HISTORICO WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		if(!rset->isNull(6))
			dataInicio=convertData(rset->getString(6));
		else
		{
			Data tmp(1900,1,1);
			dataInicio = tmp;
		}
			if(!rset->isNull(7))
			dataFim=convertData(rset->getString(7));
		else
		{
			Data tmp(1900,1,1);
			dataFim = tmp;
		}
					if(!rset->isNull(9))
			estimativa=convertData(rset->getString(9));
		else
		{
			Data tmp(1900,1,1);
			estimativa = tmp;
		}
		Data dataInsercao = convertData(rset->getString(17));
		HistoricoTarefa ht(rset->getInt(1), rset->getInt(2), rset->getInt(3), rset->getInt(4), rset->getInt(5),dataInicio, dataFim, rset->getString(8), estimativa, rset->getInt(10), rset->getString(11), rset->getString(12), rset->getInt(13), rset->getInt(14), rset->getInt(15), rset->getInt(16), dataInsercao, rset->getInt(18), rset->getString(19) );		
		ret.insere(ret.comprimento() + 1, ht);
	}
	instrucao->closeResultSet (rset);


	return ret;
}


/**
 * lista o historico de projectos
 * @param 	codUser 	codigo de utilizador
 * @return 	devolve lista do tipo HistoricoProjecto
 */
Lista<HistoricoProjecto> BDados::listarHistoricoProjecto(int codUser)
{
	Lista<HistoricoProjecto> ret;
	stringstream out;
	string operacao;
	Data dataInicio, dataFim, dataInsercao;
	out << "SELECT * FROM PROJECTO_HISTORICO WHERE COD_UTILIZADOR = " << codUser;
	operacao = out.str();
	instrucao = ligacao->createStatement(operacao);
	ResultSet *rset = instrucao->executeQuery ();
	while (rset->next ())
	{
		if(!rset->isNull(4))
			dataInicio=convertData(rset->getString(4));
		else
		{
			Data tmp(1900,1,1);
			dataInicio = tmp;
		}

		dataInsercao=convertData(rset->getString(10));
		
		HistoricoProjecto hp(rset->getInt(1), rset->getInt(2), rset->getInt(3), dataInicio, dataFim, rset->getString(6), rset->getString(7), rset->getInt(8), rset->getInt(9), dataInsercao, rset->getInt(11) , rset->getString(12));		
		ret.insere(ret.comprimento() + 1, hp);
	}
	instrucao->closeResultSet (rset);

	return ret;
}

#endif