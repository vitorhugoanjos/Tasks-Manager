/**
 * @author Joao Machado
 * @author Vitor Hugo
 * @date 21/12/2012 
 * @file Nivel.h 
 * Classe responsavel por guardar toda a informacao sobre os niveis de importancia.*/ 


#ifndef NIVEL_H
#define NIVEL_H

class Nivel
{
private:
	int nivelImportancia;
	string descricao;

public:
	Nivel();
	Nivel(int nivelImportancia, string descricao);
	Nivel(const Nivel &n);
	~Nivel();

	int getNivelImportancia() const;
	string getDescricao() const;
	void setDescricao(const string desc);
	void setNivelImportancia(const int imp);
	virtual Nivel *clone() const;
	void escreve(ostream &out) const;
};


/**
 * Construtor vazio.
 */
Nivel::Nivel()
{
	Nivel(0,"");
}


/**
 * Construtor completo.
 * @param nivelImportancia nivel de importancia.
 * @param descricao descricao do nivel de importancia.
 */
Nivel::Nivel(int nivelImportancia, string descricao)
{
	setNivelImportancia(nivelImportancia);
	setDescricao(descricao);
}


/**
 * Construtor copia.
 * @param 	n 	objecto Nivel a ser copiado.
 */
Nivel::Nivel(const Nivel &n)
{
	nivelImportancia = n.nivelImportancia;
	descricao = n.descricao;
}


/**
 * Destrutor
 */
Nivel::~Nivel()
{
}


/**
 * Metodo para retornar o nivel de importancia
 * @return 	devolve o nivel de importancia
 */
int Nivel::getNivelImportancia() const
{
	return nivelImportancia;
}


/**
 * Metodo para retornar a descricao do nivel de importancia
 * @return 	devolve descricao do nivel de importancia
 */
string Nivel::getDescricao() const
{	
	return descricao;
}


/**
 * Metodo de atribuicao do nivel de importancia
 */
void Nivel::setNivelImportancia(const int imp)
{
	nivelImportancia = imp;
}


/**
 * Metodo de atribuicao de uma descricao ao nivel de importancia
 * @param 	desc 	descricao do nivel de importancia
 */
void Nivel::setDescricao(const string desc)
{
	descricao = desc;
}


/**
 * Apresenta os dados do nivel de importancia.
 * @param 	out 	objecto de stream out
 */
void Nivel::escreve(ostream &out) const
{
	out << "Nivel de importancia: " << nivelImportancia << endl;
	out << "Descricao: " << descricao << endl;
} 


/**
 * Sobrecarga do operador stream out
 * @param	out 	objecto de stream out
 * @param 	n 		objecto Nivel
 */
ostream & operator << (ostream &out, const Nivel &n)
{
	n.escreve(out);
	return out;
}


/**
 * metodo clone
 * @return 	devolve apontador para objecto Nivel
 */
Nivel* Nivel::clone() const
{
	return new Nivel(*this);

}

#endif