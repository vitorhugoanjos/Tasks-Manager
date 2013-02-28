/**
 * @author Vitor Hugo
 * @date 13/01/2013 
 * @file Calendario.h 
 * Classe responsavel por importacoes e exportacoes iCal
 */ 

#ifndef CALENDARIO_H
#define CALENDARIO_H

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

class Calendario
{

private:

public:

	int exportar(string nomeFicheiro, int codUser);
};

/**
 * Metodo responsavel pela exportacao das tarefas da base de dados para o calendario.
 * @param  nomeFicheiro nome do ficheiro.
 * @param  codUser      codigo do utilizador
 * @return              retorna 0 se exportar com sucesso, -1 caso contrario.
 */
int Calendario::exportar(string nomeFicheiro, int codUser)
{

	string beginCal = "BEGIN:VCALENDAR\n";
	string beginEv = "BEGIN:VEVENT\n";
	string version = "VERSION:2.0\n";
	string estado = "STATUS:";
	string dInicio = "DTSTART:";
	string dFim = "DTEND:";
	string titulo = "SUMMARY:";
	string desc = "DESCRIPTION:";
	string contexto = "LOCATION:";
	string codigo = "UID:";
	string endEv = "END:VEVENT\n";
	string endCal = "END:VCALENDAR\n";
	string hora1 = "T030000Z";
	string hora2 = "T020000Z";

	string linha;
	string _nomeFicheiro;
	stringstream out;
	string dataFim;
	string _estado;
	string _user;
	string dataI;
	string dataF;
	Lista<Tarefa> tarefas;
	Lista<Projecto> projectos;
	Tarefa tarefa;
	Projecto projecto;


	out << nomeFicheiro << ".ical";
	_nomeFicheiro = out.str();
	ofstream  ficheiro(_nomeFicheiro);

	if(ficheiro.is_open())
	{
		try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				tarefas = conexao ->listarTarefasTodas(codUser);
				projectos = conexao ->listarProjectos(codUser);
				estado = conexao ->getEstado(tarefa.getCodEstado());
				delete(conexao);
			} 
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

		ficheiro << beginCal << "";
		ficheiro << "PRODID:-//Google Inc//Google Calendar 70.9054//EN\n";
		ficheiro << version << "" ;
		ficheiro << "CALSCALE:GREGORIAN\nMETHOD:PUBLISH\n";
		 

		for(int i = 1; i< tarefas.comprimento()+1; i++)
		{
			
			tarefas.encontra(i, tarefa);

			
			try
			{
				BDados *conexao = new BDados ("B2-7", "queroarroz", "193.136.62.27:1521/isepdb");
				_estado = conexao ->getEstado(tarefa.getCodEstado());
				_user = conexao ->getUser(codUser);
				delete(conexao);
			}
			catch(SQLException erro)
			{
				cerr << "Erro: " << erro.getMessage() << endl;
			}

			if(tarefa.getDataFim().getAno() != 1900)
				ficheiro << beginEv << dInicio << tarefa.getDataCriacao().getAno() << tarefa.getDataCriacao().getMes() << tarefa.getDataCriacao().getDia() << hora1 << "\n" << dFim <<  tarefa.getDataFim().getAno() << tarefa.getDataFim().getMes() << tarefa.getDataFim().getDia() << hora1 << "\n";
			else
				ficheiro << beginEv << dInicio << tarefa.getDataCriacao().getAno() << tarefa.getDataCriacao().getMes() << tarefa.getDataCriacao().getDia() << hora1 << "\n" << dFim <<  tarefa.getDataCriacao().getAno() << tarefa.getDataCriacao().getMes() << tarefa.getDataCriacao().getDia() << hora1 << "\n";
			ficheiro << "DTSTAMP:" << tarefa.getDataCriacao().getAno() << tarefa.getDataCriacao().getMes() << tarefa.getDataCriacao().getDia() << "T013716Z" << "\n";
			ficheiro << "STATUS:" <<  _estado << "\n";
			ficheiro << titulo << tarefa.getTitulo() << "\n";
			ficheiro << desc << tarefa.getInformacao() << "\n";
			ficheiro << codigo << "tarefa-" << tarefa.getCodTarefa() << "c2fbb1a7@" << _user << "\nTRANSP:OPAQUE\n";
			ficheiro << endEv << "";

		}

		ficheiro << endCal << "";
		ficheiro.close();
	}

	return 0;
}

#endif
