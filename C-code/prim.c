#include <stdio.h>
#include <string.h>

#define MAXN 431
#define MAXM 100000 
// Número máximo de arestas (sem considerar duplicação).
// Para grafos completos com 431 vértices: E ≈ 92.665.
// Como usamos lista de adjacência (grafo não direcionado),
// armazenamos 2 * E arestas (ida e volta).
// Portanto, MAXM precisa suportar esse volume.


#define INF 1000000000
// Indica que ainda não existe aresta conhecida conectando o vértice à árvore.
// Não representa um peso real do grafo.

int head[MAXN];
int to[2 * MAXM];
int w[2 * MAXM];
int nxt[2 * MAXM];
int edge_cnt = 0;
// head[u] → índice da primeira aresta do vértice u
// to[e] → vértice de destino da aresta e
// w[e] → peso da aresta e
// nxt[e] → próxima aresta ligada ao mesmo vértice

int n, m;

/// @brief Adiciona uma aresta na lista de adjacência.
// Como o grafo é não direcionado, cada aresta deve ser inserida duas vezes:
// (u → v) e (v → u).

/// @param u 
/// @param v 
/// @param weight 
void add_edge(int u, int v, int weight) {
    to[edge_cnt] = v;
    w[edge_cnt] = weight;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

/// @brief Para cada vértice, armazena:
// w → menor custo conhecido para conectá-lo à árvore
// from → vértice de onde vem essa conexão mínima
typedef struct {
    int w;
    int from;
} MinEdge;


void prim() {
    MinEdge min_e[MAXN];
    int selected[MAXN] = {0};

    for (int i = 0; i < n; i++) {
        min_e[i].w = INF; // ainda não sabemos como conectar o vértice i.
        min_e[i].from = -1; // não possui origem definida.
    }

    min_e[0].w = 0;

    int total_cost = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;

        // Escolhe o vértice, dentre os não conectados AINDA, que tenha menor aresta de conexão.
        for (int j = 0; j < n; j++) {
            if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w)) {
                v = j;
            }
        }

        // Se o menor custo continua sendo INF, entende que não existe aresta.
        if (min_e[v].w == INF) {
            printf("Grafo não é conexo\n");
            return;
        }

        selected[v] = 1;
        // Marca o vértice como incluído na árvore geradora mínima.
        // A partir deste ponto, ele passa a fazer parte da solução
        // e não será mais considerado nas próximas escolhas.

        
        total_cost += min_e[v].w; // Adicionando ao custo total...

        if (min_e[v].from != -1) {
            printf("%d %d (peso = %d)\n", min_e[v].from, v, min_e[v].w);
        }

        // Percorre os vizinhos do vértice recém-inserido.
        // Para cada vizinho ainda não selecionado,
        // verifica se existe uma aresta mais barata para conectá-lo.
        // Se sim, atualiza o melhor custo conhecido (relaxamento).
        for (int e = head[v]; e != -1; e = nxt[e]) {
            int u = to[e];

            if (!selected[u] && w[e] < min_e[u].w) {
                min_e[u].w = w[e];
                min_e[u].from = v;
            }
        }
    }

    printf("Custo total: %d\n", total_cost);
}

// Utilitário para ler os .txt e usar as listas
void load_graph_simple(FILE *f) {
    int u, v, weight;

    while (fscanf(f, "%d %d %d", &u, &v, &weight) == 3) {
        add_edge(u, v, weight);
        add_edge(v, u, weight); // não direcionado
    }

    printf("Edges carregadas: %d\n", edge_cnt);
}

int main() {
    n = MAXN; // 431 vértices
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }

    // declaração dos arquivos de teste
    char file_case_1[] = "lista_case_1.txt";
    char file_case_2[] = "lista_case_2.txt";
    char file_case_3[] = "lista_case_3.txt";
    char file_case_4[] = "lista_case_4.txt";

    // Leitura da lista de adjacência
    FILE *f = fopen(file_case_1, "r"); 
    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    load_graph_simple(f);

    fclose(f);
    prim();
    return 0;
}

