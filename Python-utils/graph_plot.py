import matplotlib.pyplot as plt
import random

NUM_VERTICES = 431
MAX_WEIGHT = 431

# ------------------------
# 1. Gerar vértices
# ------------------------
points = {
    i: (random.uniform(0, 100), random.uniform(0, 100))
    for i in range(NUM_VERTICES)
}

# ------------------------
# 2. Gerar arestas (garantindo conexão)
# ------------------------
edges = []

# cria uma "árvore" conectando todos
for i in range(1, NUM_VERTICES):
    j = random.randint(0, i - 1)
    weight = random.randint(1, MAX_WEIGHT)
    edges.append((i, j, weight))

# adiciona arestas extras
EXTRA_EDGES = 400  # pode aumentar/diminuir

for _ in range(EXTRA_EDGES):
    u = random.randint(0, NUM_VERTICES - 1)
    v = random.randint(0, NUM_VERTICES - 1)
    
    if u != v:
        weight = random.randint(1, MAX_WEIGHT)
        edges.append((u, v, weight))

# ------------------------
# 3. Plot
# ------------------------
plt.figure(figsize=(10,10))

# desenhar arestas
for u, v, w in edges:
    x1, y1 = points[u]
    x2, y2 = points[v]
    plt.plot([x1, x2], [y1, y2], alpha=0.25)
    xm = (x1 + x2) / 2
    ym = (y1 + y2) / 2
    plt.text(xm, ym, str(w), fontsize=6)

# desenhar vértices
for i, (x, y) in points.items():
    plt.scatter(x, y, s=10)

plt.title("Grafo não direcionado com 431 vértices")
plt.grid()
plt.show()