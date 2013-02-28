/**
 * @author Joao Machado
 * @author Vitor Hugo
 * @date 21/12/2012 
 * @file Contexto.h 
 * Classe responsavel por guardar os contextos referentes as tarefas
 */ 

#ifndef CONTEXTO_H
#define CONTEXTO_H
#include <string>


class Contexto
{
private:
	int codContexto;
	string descricao;

public:
	Contexto();
	Contexto(int cod, string descricao);
	Contexto(const Contexto &c);
	~Contexto();

	int getCodContexto() const;
	string getDescricao() const;

	void setCodContexto(const int cod);
	void setDescricao(const string desc);

	virtual Contexto *clone() const;
	void escreve(ostream &out) const;
};


/**
 * Construtor vazio
 */
Contexto::Contexto()
{
	
}   


/**
 * Construtor completo.
 * @param 	cod 		codigo do contexto
 * @param 	descricao 	contexto da tarefa
 */
Contexto::Contexto(int cod, string descricao)
{
	setCodContexto(cod);
	setDescricao(descricao);
}


/**
 * Construtor copia.
 * @param 	c 	objecto Contexto a ser copiado
 */
Contexto::Contexto(const Contexto &c)
{
	codContexto = c.codContexto;
	descricao = c.descricao;
}


/**
 * Destrutor.
 */
Contexto::~Contexto()
{
}


/**
 * Metodo para retornar o codigo do contexto
 * @return 	devolve o codigo do contexto
 */
int Contexto::getCodContexto() const
{
	return codContexto;	
}

/**
 * Metodo para retornar a descricao do contexto da tarefa.
 * @return 	contexto da tarefa.
 */
string Contexto::getDescricao() const
{	
	return descricao;
}


/**
 * Metodo de atribuicao do codigo do contexto
 * @param 	cod 	codigo do contexto
 */
void Contexto::setCodContexto(const int cod)
{
	codContexto = cod;
}


/**
 * Metodo de atribuicao da descricao de um contexto
 * @param 	desc 	descricao textual do contexto
 */
void Contexto::setDescricao(const string desc)
{
	descricao = desc;
}


/**
 * escreve os dados do contexto
 * @param 	out 	objecto de stream out
 */
void Contexto::escreve(ostream &out) const
{
	cout << "Contexto: " << codContexto << endl;
	cout << "Descricao: " << descricao << endl;
	
} 


/**
 * Sobrecarga do operador stream out
 * @param 	out 	objecto stream out
 * @param 	c 		objecto Contexto
 * @return 	devolve objecto de stream out
 */
ostream & operator << (ostream &out, const Contexto &c)
{
	c.escreve(out);
	return out;
}


/**
 * copia um objecto do tipo Contexto
 * @return 	devolve apontador para objecto do tipo Contexto
 */
Contexto* Contexto::clone() const
{
	return new Contexto(*this);

}

#endif