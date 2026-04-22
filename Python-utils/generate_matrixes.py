import random

n = 431

def save_matrix(filename, matrix):
    with open(filename, "w") as f:
        f.write(str(n) + "\n")
        for row in matrix:
            f.write(" ".join(map(str, row)) + "\n")

# ------------------------
# CASO 1: pesos = 1 + 600 arestas extras
# ------------------------
matrix1 = [[0]*n for _ in range(n)]

# garante conexão (cadeia)
for i in range(n-1):
    matrix1[i][i+1] = 1
    matrix1[i+1][i] = 1

# adiciona 600 arestas extras
extra_edges = 600
added = 0
while added < extra_edges:
    u = random.randint(0, n-1)
    v = random.randint(0, n-1)
    if u != v and matrix1[u][v] == 0:
        matrix1[u][v] = 1
        matrix1[v][u] = 1
        added += 1

save_matrix("test_case_1.txt", matrix1)

# ------------------------
# CASO 2: grafo completo (1 a 430)
# ------------------------
matrix2 = [[0]*n for _ in range(n)]

for i in range(n):
    for j in range(i+1, n):
        w = random.randint(1, 430)
        matrix2[i][j] = w
        matrix2[j][i] = w

save_matrix("test_case_2.txt", matrix2)

# ------------------------
# CASO 3: estrela (centro = 0)
# ------------------------
matrix3 = [[0]*n for _ in range(n)]

for i in range(1, n):
    matrix3[0][i] = i
    matrix3[i][0] = i

save_matrix("test_case_3.txt", matrix3)

# ------------------------
# CASO 4: completo com pesos altos
# ------------------------
matrix4 = [[0]*n for _ in range(n)]

for i in range(n):
    for j in range(i+1, n):
        w = random.randint(60000, 65535)
        matrix4[i][j] = w
        matrix4[j][i] = w

save_matrix("test_case_4.txt", matrix4)

print("Arquivos gerados com sucesso!")