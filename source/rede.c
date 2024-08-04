#include "../headers/rede.h"

struct rede{
    int *servidores, *clientes, *monitores;
    int qtd_servidores, qtd_clientes, qtd_monitores;
    Graph *grafo;
};

Rede *rede_create_from_file(FILE *input){
    Rede *r = malloc(sizeof(Rede));

    int qtd_vertices = 0, qtd_edges = 0;

    fscanf(input, "%d %d", &qtd_vertices, &qtd_edges);
    fscanf(input, "%d %d %d", &r->qtd_servidores, &r->qtd_clientes, &r->qtd_monitores);

    r->servidores = malloc(r->qtd_servidores * sizeof(int));
    r->clientes = malloc(r->qtd_clientes * sizeof(int));
    r->monitores = malloc(r->qtd_monitores * sizeof(int));

    for(int i = 0; i < r->qtd_servidores; i++)
        fscanf(input, "%d", &r->servidores[i]);

    for(int i = 0; i < r->qtd_clientes; i++)
        fscanf(input, "%d", &r->clientes[i]);

    for(int i = 0; i < r->qtd_monitores; i++)
        fscanf(input, "%d", &r->monitores[i]);

    r->grafo = graph_create(qtd_vertices, qtd_edges, input);

    return r;
}

void rede_calc_inflacao_RTT(Rede *r, FILE *output){
    double RTT_real = 0, *RTT_estimados = malloc(r->qtd_monitores * sizeof(double));
    double *dist_servidor, *dist_monitor, *dist_cliente;
    double rtt_servidor_monitor, rtt_monitor_cliente, rtt_cliente_servidor;
    double inflacao_RTT = 0;
    double min_RTT_estimado = INFINITY;
    // PQ *RTT_estimados_pq = PQ_create(r->qtd_servidores * r->qtd_clientes);

    for (int i = 0; i < r->qtd_servidores; i++)
    {
        dist_servidor = graph_dijkstra(r->grafo, r->servidores[i]);

        for (int j = 0; j < r->qtd_clientes; j++)
        {
            dist_cliente = graph_dijkstra(r->grafo, r->clientes[j]);

            rtt_cliente_servidor = dist_servidor[r->clientes[j]] + dist_cliente[r->servidores[i]];
            RTT_real = rtt_cliente_servidor;

            for (int k = 0; k < r->qtd_monitores; k++)
            {
                dist_monitor = graph_dijkstra(r->grafo, r->monitores[k]);

                rtt_servidor_monitor = (dist_servidor[r->monitores[k]] + dist_monitor[r->servidores[i]]);
                rtt_monitor_cliente = (dist_monitor[r->clientes[j]] + dist_cliente[r->monitores[k]]);

                RTT_estimados[k] = rtt_servidor_monitor + rtt_monitor_cliente;

                free(dist_monitor);
            }

            for (int k = 0; k < r->qtd_monitores; k++)
            {
                if(RTT_estimados[k] < min_RTT_estimado){
                    min_RTT_estimado = RTT_estimados[k];
                }
            }
            inflacao_RTT = min_RTT_estimado / RTT_real;

            // PQ_insert(RTT_estimados_pq, item_create(i * j, inflacao_RTT));

            min_RTT_estimado = INFINITY;

            fprintf(output, "%d %d %.16lf\n", r->servidores[i], r->clientes[j], inflacao_RTT);

            free(dist_cliente);
        }
        free(dist_servidor);
    }

    free(RTT_estimados);
}

void rede_destroy(Rede *r){
    free(r->servidores);
    free(r->clientes);
    free(r->monitores);
    graph_destroy(r->grafo);
    free(r);
}