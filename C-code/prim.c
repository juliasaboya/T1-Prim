#include <stdio.h>
#include <string.h>

#define MAXN 431
#define MAXM 100000 
// Número máximo de arestas (sem considerar duplicação).
// Para grafos completos com 431 vértices: E ≈ 92.665.
// Como usamos lista de adjacência (grafo não direcionado),
// armazenamos 2 * E arestas (ida e volta).
// Portanto, MAXM precisa suportar esse volume.


#define INF 65535
// Indica que ainda não existe aresta conhecida conectando o vértice à árvore.
// Não representa um peso real do grafo.
// Na prática, será usado 65535 que é o maximo armazenado por u_int_16

int head[MAXN];
int to[2 * MAXM];
u_int16_t w[2 * MAXM];
int nxt[2 * MAXM];
int edge_cnt = 0;
// head[u] → índice da primeira aresta do vértice u
// to[e] → vértice de destino da aresta e
// w[e] → peso da aresta e
// nxt[e] → próxima aresta ligada ao mesmo vértice
u_int16_t key[MAXN];
u_int16_t parent[MAXN];
u_int8_t visited[MAXN];

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

void prim() {

    for (int i = 0; i < n; i++) {
        key[i] = INF;      // INF: ainda não sabemos alcançar esse vertice
        parent[i] = INF;   // NIL: sem origem conhecida
        visited[i] = 0;
    }

    key[0] = 0;

    int total_cost = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;

        // Escolhe o vértice, dentre os não conectados AINDA, que tenha menor aresta de conexão.
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || key[j] < key[v])) {
                v = j;
            }
        }

        // Se o menor custo continua sendo INF, entende que não existe aresta.
        if (key[v] == INF) {
            printf("Grafo não é conexo\n");
            return;
        }

        visited[v] = 1;
        // Marca o vértice como incluído na árvore geradora mínima.
        // A partir deste ponto, ele passa a fazer parte da solução
        // e não será mais considerado nas próximas escolhas.

        
        total_cost += key[v]; // Adicionando ao custo total...

        if (parent[v] != 65535) {
            printf("%d %d (peso = %d)\n", parent[v], v, key[v]);
        }

        // Percorre os vizinhos do vértice recém-inserido.
        // Para cada vizinho ainda não selecionado,
        // verifica se existe uma aresta mais barata para conectá-lo.
        // Se sim, atualiza o melhor custo conhecido (relaxamento).
        for (int e = head[v]; e != -1; e = nxt[e]) {
            int u = to[e];

            if (!visited[u] && w[e] < key[u]) {
                key[u] = w[e];
                parent[u] = v;
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
    FILE *f = fopen(file_case_4, "r"); 
    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    load_graph_simple(f);

    fclose(f);
    prim();
    return 0;
}

