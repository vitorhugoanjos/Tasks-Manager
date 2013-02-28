/**
*@author Andre Silva
*@date 20/12/2012
*@file main.c
*Ficheiro onde serao processadas as funcoes principais de importacao e tratamento de dados.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct
{
	int numeroAcao;
	int prioAcao;
	int contexto;
	char nomeAcao[50];
}tarefa;

#include "modulo.h"

/**
*@param string apontador onde esta guardado um array de carateres a ser convertido
*@return retorna o valor que foi convertido para decimal
*Funcao que converte determinada string que tera um numero em binario e que o ira converter em decimal e retornado.
*/
int binConvert(char *string)
{
	int pos = 0, valor = 0;

	for (pos = 0; string[pos] != 0; ++pos)
	{
		///Caso o valor na posicao da string seja '1', ele ira converter para decimal e somar ao valor de retorno
		if(string[pos] == '1')
			valor += (int)pow(2.0, (double)pos);
	}

	return valor;
}

/**
*@param tar Apontador de apontador que passa por parametro o endereco de memoria do array de structs onde serao guardados os valores do csv.
*@return retorna o tamanho da estrutura definida
*Funcao que retira os valores de uma linha de csv e que os ira guardar num array de estruturas do tipo tarefa
*/
int lerFicheiro(tarefa **tar)
{
	tarefa *temp = *tar;
	int tamanho = 0;
	FILE *ficheiro;
	char *strTemp, *str;

	strTemp=(char *)malloc(sizeof(char)*150);
	ficheiro = fopen("FX.csv", "r");
	///Caso ocorra algum erro na importacao, dara um erro de Ficheiro vazio.
	if(ficheiro == NULL)
	{
		printf("Ficheiro vazio");

		return 0;
	}
	///Ciclo que ira percorrer todas as linhas do ficheiro
	while(!feof(ficheiro))
	{
		fgets(strTemp, 150, ficheiro);
		if(strTemp != NULL)
		{
			temp = (tarefa *)realloc(*tar, sizeof(tarefa)*(tamanho+2));
			if(temp == NULL)
			{
				printf("Erro na alocacao de memoria");

				return 0;
			}
			*tar=temp;
			///usou-se o strtok para dividir cada linha pelos atributos da struct
			str = strtok(strTemp, ",");
			(*tar)[tamanho].numeroAcao = atoi(str);
			str = strtok(NULL, ",");
			strncpy((*tar)[tamanho].nomeAcao, str, 50);		
			str = strtok(NULL, ",");
			(*tar)[tamanho].prioAcao = atoi(str);
			str = strtok(NULL, ",");
			(*tar)[tamanho].contexto = binConvert(str);
			tamanho++;
		}
		
	}	
	fclose(ficheiro);

	return tamanho;
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que serve como interface para a funcao em Assembly que ira mostrar os contextos de uma determinada acao
*/
void mContextos(tarefa *tar, int tamanho)
{
	int *contextos, i, acao, nAcao = -1;

	system("clear");
	printf("Insira a acao a consultar:\n");
	scanf("%d", &acao);
	for (i = 0; i < tamanho; ++i)
	{
		if(acao == tar[i].numeroAcao)
			nAcao = i;
	}
	if(nAcao == -1)
		printf("Acao nao encontrada.\n");
	else
	{
		contextos = (int *)malloc(sizeof(int)*32);
		for (i = 0; i < 32; ++i)
		{
			contextos[i]=0;
		}
		mostraContexto(tar,sizeof(tarefa), nAcao, contextos);
		printf("Contextos da acao %d:\n", acao);
		for (i = 0; contextos[i]!=0; ++i)
		{
			printf("%d ", contextos[i]);
		}
		printf("\n");
	}
	getchar();
	while(getchar() != '\n');
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que serve como interface para a funcao em Assembly que ira mostrar o maior contexto de uma determinada acao
*/
void mMaiorContextos(tarefa *tar, int tamanho)
{
	int mCont, acao, nAcao = -1, i;

	system("clear");
	printf("Insira a acao a consultar:\n");
	scanf("%d", &acao);
	for (i = 0; i < tamanho; ++i)
	{
		if(acao == tar[i].numeroAcao)
			nAcao = i;
	}
	if(nAcao == -1)
		printf("Acao nao encontrada.\n");
	else
	{
		mCont = maiorContexto(tar, sizeof(tarefa), nAcao);
		printf("Maior Contexto da acao %d: %d\n", acao, mCont);
	}
	getchar();
	while(getchar() != '\n');
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que serve como interface para a funcao em Assembly que ira mostrar o numero de contextos de uma determinada acao
*/
void mNumContextos(tarefa *tar, int tamanho)
{
	int nCont, acao, nAcao = -1, i;

	system("clear");
	printf("Insira a acao a consultar:\n");
	scanf("%d", &acao);
	for (i = 0; i < tamanho; ++i)
	{
		if(acao == tar[i].numeroAcao)
			nAcao = i;
	}
	if(nAcao == -1)
		printf("Acao nao encontrada.\n");
	else
	{
		nCont = numContexto(tar, sizeof(tarefa), nAcao);
		printf("Numero de contextos: %d\n", nCont);
	}
	getchar();
	while(getchar() != '\n');	
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que serve como interface para a funcao em Assembly que ira mostrar o numero de acoes com uma determinada prioridade
*/
void mPrioridades(tarefa *tar, int tamanho)
{
	int nPrio, prioridade;

	system("clear");
	printf("Insira a prioridade a consultar:\n");
	scanf("%d", &prioridade);
	nPrio = numPrio(tar, sizeof(tarefa), tamanho, prioridade);
	printf("Numero de prioridades %d: %d\n", prioridade, nPrio);
	getchar();
	while(getchar() != '\n');
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que serve como interface para mostrar listagem de acoes
*/
void mListagem(tarefa *tar, int tamanho)
{
	int i;

	system("clear");
	printf("Listagem de acoes:\n");
	printf("Numero\tPrioridade\tContexto\tNome\n");
	for (i = 0; i < tamanho; ++i)
	{
		printf("%d\t%d\t\t%X\t\t%s\n", tar[i].numeroAcao, tar[i].prioAcao, tar[i].contexto, tar[i].nomeAcao);
	}
	getchar();
	while(getchar() != '\n');
}

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanho Tamanho da estrutura de dados de tarefa
*Funcao que funciona como menu da aplicacao
*/
void menu(tarefa *tar, int tamanho)
{
	int opcao;

	do{
		system ("clear");
		printf("----- MENU -----\n");
		printf("1 - Contextos de uma acao.\n");
		printf("2 - Maior contexto de uma acao.\n");
		printf("3 - Numero de contextos de uma acao.\n");
		printf("4 - Numero de acoes de uma dada prioridade.\n");
		printf("5 - Listagem das accoes\n");
		printf("0 - Sair\n");
		scanf("%d", &opcao);
		switch (opcao)
		{
			case 1:
				mContextos(tar, tamanho);
				break;
			case 2:
				mMaiorContextos(tar, tamanho);
				break;
			case 3:
				mNumContextos(tar, tamanho);
				break;
			case 4:
				mPrioridades(tar, tamanho);
				break;
			case 5:
				mListagem(tar, tamanho);
				break;
			case 0:
				printf("A sair...\n");
				break;
			default:
				break;
		}
	}while(opcao != 0);
}

/**
*@return retorna o valor do codigo do erro caso tenha. Se for 0, nao houve nenhum erro.
*Funcao principal do programa, onde faz tambem uma listagem dos valores guardados na estrutura.
*/
int main()
{
	tarefa *tar = (tarefa *)malloc(sizeof(tarefa));
	int tamanho = lerFicheiro(&tar);
	if(tamanho != 0)
		menu(tar, tamanho);

	return 0;
}
