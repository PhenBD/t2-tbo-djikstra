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
    double **dist_servidor = malloc(r->qtd_servidores * sizeof(double*));
    double **dist_monitor = malloc(r->qtd_monitores * sizeof(double*));
    double **dist_cliente = malloc(r->qtd_clientes * sizeof(double*));
    double rtt_servidor_monitor, rtt_monitor_cliente, rtt_cliente_servidor;
    double inflacao_RTT = 0;
    double min_RTT_estimado = INFINITY;
    Edge **ordered = malloc((r->qtd_servidores * r->qtd_clientes) * sizeof(Edge*));

    for (int i = 0; i < r->qtd_servidores; i++)
        dist_servidor[i] = graph_dijkstra(r->grafo, r->servidores[i]);

    for (int j = 0; j < r->qtd_clientes; j++)
        dist_cliente[j] = graph_dijkstra(r->grafo, r->clientes[j]);

    for (int k = 0; k < r->qtd_monitores; k++)
        dist_monitor[k] = graph_dijkstra(r->grafo, r->monitores[k]);

    for (int i = 0; i < r->qtd_servidores; i++){
        for (int j = 0; j < r->qtd_clientes; j++)
        {
            rtt_cliente_servidor = dist_servidor[i][r->clientes[j]] + dist_cliente[j][r->servidores[i]];
            RTT_real = rtt_cliente_servidor;
            
            for (int k = 0; k < r->qtd_monitores; k++)
            {
                rtt_servidor_monitor = (dist_servidor[i][r->monitores[k]] + dist_monitor[k][r->servidores[i]]);
                rtt_monitor_cliente = (dist_monitor[k][r->clientes[j]] + dist_cliente[j][r->monitores[k]]);

                RTT_estimados[k] = rtt_servidor_monitor + rtt_monitor_cliente;
            }
            
            for (int k = 0; k < r->qtd_monitores; k++)
            {
                if(RTT_estimados[k] < min_RTT_estimado){
                    min_RTT_estimado = RTT_estimados[k];
                }
            }

            inflacao_RTT = min_RTT_estimado / RTT_real;

            min_RTT_estimado = INFINITY;

            ordered[i * r->qtd_clientes + j] = edge_create(r->servidores[i], r->clientes[j], inflacao_RTT);
        }
    }

    qsort(ordered, r->qtd_servidores * r->qtd_clientes, sizeof(Edge *), edge_weight_compare);

    for(int i = 0; i < r->qtd_servidores * r->qtd_clientes; i++){
        fprintf(output, "%d %d %.16lf\n", edge_src(ordered[i]), edge_dest(ordered[i]), edge_weight(ordered[i]));
        edge_destroy(ordered[i]);
    }

    for (int i = 0; i < r->qtd_servidores; i++)
        free(dist_servidor[i]);

    for (int j = 0; j < r->qtd_clientes; j++)
        free(dist_cliente[j]);

    for (int k = 0; k < r->qtd_monitores; k++)
        free(dist_monitor[k]);

    free(dist_servidor);
    free(dist_cliente);
    free(dist_monitor);
    free(ordered);
    free(RTT_estimados);
}

void rede_destroy(Rede *r){
    free(r->servidores);
    free(r->clientes);
    free(r->monitores);
    graph_destroy(r->grafo);
    free(r);
}