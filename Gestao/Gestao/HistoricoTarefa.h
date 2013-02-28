/**
*@author Tiago Pacheco
*@author Vitor Hugo
*@date 14/01/2013 
*@file HistoricoTarefa.h 
*Classe responsavel por guardar todo o historico das tarefas
*/ 

#ifndef HistoricoTarefa_H
#define HistoricoTarefa_H
#include <iostream>
#include <string>
using namespace std;
#include "Data.h"


class HistoricoTarefa
{
private:
 int codHistorico;
 int codTarefa;
 int codProjecto;
 int codEstado;
 int nivelImportancia;
 int duracao;
 int dependente;
 int nContexto;
 int delegado;
 int codTipo;
 int codUtilizador;
 Data dataInsercao;
 Data dataInicio;
 Data dataFim;
 Data dataEstimada;
 string informacao;
 string info;
 string tipo;
 string titulo;

public:
 HistoricoTarefa(int codhistorico, int codtarefa, int codprojecto, int codestado, int nivelimportancia, Data datacriacao, Data datafim, string informacao, Data dataestimada, int duracao, string tipo, string titulo, int dependente, int codutilizador, int ncontexto, int delegado, Data datainsercao, int codtipo, string info);
 HistoricoTarefa();
 HistoricoTarefa(const HistoricoTarefa& ht);
 ~HistoricoTarefa();

 int getCodHistorico()const;
 int getCodTarefa() const;
 int getCodProjecto() const;
 int getCodEstado() const;
 int getCodUtilizador() const;
 int getNivelImportancia() const;
 int getDuracao() const;
 int getDependente()const;
 int getNContexto()const;
 int getDelegado()const;
 int getCodTipo()const;
 Data getDataInicio();
 Data getDataFim();
 Data getDataEstimada();
 Data getDataInsercao();
 string getInformacao() const;
 string getInfo() const;

 string getTipo()const;
 string getTitulo()const;

 void setCodHistorico(const int codhistorico);
 void setCodTarefa(const int codtarefa) ;
 void setCodProjecto(const int codprojecto) ;
 void setCodEstado(const int codestado) ;
 void setCodUtilizador(const int codutilizador) ;
 void setNivelImportancia(const int nivelimportancia) ;
 void setDuracao(const int duracao) ;
 void setDependente(const int dependente);
 void setNContexto(const int ncontexto);
 void setDelegado(const int delegado);
 void setCodTipo(const int codtipo);
 void setDataInicio(const Data dataInicio);
 void setDataFim(const Data datafim);
 void setDataEstimada(const Data dataestimada);
 void setDataInsercao(const Data datainsercao);
 void setInformacao(const string informacao) ;
 void setInfo(const string info);
 void setTipo(const string tipo);
 void setTitulo(const string titulo);

 virtual HistoricoTarefa *clone() const;
 void escreve(ostream &out) const;

};

/**
 *Construtor vazio
 */
HistoricoTarefa::HistoricoTarefa()
{
	HistoricoTarefa(0,0,0,0,0,Data(),Data(),"",Data(),0,"","",0,0,0,0,Data(),0,"");
}

/**
 *Construtor completo
 *@param codhistorico 		codigo de historico
 *@param codtarefa 			codigo de tarefa
 *@param codprojecto 		codigo de projecto
 *@param codestado 			codigo de estado
 *@param nivelimportancia 	nivel de importancia
 *@param datacriacao		data de criacao
 *@param datafim 			data de conclusao
 *@param informacao 		informacao
 *@param dataestimada 		data estimada
 *@param duracao 			duracao
 *@param tipo 				tipo
 *@param titulo 			titulo
 *@param dependente 		dependente
 *@param codutilizador 		codigo de utilizador
 *@param ncontexto  		numero de contexto
 *@param delegado 			delegado
 *@param datainsercao 		data de insercao
 *@param codtipo 			codigo do tipo
 *@param info 				informacao
 */
HistoricoTarefa::HistoricoTarefa(int codhistorico, int codtarefa, int codprojecto, int codestado, int nivelimportancia, Data datacriacao, Data datafim, string informacao, Data dataestimada, int duracao, string tipo, string titulo, int dependente, int codutilizador, int ncontexto, int delegado, Data datainsercao, int codtipo, string info)
{
 setCodHistorico(codhistorico);
 setCodTarefa(codtarefa) ;
 setCodProjecto(codprojecto) ;
 setCodEstado(codestado) ;
 setCodUtilizador(codutilizador) ;
 setNivelImportancia(nivelimportancia) ;
 setDuracao(duracao) ;
 setDependente(dependente);
 setNContexto(ncontexto);
 setDelegado(delegado);
 setCodTipo(codtipo);
 setDataInicio(datacriacao);
 setDataFim(datafim);
 setDataEstimada(dataestimada);
 setDataInsercao(datainsercao);
 setInformacao(informacao) ;
 setInfo(info) ;

 setTipo(tipo);
 setTitulo(titulo);
}

/**
 *Construtor copia
 * @param objeto ht do tipo HistoricoTarefa a ser copiado
 */
HistoricoTarefa::HistoricoTarefa(const HistoricoTarefa& ht)
{
	codHistorico= ht.codHistorico;
	codTarefa= ht.codTarefa;
	codProjecto= ht.codProjecto;
	codEstado= ht.codEstado;
	nivelImportancia= ht.nivelImportancia;
	duracao= ht.duracao;
	dependente= ht.dependente;
	nContexto= ht.nContexto;
	delegado= ht.delegado;
	codTipo= ht.codTipo;
	codUtilizador= ht.codUtilizador;
	dataInsercao= ht.dataInsercao;
	dataInicio= ht.dataInicio;
	dataFim= ht.dataFim;
	dataEstimada= ht.dataEstimada;
	informacao= ht.informacao;
	info= ht.info;
	tipo= ht.tipo;
	titulo= ht.titulo;
}

/**
* Destrutor.
*/
HistoricoTarefa::~HistoricoTarefa()
{
}

/**
 * Metodo para retornar o codigo de historico.
 * @return devolve o codigo de historico.
 */
int HistoricoTarefa::getCodHistorico()const
{
 return codHistorico;
}

/**
 * Metodo para retornar o codigo de tarefa.
 * @return devolve o codigo de tarefa.
 */
int HistoricoTarefa::getCodTarefa() const
{
 return codTarefa;
}

/**
 * Metodo para retornar o codigo de projecto.
 * @return devolve o codigo de projecto.
 */
int HistoricoTarefa::getCodProjecto() const
{
 return codProjecto;
}

/**
 * Metodo para retornar o codigo de estado.
 * @return devolve o codigo de estado.
 */
int HistoricoTarefa::getCodEstado() const
{
 return codEstado;
}

/**
 * Metodo para retornar o nivel de importancia.
 * @return devolve o nivel de importancia.
 */
int HistoricoTarefa::getNivelImportancia() const
{
 return nivelImportancia;
}

/**
 * Metodo para retornar a data de inicio.
 * @return devolve a data de inicio.
 */
Data HistoricoTarefa::getDataInicio()
{
 return dataInicio;
}

/**
 * Metodo para retornar a data de conclusao.
 * @return devolve a data de conclusao.
 */
Data HistoricoTarefa::getDataFim()
{
 return dataFim;
}

/**
 * Metodo para retornar a data estimada.
 * @return devolve a data estimada.
 */
Data HistoricoTarefa::getDataEstimada()
{
 return dataEstimada;
}

/**
 * Metodo para retornar a data de insercao.
 * @return devolve a data de insercao.
 */
Data HistoricoTarefa::getDataInsercao()
{
 return dataInsercao;
}

/**
 * Metodo para retornar a informacao.
 * @return devolve a informacao.
 */
string HistoricoTarefa::getInformacao() const
{
 return informacao;
}

/**
 * Metodo para retornar a duracao.
 * @return devolve a duracao.
 */
int HistoricoTarefa::getDuracao() const 
{
	return duracao;
}

/**
 * Metodo para retornar o tipo.
 * @return devolve o tipo.
 */
string HistoricoTarefa::getTipo() const 
{
	return tipo;
}

/**
 * Metodo para retornar o titulo.
 * @return devolve o titulo.
 */
string HistoricoTarefa::getTitulo() const 
{
	return titulo;
}

/**
 * Metodo para retornar a tarefa dependente.
 * @return devolve a tarefa dependente.
 */
int HistoricoTarefa::getDependente() const 
{
	return dependente;
}

/**
 * Metodo para retornar o codigo de utilizador.
 * @return devolve o codigo de utilizador.
 */
int HistoricoTarefa::getCodUtilizador() const 
{
	return codUtilizador;
}

/**
 * Metodo para retornar o numero de contexto.
 * @return devolve o numero de contexto.
 */
int HistoricoTarefa::getNContexto() const 
{
	return nContexto;
}

/**
 * Metodo para retornar o delegado.
 * @return devolve o delegado.
 */
int HistoricoTarefa::getDelegado() const 
{
	return delegado;
}

/**
 * Metodo para retornar o codigo de tipo.
 * @return devolve o codigo de tipo.
 */
int HistoricoTarefa::getCodTipo() const 
{
	return codTipo;
}

/**
 * Metodo para retornar a informacao.
 * @return devolve a informacao.
 */
string HistoricoTarefa::getInfo() const 
{
	return info;
}

/**
 * Metodo de atribuicao do codigo de historico.
 * @param codhistorico codigo de historico.
 */
void HistoricoTarefa::setCodHistorico(const int codhistorico)
{
	codHistorico = codhistorico;
}

/**
 * Metodo de atribuicao do codigo de tarefa.
 * @param codtarefa codigo de tarefa.
 */
void HistoricoTarefa::setCodTarefa(const int codtarefa) 
{
	codTarefa = codtarefa;
}

/**
 * Metodo de atribuicao do codigo de projecto.
 * @param codprojecto codigo de projecto.
 */
void HistoricoTarefa::setCodProjecto(const int codprojecto) 
{
	codProjecto = codprojecto;
}

/**
 * Metodo de atribuicao do codigo de estado.
 * @param codestado codigo de estado.
 */
void HistoricoTarefa::setCodEstado(const int codestado) 
{
	codEstado = codestado;
}

/**
 * Metodo de atribuicao do codigo de utilizador.
 * @param codutilizador codigo de utilizador.
 */
void HistoricoTarefa::setCodUtilizador(const int codutilizador) 
{
	codUtilizador = codutilizador;
}

/**
 * Metodo de atribuicao do nivel de importancia.
 * @param nivelimportancia nivel de importancia.
 */
void HistoricoTarefa::setNivelImportancia(const int nivelimportancia) 
{
	nivelImportancia = nivelimportancia;
}

/**
 * Metodo de atribuicao da duracao.
 * @param duracao duracao.
 */
void HistoricoTarefa::setDuracao(const int duracao) 
{
	this->duracao = duracao;
}

/**
 * Metodo de atribuicao da tarefa dependente.
 * @param dependente tarefa dependente.
 */
void HistoricoTarefa::setDependente(const int dependente)
{
	this->dependente = dependente;
}

/**
 * Metodo de atribuicao do numero de contexto.
 * @param ncontexto numero de contexto.
 */
void HistoricoTarefa::setNContexto(const int ncontexto)
{
	nContexto = ncontexto;
}

/**
 * Metodo de atribuicao do delegado.
 * @param delegado delegado.
 */
void HistoricoTarefa::setDelegado(const int delegado)
{
	this->delegado = delegado;
}

/**
 * Metodo de atribuicao do codigo de tipo.
 * @param codtipo codigo de tipo.
 */
void HistoricoTarefa::setCodTipo(const int codtipo)
{
	codTipo = codtipo;
}

/**
 * Metodo de atribuicao da data de inicio.
 * @param dataInicio data de inicio.
 */
void HistoricoTarefa::setDataInicio(const Data dataInicio)
{
	this->dataInicio = dataInicio;
}

/**
 * Metodo de atribuicao da data de conclusao.
 * @param datafim data de conclusao.
 */
void HistoricoTarefa::setDataFim(const Data datafim)
{
	dataFim = datafim;
}

/**
 * Metodo de atribuicao da data estimada.
 * @param dataestimada data estimada.
 */
void HistoricoTarefa::setDataEstimada(const Data dataestimada)
{
	dataEstimada = dataestimada;
}

/**
 * Metodo de atribuicao da data de insercao.
 * @param datainsercao data de insercao.
 */
void HistoricoTarefa::setDataInsercao(const Data datainsercao)
{
	dataInsercao = datainsercao;
}

/**
 * Metodo de atribuicao da informacao.
 * @param informacao informacao.
 */
void HistoricoTarefa::setInformacao(const string informacao) 
{
	this->informacao = informacao;
}

/**
 * Metodo de atribuicao da info.
 * @param codinformacao codigo de informacao.
 */
void HistoricoTarefa::setInfo(const string info) 
{
	this->info = info;
}

/**
 * Metodo de atribuicao do tipo.
 * @param tipo tipo.
 */
void HistoricoTarefa::setTipo(const string tipo)
{
	this->tipo = tipo;
}

/**
 * Metodo de atribuicao do titulo.
 * @param titulo titulo.
 */
void HistoricoTarefa::setTitulo(const string titulo)
{
	this->titulo = titulo;
}

/**
 * Apresenta os dados do historico informacao.
 * @param out objecto stream out.
 */
void HistoricoTarefa::escreve(ostream &out) const
{
	out << "Cod. Historico: " << codHistorico << endl;
	out << "Cod. Tarefa: " << codTarefa << endl;
	out << "Cod. Projecto: " << codProjecto << endl;
	out << "Cod. Estado: " << codEstado << endl;
	out << "Nivel Importancia: " << nivelImportancia << endl;
	out << "Data Inicio: ";  dataInicio.listar();
	out << "Data Estimada: ";  dataEstimada.listar();
	out << "Data Fim: ";  dataFim.listar();
	out << "Informacao: " << informacao << endl;
	out << "Duracao: " << duracao << endl;
	out << "Tipo: " << tipo << endl;
	out << "Titulo: " << titulo << endl;
	out << "Dependente: " << dependente << endl;
	out << "Cod. Utilizador: " << codUtilizador << endl;
	out << "Num Contexto: " << nContexto << endl;
	out << "Delegado: " << delegado << endl;
	out << "Data Insercao: ";  dataInsercao.listar();
	out << "Cod. Tipo: " << codTipo << endl;
	out << "Info: " << info << endl;
} 

/**
 * Sobrecarga do operador stream out.
 * @param out object stream out.
 * @param ht objecto HistoricoTarefa.
 */
ostream & operator << (ostream &out, const HistoricoTarefa &ht)
{
	ht.escreve(out);
	return out;
}

/**
 * Clone
 * @return devolve um clone.
 */
HistoricoTarefa* HistoricoTarefa::clone() const
{
	return new HistoricoTarefa(*this);

}


#endif