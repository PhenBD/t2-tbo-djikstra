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
    double RTT_real = 0, RTT_estrela = 0, inflacao_RTT = 0;
    double **dist_servidor = malloc(r->qtd_servidores * sizeof(double*));
    double **dist_monitor = malloc(r->qtd_monitores * sizeof(double*));
    double **dist_cliente = malloc(r->qtd_clientes * sizeof(double*));
    Edge **ordered = malloc((r->qtd_servidores * r->qtd_clientes) * sizeof(Edge*));

    // Gera a distancia de cada servidor, cliente e monitor para todos os vertices
    for (int i = 0; i < r->qtd_servidores; i++)
        dist_servidor[i] = graph_dijkstra(r->grafo, r->servidores[i]);

    for (int j = 0; j < r->qtd_clientes; j++)
        dist_cliente[j] = graph_dijkstra(r->grafo, r->clientes[j]);

    for (int k = 0; k < r->qtd_monitores; k++)
        dist_monitor[k] = graph_dijkstra(r->grafo, r->monitores[k]);

    // Loop para todas as conexoes necessarias
    for (int i = 0; i < r->qtd_servidores; i++){
        for (int j = 0; j < r->qtd_clientes; j++)
        {
            RTT_real = rede_RTT_real(r, dist_servidor, dist_cliente, i, j);

            RTT_estrela = rede_RTT_estrela(r, dist_servidor, dist_cliente, dist_monitor, i, j);
            
            // Calcula a inflacao entre o RTT estrela e o real
            inflacao_RTT = RTT_estrela / RTT_real;

            // Adiciona numa lista de edges(arestas) a aresta "direta" entre servidor[i] e ciente[j] e a inflacao entre os RTTs
            ordered[i * r->qtd_clientes + j] = edge_create(r->servidores[i], r->clientes[j], inflacao_RTT);
        }
    }

    // Ordena a lista de edges(arestas)
    qsort(ordered, r->qtd_servidores * r->qtd_clientes, sizeof(Edge *), edge_weight_compare);

    // Imprime no arquivo output todas arestas diretas entre cada servidor e cliente e suas inflacoes
    for(int i = 0; i < r->qtd_servidores * r->qtd_clientes; i++){
        fprintf(output, "%d %d %.16lf\n", edge_src(ordered[i]), edge_dest(ordered[i]), edge_weight(ordered[i]));
        edge_destroy(ordered[i]);
    }

    // Libera toda a memoria auxiliar alocada
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
}

double rede_RTT_real(Rede *r, double **dist_servidor, double **dist_cliente, int servidor, int cliente){
    double RTT_real = 0, rtt_cliente_servidor = 0;

    // Calculo do RTT real entre o servidor e o cliente
    // obs: "distancia_do_servidor" do [servidor] para o [cliente] mais vice versa
    rtt_cliente_servidor = dist_servidor[servidor][r->clientes[cliente]] + dist_cliente[cliente][r->servidores[servidor]];
    RTT_real = rtt_cliente_servidor;

    return RTT_real;
}

double rede_RTT_estrela(Rede *r, double **dist_servidor, double **dist_cliente, double **dist_monitor, int servidor, int cliente){
    double rtt_servidor_monitor = 0, rtt_monitor_cliente = 0, RTT_estrela = INFINITY;
    double *RTT_estimados = malloc(r->qtd_monitores * sizeof(double));

    // Calculo de todos os possiveis RTTs estrela
    for (int k = 0; k < r->qtd_monitores; k++)
    {
        // Calculo do RTT entre servidor e monitor
        rtt_servidor_monitor = (dist_servidor[servidor][r->monitores[k]] + dist_monitor[k][r->servidores[servidor]]);

        // Calculo do RTT entre monitor e cliente
        rtt_monitor_cliente = (dist_monitor[k][r->clientes[cliente]] + dist_cliente[cliente][r->monitores[k]]);

        // Calculo de um possivel RTT estrela
        RTT_estimados[k] = rtt_servidor_monitor + rtt_monitor_cliente;
    }
    
    // Acha o menor RTT estimado, que sera o RTT estrela
    for (int k = 0; k < r->qtd_monitores; k++)
    {
        if(RTT_estimados[k] < RTT_estrela){
            RTT_estrela = RTT_estimados[k];
        }
    }

    free(RTT_estimados);
    return RTT_estrela;
}

void rede_destroy(Rede *r){
    free(r->servidores);
    free(r->clientes);
    free(r->monitores);
    graph_destroy(r->grafo);
    free(r);
}