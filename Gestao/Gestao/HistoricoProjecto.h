/**
*@author Tiago Pacheco
*@author Vitor Hugo
*@date 14/01/2013 
*@file HistoricoProjecto.h 
*Classe responsavel por guardar todo o historico dos projectos
*/ 

#ifndef HistoricoProjecto_H
#define HistoricoProjecto_H
#include <iostream>
#include <string>
using namespace std;
#include "Data.h"


class HistoricoProjecto
{
private:
 int codHistorico;
 int codProjecto;
 int codEstado;
 int nivelImportancia;
 int codTipo;
 int codUtilizador;
 Data dataInsercao;
 Data dataInicio;
 Data dataFim;
 string informacao;
 string nome;
 string info;

public:
 HistoricoProjecto(int codhistorico, int codprojecto, int nivelimportancia, Data dataInsercao, Data dataFim, string informacao, string nome, int codEstado, int codUtilizador, Data datainicio, int codTipo, string info);
 HistoricoProjecto();
 HistoricoProjecto(const HistoricoProjecto& hp);
 ~HistoricoProjecto();

 int getCodHistorico()const;
 int getCodProjecto() const;
 int getCodEstado() const;
 int getCodUtilizador() const;
 int getNivelImportancia() const;
 int getCodTipo()const;
 Data getDataInicio();
 Data getDataFim();
 Data getDataInsercao();
 string getInformacao() const;
 string getInfo() const;
 string getNome()const;

 void setCodHistorico(const int codhistorico);
 void setCodProjecto(const int codprojecto) ;
 void setCodEstado(const int codestado) ;
 void setCodUtilizador(const int codutilizador) ;
 void setNivelImportancia(const int nivelimportancia) ;
 void setCodTipo(const int codtipo);
 void setDataInicio(const Data dataInicio);
 void setDataFim(const Data datafim);
 void setDataInsercao(const Data datainsercao);
 void setInformacao(const string informacao) ;
 void setInfo(const string info) ;
 void setNome(const string nome);

 virtual HistoricoProjecto *clone() const;
 void escreve(ostream &out) const;

};

/**
 *Construtor vazio
 */
HistoricoProjecto::HistoricoProjecto()
{
	HistoricoProjecto(0,0,0,Data(), Data(), "","",0,0,Data(),0,"");
}

/**
 *Construtor completo
 * @param 	codHistorico	    codigo do historico
 * @param 	codProjecto 		codigo do projecto
 * @param 	codEstado 			codigo de estado da tarefa
 * @param 	nivelImportancia 	nivel de importancia da tarefa
 * @param	datainsercao 		data de insercao do projecto
 * @param 	dataInicio		    data de inicio de projeto
 * @param 	dataFim 			data de conclusao da tarefa
 * @param 	informacao 			informacao sobre a tarefa
 * @param 	nome 		        nome do projecto
 * @param   codestado           codigo de estado
 * @param   codutilizador       codigo de utilizador
 * @param   codtipo             codigo do tipo
 * @param   info                info
 */
HistoricoProjecto::HistoricoProjecto(int codhistorico, int codprojecto, int nivelimportancia, Data datainsercao, Data datafim, string informacao, string nome, int codestado, int codutilizador, Data datainicio, int codtipo, string info)
{
	setCodHistorico( codhistorico);
	setCodProjecto( codprojecto) ;
	setCodEstado( codestado) ;
	setCodUtilizador( codutilizador) ;
	setNivelImportancia( nivelimportancia) ;
	setCodTipo( codtipo);
	setDataInicio( dataInicio);
	setDataFim( datafim);
	setDataInsercao( datainsercao);
	setInformacao(informacao) ;
	setInfo(info) ;
	setNome(nome);
}

/**
 *Construtor copia
 * @param objeto hp do tipo HistoricoProjecto a ser copiado
 */
HistoricoProjecto::HistoricoProjecto(const HistoricoProjecto& hp)
{
	codHistorico = hp.codHistorico;
	codProjecto = hp.codProjecto;
	codEstado = hp.codEstado;
	nivelImportancia = hp.nivelImportancia;
	codTipo = hp.codTipo;
	codUtilizador = hp.codUtilizador;
	dataInsercao = hp.dataInsercao;
	dataInicio = hp.dataInicio;
	dataFim = hp.dataFim;
	informacao = hp.informacao;
	nome = hp.nome;
	info = hp.info;
}

/**
* Destrutor.
*/
HistoricoProjecto::~HistoricoProjecto()
{
}

/**
 * Obter o codido do historico
 * @return codigo do historico
 */
int HistoricoProjecto::getCodHistorico()const
{
 return codHistorico;
}

/**
 * Obter o codigo do projecto
 *@return codigo do projecto
 */

int HistoricoProjecto::getCodProjecto() const
{
 return codProjecto;
}
/**
 * Obter o codigo do estado
 *@return codigo do estado
 */
int HistoricoProjecto::getCodEstado() const
{
 return codEstado;
}

/**
 * Obter o nivel de importancia
 *@return nivel de importancia
 */
int HistoricoProjecto::getNivelImportancia() const
{
 return nivelImportancia;
}

/**
 * Obter a data de inicio de projecto
 *@return data de inicio de projecto
 */
Data HistoricoProjecto::getDataInicio()
{
 return dataInicio;
}

/**
 * Obter a data de fim de projecto
 *@return data de fim projecto
 */
Data HistoricoProjecto::getDataFim()
{
 return dataFim;
}

/**
 * Obter a data de insercao do projecto
 *@return data de insercao
 */
Data HistoricoProjecto::getDataInsercao()
{
 return dataInsercao;
}

/**
 * Obter informacao do projecto
 *@return informacao do projecto
 */
string HistoricoProjecto::getInformacao() const
{
 return informacao;
}

/**
 * Obter o informacao da modificacao do projeto
 *@return informacao da modificacao do projeto
 */
string HistoricoProjecto::getInfo() const
{
 return info;
}

/**
 * Obter o nome do projecto
 *@return nome do projeto
 */
string HistoricoProjecto::getNome() const 
{
	return nome;
}

/**
 * Obter o codigo de utilizador
 *@return codigo de utilizador
 */
int HistoricoProjecto::getCodUtilizador() const 
{
	return codUtilizador;
}

/**
 * Obter o codigo do tipo de tarefa
 *@return codigo do tipo
 */
int HistoricoProjecto::getCodTipo() const 
{
	return codTipo;
}

/**
 * Alterar o codigo do historico
 * @param codhistorico codigo do historico
 */
 void HistoricoProjecto::setCodHistorico(const int codhistorico)
 {
 	codHistorico = codhistorico;
 }

 /**
 * Metodo de atribuicao do codigo do projecto
 * @param 	codprojecto 	codigo do projecto
 */
 void HistoricoProjecto::setCodProjecto(const int codprojecto) 
 {
 	codProjecto = codprojecto;
 }

 /**
 * Metodo de atribuicao do codigo do estado
 * @param 	codestado 	codigo do estado
 */
 void HistoricoProjecto::setCodEstado(const int codestado) 
 {
 	codEstado = codestado;
 }
 /**
 * Metodo de atribuicao do codigo do utilizador
 * @param 	codutilizador 	codigo do utilizador
 */
 void HistoricoProjecto::setCodUtilizador(const int codutilizador) 
 {
 	codUtilizador = codutilizador;
 }

 /**
 * Metodo de atribuicao do nivel de importancia
 * @param 	nivelimportancia 	nivelimportancia
 */
 void HistoricoProjecto::setNivelImportancia(const int nivelimportancia) 
 {
 	nivelImportancia = nivelimportancia;
 }
 
 /**
 * Metodo de atribuicao do codigo do tipo
 * @param 	codtipo 	codigo do tipo
 */
 void HistoricoProjecto::setCodTipo(const int codtipo)
 {
 	codTipo = codtipo;
 }

 /**
 * Metodo de atribuicao da data de inicio
 * @param 	datainicio 	data de inicio
 */
 void HistoricoProjecto::setDataInicio(const Data dataInicio)
 {
 	this->dataInicio = dataInicio;
 }

 /**
 * Metodo de atribuicao da data de fim
 * @param 	datafim 	data de fim
 */
 void HistoricoProjecto::setDataFim(const Data datafim)
 {
 	dataFim = datafim;
 }


 /**
 * Metodo de atribuicao da data de insercao
 * @param 	datainsercao 	data de insercao do projecto
 */
 void HistoricoProjecto::setDataInsercao(const Data datainsercao)
 {
 	dataInsercao = datainsercao;
 }

 /**
 * Metodo de atribuicao da informacao do projeto
 * @param 	informacao	informacao do projeto
 */
 void HistoricoProjecto::setInformacao(const string informacao) 
 {
 	this->informacao = informacao;
 }

 /**
 * Metodo de atribuicao do codigo da info
 * @param 	info 	info
 */
 void HistoricoProjecto::setInfo(const string info) 
 {
 	this->info = info;
 }


 /**
 * Metodo de atribuicao do nome
 * @param 	nome 	nome do projeto
 */
 void HistoricoProjecto::setNome(const string nome)
 {
 	this->nome = nome;
 }


/**
 * Apresenta os dados do historico informacao.
 * @param out objecto stream out.
 */
void HistoricoProjecto::escreve(ostream &out) const
{
	out << "Cod. Historico: " << codHistorico << endl;
	out << "Cod. Projecto: " << codProjecto << endl;
	out << "Cod. Estado: " << codEstado << endl;
	out << "Nivel Importancia: " << nivelImportancia << endl;
	out << "Data Inicio: ";  dataInicio.listar();
	out << "Data Fim: ";  dataFim.listar();
	out << "Informacao: " << informacao << endl;
	out << "Nome: " << nome << endl;
	out << "Cod. Utilizador: " << codUtilizador << endl;
	out << "Data Insercao: ";  dataInsercao.listar();
	out << "Cod. Tipo: " << codTipo << endl;
	out << "Info: " << info << endl;
} 

/**
 * Sobrecarga do operador stream out.
 * @param out object stream out.
 * @param hp objecto HistoricoProjecto.
 */
ostream & operator << (ostream &out, const HistoricoProjecto &hp)
{
	hp.escreve(out);
	return out;
}

/**
 * Método clone
 * @return objeto clone do tipo HistoricoProjecto
 */
HistoricoProjecto* HistoricoProjecto::clone() const
{
	return new HistoricoProjecto(*this);

}


#endif