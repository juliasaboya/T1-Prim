def ler_matriz_txt(caminho):
    with open(caminho, "r") as f:
        linhas = f.readlines()

    n = int(linhas[0].strip())
    matriz = []

    for i in range(1, n+1):
        linha = list(map(int, linhas[i].split()))
        matriz.append(linha)

    return matriz


def matriz_para_lista(adj_matrix):
    n = len(adj_matrix)
    adj_list = [[] for _ in range(n)]

    for i in range(n):
        for j in range(i+1, n):
            w = adj_matrix[i][j]
            if w != 0:
                adj_list[i].append((j, w))
                adj_list[j].append((i, w))

    return adj_list

def salvar_lista_txt(adj_list, caminho):
    with open(caminho, "w") as f:
        for i, vizinhos in enumerate(adj_list):
            for j, w in vizinhos:
                if i < j:  # evita duplicar arestas
                    f.write(f"{i} {j} {w}\n")



# ------------------------
# USO
# ------------------------
matriz = ler_matriz_txt("test_case_4.txt")
lista = matriz_para_lista(matriz)
salvar_lista_txt(lista, "lista_case_4.txt")


# exemplo: printar primeiros vértices
for i in range(5):
    print(f"{i}: {lista[i]}")