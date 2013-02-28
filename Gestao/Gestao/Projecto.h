/**
*@author Joao Machado
*@author Tiago Pacheco
*@author Vitor Hugo
*@date 08/01/2013 
*@file Projecto.h 
*Classe responsavel por guardar toda a informacao sobre o projecto.*/ 


#ifndef PROJECTO_H
#define PROJECTO_H
#include "Data.h"
#include "Lista.h"
#include "Tarefa.h"

class Projecto
{
private:
	int codProjecto;
	int codEstado;
	int codUtilizador;
	int nivelImportancia;
	Data dataCriacao;
	Data dataFim;
	string informacao;
	string nome;
	Lista<Tarefa> listaTarefas;
	

public:
	Projecto();
	Projecto(int codprojecto, int codestado, int codutilizador, int nivelimportancia, Data datacriacao, Data datafim, string informacao, string nome);  
	Projecto(const Projecto& p);
	~Projecto();

	int getCodProjecto() const;
	int getCodEstado() const;
	int getCodUtilizador() const;
	int getNivelImportancia() const;
	string getInformacao()const;
	string getNome()const;
	Data getDataCriacao();
	Data getDataFim();
	Lista<Tarefa> getListaTarefas() const;

	void setInformacao(const string informacao);
	void setNivelImportancia(const int nivelImportancia);
	void setNome(const string nome);
	void setCodUtilizador(const int codUtilizador);
	void setDataCriacao(const Data& dataCriacao);
	void setDataFim(const Data& dataFim);

	virtual Projecto *clone() const;
	void escreve(ostream &out)const;

};



/**
* Construtor completo
* @param 	codprojecto 		codigo do projecto
* @param 	codestado 			codigo do estado
* @param 	codutilizador 		codigo do utilizador
* @param 	nivelimportancia 	nivel de importancia
* @param 	datacriacao 		data de criacao do projecto
* @param 	datafim 			data de fim do projecto
* @param 	info 				informacao sobre o projecto
* @param 	n 					nome do projecto
* @param 	listatarefa 		objecto lista do tipo Tarefa (contem as tarefas que fazem parte do projecto)
*/
Projecto::Projecto(int codprojecto, int codestado, int codutilizador, int nivelimportancia, Data datacriacao, Data datafim, string info, string n)
{
	codProjecto=codprojecto;
	codUtilizador=codutilizador;
	codEstado = codestado;
	nivelImportancia=nivelimportancia;
	dataCriacao=datacriacao;
	dataFim=datafim;
	informacao=info;
	nome=n;
}


/**
 * Construtor vazio.
 */
Projecto::Projecto()
{
	
	Projecto(0,0,0,0, Data(), Data(), "","");
}


/**
 * Construtor copia
 * @param 	p 	objecto Projecto a ser copiado
 */
Projecto::Projecto(const Projecto& p)
{
	codProjecto=p.getCodProjecto();
	nivelImportancia=p.getNivelImportancia();
	dataCriacao=p.dataCriacao;
	dataFim=p.dataFim;
	informacao=p.getInformacao();
	nome=p.getNome();
	codEstado=p.getCodEstado();
	codUtilizador=p.getCodUtilizador();
	listaTarefas=p.getListaTarefas();
}


/*
 * Destrutor
 */
Projecto::~Projecto()
{
}


/**
 * Metodo para retornar o codigo do projecto
 * @return 	devolve codigo do projecto
 */
int Projecto::getCodProjecto() const
{
	return codProjecto;
}


/**
 * Metodo para retornar o codigo do estado
 * @return 	devolve codigo do estado do projecto
 */
int Projecto::getCodEstado() const
{
	return codEstado;
}


/**
 * Metodo para retornar o codigo do utilizador
 * @return 	devolve o codigo do utilizador associado ao projecto
 */
int Projecto::getCodUtilizador() const
{
	return codUtilizador;
}


/**
 * Metodo para retornar o nivel de importancia
 * @return 	devolve o nivel de importancia
 */
int Projecto::getNivelImportancia() const
{
	return nivelImportancia;
}


/**
* Metodo para retornar a informacao
* @return 	devolve informacao sobre o projecto
*/
string Projecto::getInformacao() const
{
	return informacao;
}


/**
* Metodo para retornar o nome
* @return 	devolve o nome do projecto
*/
string Projecto::getNome() const
{
	return nome;
}


/**
 * Metodo para retornar a data de criacao
 * @return 	devolve a data de criacao
 */
Data Projecto::getDataCriacao()
{
	return dataCriacao;
}


/**
 * Metodo para retornar a data de fim
 * @return 	devolve data de fim do projecto
 */
Data Projecto::getDataFim()
{
	return dataFim;
}


/**
 * Metodo que retorna o endereco da lista de tarefas
 * @return 	devolve objecto lista com as tarefas associada ao projecto
 */
Lista<Tarefa> Projecto::getListaTarefas() const
{
	return listaTarefas;
}


/**
 * Metodo de atribuicao da informacao
 * @param 	informacao 	informacao sobre o projecto
 */
void Projecto::setInformacao(const string informacao)
{
	this->informacao = informacao;
}


/**
 * Metodo de atribuicao do nivel de importancia
 * @param 	nivelImportancia 	nivel de importancia do projecto
 */
void Projecto::setNivelImportancia(const int nivelImportancia)
{
	this->nivelImportancia = nivelImportancia;
}


/**
 * Metodo de atribuicao do nome
 * @param 	nome 	nome do projecto
 */
void Projecto::setNome(const string nome)
{
	this->nome = nome;
}


/**
 * Metodo de atribuicao do codigo de utilizador
 * @param 	codUtilizador 	codigo do utilizador
 */
void Projecto::setCodUtilizador(const int codUtilizador)
{
	this->codUtilizador = codUtilizador;
}


/**
 * Metodo de atribuicao de data de criacao
 * @param 	dataCriacao 	data de criacao do projecto
 */
void Projecto::setDataCriacao(const Data& dataCriacao)
{
	this->dataCriacao = dataCriacao;
}


/**
 * Metodo de atribuicao de data fim
 * @param 	dataFim 	data de término do projecto
 */
void Projecto::setDataFim(const Data& dataFim)
{
	this->dataFim = dataFim;
}


/**
 * Apresenta os dados do projecto
 * @param 	out 	objecto de stream out
 */
void Projecto::escreve(ostream &out)const
{
	out << "Cod. Projecto: " << codProjecto << endl;
	out << "Nome: " << nome << endl;
	out << "Nivel de importancia: " << nivelImportancia << endl;
	out << "Data de criacao: " << dataCriacao;
	out << "Cod. Estado: " << codEstado << endl;
	out << "Cod. Utilizador: " << codUtilizador << endl;
	out << "Informacao: " << informacao << endl;
	out << "Data de fim: " << dataFim;
} 


/**
 * Sobrecarga do operador stream out
 * @param 	out 	objecto de stream out
 * @param 	p 		objecto Projecto
 */
ostream &operator << (ostream &out, const Projecto& p)
{
	p.escreve(out);
	return out;
}


/**
 * método clone de Projecto
 * @return 	devolve apontador para objecto Projecto
 */
Projecto* Projecto::clone() const
{
	return new Projecto(*this);
}

#endif