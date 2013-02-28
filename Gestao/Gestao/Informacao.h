/**
 * @author Joao Machado
 * @author Vitor Hugo
 * @date 21/12/2012 
 * @file Informacao.h 
 * Classe responsavel por guardar toda a informacao que o utilizador desejar colocar no programa, que pode ser ou nao uma tarefa
 */ 

#ifndef INFORMACAO_H
#define INFORMACAO_H
#include <iostream>
#include <string>
using namespace std;
#include "Data.h"

class Informacao
{
private:
	int codInformacao;
	int codTarefa;
	string descricao;
	Data dataInsercao;
	int codUtilizador;	

public:
	Informacao();
	Informacao(int codInformacao, int codTarefa, string descricao, Data dataInsercao, int codUtilizador);
	Informacao(const Informacao &i);
	~Informacao();

	int getCodInformacao() const;
	int getCodTarefa() const;
	string getDescricao() const;
	Data& getDataInsercao();
	int getCodUtilizador() const;

	void setCodUtilizador(const int cod);
	void setCodTarefa(const int cod);
	void setDescricao(const string desc);
	void setDataInsercao(const Data& data);
	void setCodInformacao(const int cod);

	virtual Informacao* clone() const;
	void escreve(ostream &out) const;
};


/**
 * Construtor vazio.
 */
Informacao::Informacao()
{
}   


/**
 * Construtor completo
 * @param 	codInformacao 	codigo da informacao
 * @param 	codTarefa 		codigo da tarefa
 * @param 	descricao 		descricao da informacao
 * @param 	dataIns 		data em que a informacao foi inserida no sistema
 * @param 	codUtilizador 	codigo do utilizador
 */
Informacao::Informacao(int codInformacao, int codTarefa, string descricao, Data dataIns, int codUtilizador)
{
	setCodInformacao(codInformacao);
	setCodTarefa(codTarefa);
	setDescricao(descricao);
	setDataInsercao(dataIns);
	setCodUtilizador(codUtilizador);
}


/**
 * Construtor copia.
 * @param 	i 		objecto Informacao a ser copiado
 */
Informacao::Informacao(const Informacao &i)
{
	codInformacao = i.codInformacao;
	descricao = i.descricao;
}


/**
 * Destrutor
 */
Informacao::~Informacao()
{
}


/**
 * retorna o codigo da informacao
 * @return 	devolve o codigo da informacao
 */
int Informacao::getCodInformacao() const
{
	return codInformacao;	
}


/**
 * Metodo para retornar a descricao da informacao.
 * @return 	retorna a descricao da informacao
 */
string Informacao::getDescricao() const
{	
	return descricao;
}


/**
 * Metodo de atribuicao do codigo da informacao
 * @param 	cod 	codigo da informacao
 */
void Informacao::setCodInformacao(const int cod)
{
	codInformacao = cod;
}


/**
 * Metodo de atribuicao de uma descricao a informacao
 * @param 	desc 	descricao da informacao
 */
void Informacao::setDescricao(const string desc)
{
	descricao = desc;
}


/** 
 * Metodo de atribuicao de um codigo de utilizador a informacao
 * @param 	cod 	codigo de utilizador
 */
void Informacao::setCodUtilizador(const int cod)
{
	codUtilizador=cod;
}


/**
 * retorna o codigo de utilizador
 * @return 	devolve o codigo do utilizador de uma dada informacao
 */
int Informacao::getCodUtilizador() const
{
	return codUtilizador;
}


/**
 * Metodo de atribuicao codigo de tarefa
 * @param 	cod 	codigo da tarefa 
 */
void Informacao::setCodTarefa(const int cod)
{
	codTarefa=cod;
}


/**
 * Metodo para retornar codigo de tarefa
 * @return 	devolve o codigo de tarefa
 */
int Informacao::getCodTarefa() const
{
	return codTarefa;
}


/**
 * Metodo para alterar data de insercao
 * @param 	data 	data de insercao da informacao
 */
void Informacao::setDataInsercao(const Data& data)
{
	dataInsercao=data;
}


/**
 * Metodo para retornar a data de insercao	
 * @return 	retorna a data de insercao
 */
Data& Informacao::getDataInsercao()
{
	return dataInsercao;
}


/**
 * Apresenta os dados da informacao
 * @param out 	objecto stream out
 */
void Informacao::escreve(ostream &out)const
{
	out << "Informacao: " << codInformacao << endl;
	out << "Descricao: " << descricao << endl;
	out << "Data de Insercao: "; dataInsercao.listar();
	out << "Codigo de Utilizador: " << codUtilizador << endl;
} 


/**
 * Sobrecarga do operador stream out
 * @param out	object stream out
 * @param i 	objecto Informacao
 */
ostream & operator << (ostream &out, const Informacao &i)
{
	i.escreve(out);
	return out;
}


/**
 * copia um objecto do tipo Informacao
 * @return 	devolve apontador para novo objecto Informacao
 */
Informacao* Informacao::clone() const
{
	return new Informacao(*this);
}

#endif