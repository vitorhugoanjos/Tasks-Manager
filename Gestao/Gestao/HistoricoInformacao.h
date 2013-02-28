/**
*@author Tiago Pacheco
*@date 14/01/2013 
*@file HistoricoInformacao.h 
*Classe responsavel por guardar todo o historico das informacoes
*/ 

#ifndef HistoricoInformacao_H
#define HistoricoInformacao_H
#include <iostream>
#include <string>
using namespace std;
#include "Data.h"


class HistoricoInformacao
{
private:
 int codHistorico;
 int codInformacao;
 int codTarefa;
 int codTipo;
 int codUtilizador;
 Data dataInsercao;
 string info;
 string descricao;

public:
 HistoricoInformacao(int codhistorico, int codinformacao, int codtarefa, string desc, int codutilizador, Data datainsercao, int codtipo, string info);
 HistoricoInformacao();
 HistoricoInformacao(const HistoricoInformacao& hi);
 ~HistoricoInformacao();

 int getCodHistorico()const;
 int getCodInformacao() const;
 int getCodTarefa() const;
 int getCodTipo() const;
 int getCodUtilizador() const;
 Data getDataInsercao();
 string getInfo() const;
 string getDescricao() const;

 void setCodHistorico(const int codhistorico);
 void setCodInformacao(const int codinformacao);
 void setCodTarefa(const int codtarefa);
 void setDescricao(const string descricao);
 void setCodUtilizador(const int codutilizador);
 void setDataInsercao(const Data datainsercao);
 void setCodTipo(const int codtipo);
 void setInfo(const string info);

 virtual HistoricoInformacao *clone() const;
 void escreve(ostream &out) const;

};

/**
 *Construtor vazio
 */
HistoricoInformacao::HistoricoInformacao()
{
	HistoricoInformacao(0,0,0,"",0,Data(),0,"");
}

/**
 *Construtor completo
 *@param codhistorico 	codigo de historico
 *@param codinformacao 	codigo da informacao
 *@param codtarefa 		codigo da tarefa
 *@param descricao 		descricao
 *@param codutilizador 	codigo do utilizador
 *@param datainsercao 	data de insercao
 *@param codtipo 		codigo do tipo
 *@param info 			informacao
 */
HistoricoInformacao::HistoricoInformacao(int codhistorico, int codinformacao, int codtarefa, string descricao, int codutilizador, Data datainsercao, int codtipo, string info)
{
 setCodHistorico(codhistorico);
 setCodInformacao(codinformacao);
 setCodTarefa(codtarefa);
 setDescricao(descricao);
 setCodUtilizador(codutilizador);
 setDataInsercao(datainsercao);
 setCodTipo(codtipo);
 setInfo(info);
}

/**
 *Construtor copia
 * @param objeto hi do tipo HistoricoInformacao a ser copiado
 */
HistoricoInformacao::HistoricoInformacao(const HistoricoInformacao& hi)
{
 codHistorico=hi.codHistorico;
 codInformacao=hi.codInformacao;
 codTarefa=hi.codTarefa;
 descricao=hi.descricao;
 codUtilizador=hi.codUtilizador;
 dataInsercao=hi.dataInsercao;
 codTipo=hi.codTipo;
 info=hi.info;
}

/**
* Destrutor.
*/
HistoricoInformacao::~HistoricoInformacao()
{
}

/**
 * Metodo para retornar o codigo do historico.
 * @return devolve o codigo do historico.
 */
int HistoricoInformacao::getCodHistorico()const
{
 return codHistorico;
}

/**
 * Metodo para retornar o codigo da informacao.
 * @return devolve o codigo da informacao.
 */
int HistoricoInformacao::getCodInformacao() const
{
 return codInformacao;
}

/**
 * Metodo para retornar o codigo da tarefa.
 * @return devolve o codigo da tarefa.
 */
int HistoricoInformacao::getCodTarefa() const
{
 return codTarefa;
}

/**
 * Metodo para retornar a descricao.
 * @return devolve a descricao.
 */
string HistoricoInformacao::getDescricao() const
{
 return descricao;
}

/**
 * Metodo para retornar o codigo do utilizador.
 * @return devolve o codigo de utilizador.
 */
int HistoricoInformacao::getCodUtilizador() const
{
 return codUtilizador;
}

/**
 * Metodo para retornar a data de insercao.
 * @return devolve a data de insercao.
 */
Data HistoricoInformacao::getDataInsercao()
{
 return dataInsercao;
}

/**
 * Metodo para retornar o codigo do tipo.
 * @return devolve o codigo do tipo.
 */
int HistoricoInformacao::getCodTipo() const
{
 return codTipo;
}

/**
 * Metodo para retornar a info.
 * @return devolve a info.
 */
string HistoricoInformacao::getInfo() const
{
 return info;
}

/**
 * Metodo de atribuicao do codigo de historico.
 * @param codhistorico codigo do historico.
 */
void HistoricoInformacao::setCodHistorico(const int codhistorico)
{
	codHistorico = codhistorico;
}

/**
 * Metodo de atribuicao do codigo de informacao.
 * @param codinformacao codigo de informacao.
 */
void HistoricoInformacao::setCodInformacao(const int codinformacao)
{
	codInformacao = codinformacao;
}

/**
 * Metodo de atribuicao do codigo de tarefa.
 * @param codtarefa codigo de tarefa.
 */
void HistoricoInformacao::setCodTarefa(const int codtarefa)
{
	codTarefa = codtarefa;
}

/**
 * Metodo de atribuicao da descricao.
 * @param descricao descricao.
 */
void HistoricoInformacao::setDescricao(const string descricao)
{
	this->descricao = descricao;
}

/**
 * Metodo de atribuicao do codigo de utilizador.
 * @param codutilizador codigo de utilizador.
 */
void HistoricoInformacao::setCodUtilizador(const int codutilizador)
{
	codUtilizador = codutilizador;
}

/**
 * Metodo de atribuicao da data de insercao.
 * @param datainsercao data de insercao.
 */
void HistoricoInformacao::setDataInsercao(const Data datainsercao)
{
	dataInsercao = datainsercao;
}

/**
 * Metodo de atribuicao do codigo de tipo.
 * @param codtipo codigo de tipo
 */
void HistoricoInformacao::setCodTipo(const int codtipo)
{
	codTipo = codtipo;
}

/**
 * Metodo de atribuicao da info.
 * @param info info.
 */
void HistoricoInformacao::setInfo(const string info)
{
	this->info = info;
}


/**
 * Apresenta os dados do historico informacao.
 * @param out objecto stream out.
 */
void HistoricoInformacao::escreve(ostream &out) const
{
	out << "Cod. Historico: " << codHistorico << endl;
	out << "Cod. Tarefa: " << codTarefa << endl;
	out << "Cod. Tipo: " << codTipo << endl;
	out << "Cod. Informacao: " << codInformacao << endl;
	out << "Cod. Utilizador: " << codUtilizador << endl;
	out << "Data Insercao: ";  dataInsercao.listar();
	out << "Informacao: " << info << endl;
	out << "Descricao: " << descricao << endl;
} 

/**
 * Sobrecarga do operador stream out.
 * @param out object stream out.
 * @param hi objecto HistoricoInformacao.
 */
ostream & operator << (ostream &out, const HistoricoInformacao &hi)
{
	hi.escreve(out);
	return out;
}

/**
 * Clone
 * @return devolve um clone.
 */
HistoricoInformacao* HistoricoInformacao::clone() const
{
	return new HistoricoInformacao(*this);

}


#endif