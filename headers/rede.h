#ifndef REDE_H
#define REDE_H

#include "graph.h"

typedef struct rede Rede;

/**
 * Cria uma Rede a partir de um arquivo de entrada.
 *
 * @param input O arquivo de entrada contendo as informações da Rede.
 * @return Um ponteiro para a Rede criada.
 */
Rede *rede_create_from_file(FILE *input);

/**
 * Calcula a inflação do RTT (Round-Trip Time) para cada conexão entre servidor e cliente na Rede e escreve os resultados em um arquivo de saída.
 *
 * @param r O ponteiro para a Rede.
 * @param output O arquivo de saída onde os resultados serão escritos.
 */
void rede_calc_inflacao_RTT(Rede *r, FILE *output);

/**
 * Calcula o RTT real entre um servidor e um cliente na rede.
 *
 * @param r Ponteiro para a estrutura Rede contendo informações da rede.
 * @param dist_servidor Matriz de distâncias entre servidores e clientes.
 * @param dist_cliente Matriz de distâncias entre clientes e servidores.
 * @param servidor Índice do servidor na matriz de distâncias.
 * @param cliente Índice do cliente na matriz de distâncias.
 * @return O valor do RTT real entre o servidor e o cliente.
 */
double rede_RTT_real(Rede *r, double **dist_servidor, double **dist_cliente, int servidor, int cliente);

/**
 * Calcula o RTT estrela para uma determinada rede.
 *
 * Esta função calcula o RTT estrela para uma rede específica, com base nas distâncias entre os servidores, clientes e monitores.
 * O RTT estrela é definido como o menor tempo de ida e volta (RTT) entre um servidor, um monitor e um cliente.
 *
 * @param r Um ponteiro para a estrutura Rede que representa a rede.
 * @param dist_servidor Uma matriz de distâncias entre os servidores e os monitores.
 * @param dist_cliente Uma matriz de distâncias entre os clientes e os monitores.
 * @param dist_monitor Uma matriz de distâncias entre os monitores e os servidores/clientes.
 * @param servidor O índice do servidor na matriz de servidores da rede.
 * @param cliente O índice do cliente na matriz de clientes da rede.
 * @return O valor do RTT estrela para a rede.
 */
double rede_RTT_estrela(Rede *r, double **dist_servidor, double **dist_cliente, double **dist_monitor, int servidor, int cliente);

/**
 * Libera a memória alocada para a Rede.
 *
 * @param r O ponteiro para a Rede a ser liberada.
 */
void rede_destroy(Rede *r);

#endif 