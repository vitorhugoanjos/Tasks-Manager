/**
*@author Andre Silva
*@date 21/12/2012
*@file modulo.h
*Ficheiro que ira apresentar os cabecalhos das funcoes em Assembly.
*/

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanhoEst Tamanho do tipo de dados de tarefa
*@param posicao Posicao na estrutura da acao que se quer consultar
*@return retorna o valor do maior contexto
*Funcao que ira retornar o maior contexto de uma determinada acao
*/
int maiorContexto(tarefa *tar, int tamanhoEst, int posicao);

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanhoEst Tamanho do tipo de dados de tarefa
*@param posicao Posicao na estrutura da acao que se quer consultar
*@return retorna o numero de contextos
*Funcao que ira retornar o numero de contextos de uma determinada acao
*/
int numContexto(tarefa *tar, int tamanhoEst, int posicao);

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanhoEst Tamanho do tipo de dados de tarefa
*@param posicao Posicao na estrutura da acao que se quer consultar
*@param contexto Apontador de um array de contextos onde ira fucar guardado o numero do contexto
*Funcao que ira armazenar num array os contextos de uma determinada acao
*/
void mostraContexto(tarefa *tar, int tamanhoEst, int posicao, int *contexto);

/**
*@param tar Apontador que passa por parametro o endereco de memoria do array
*@param tamanhoEst Tamanho do tipo de dados de tarefa
*@param tamanho Tamanho do array de tarefas
*@param prioridade Prioridade a ser consultada
*@return retorna o numero de prioridades
*Funcao que ira retornar o numero de accoes com uma determinada prioridade
*/
int numPrio(tarefa *tar, int tamanhoEst, int tamanho, int prioridade);
