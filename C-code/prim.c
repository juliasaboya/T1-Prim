#include <stdio.h>
#include <string.h>

#define MAXN 431
#define MAXM 100000 
// - Pior caso: 100000; para o caso de grafos completos 
//   com 431 vertices temos   
// - Caso base: 860
#define INF 1000000000

int head[MAXN];
int to[2 * MAXM];
int w[2 * MAXM];
int nxt[2 * MAXM];
int edge_cnt = 0;

int n, m;

void add_edge(int u, int v, int weight) {
    to[edge_cnt] = v;
    w[edge_cnt] = weight;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

typedef struct {
    int w;
    int from;
} MinEdge;

void prim() {
    MinEdge min_e[MAXN];
    int selected[MAXN] = {0};

    for (int i = 0; i < n; i++) {
        min_e[i].w = INF;
        min_e[i].from = -1;
    }

    min_e[0].w = 0;

    int total_cost = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;

        // escolhe o vértice, dentre os não conectados, que tenha o menor peso para conectar 
        for (int j = 0; j < n; j++) {
            if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w)) {
                v = j;
            }
        }

        if (min_e[v].w == INF) {
            printf("Grafo não é conexo\n");
            return;
        }

        selected[v] = 1;

        total_cost += min_e[v].w;  // 🔥 soma o custo

        if (min_e[v].from != -1) {
            printf("%d %d (peso = %d)\n", min_e[v].from, v, min_e[v].w);
        }

        for (int e = head[v]; e != -1; e = nxt[e]) {
            int u = to[e];

            if (!selected[u] && w[e] < min_e[u].w) {
                min_e[u].w = w[e];
                min_e[u].from = v;
            }
        }
    }

    printf("Total cost: %d\n", total_cost);
}

// para ler os .txt e usar as listas
void load_graph_simple(FILE *f) {
    int u, v, weight;

    while (fscanf(f, "%d %d %d", &u, &v, &weight) == 3) {
        add_edge(u, v, weight);
        add_edge(v, u, weight); // não direcionado
    }
    printf("Edges carregadas: %d\n", edge_cnt);
}

int main() {
    n = 431;

    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }

    FILE *f = fopen("lista_case_4.txt", "r"); // 🔥 troca aqui

    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    load_graph_simple(f);

    fclose(f);

    prim();

    return 0;
}