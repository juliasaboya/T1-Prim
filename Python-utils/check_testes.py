def ler_arquivo1(caminho):
    with open(caminho, 'r') as f:
        linhas = [l.strip() for l in f.readlines()]

    # Pula linhas vazias e cabeçalho
    linhas = [l for l in linhas if l]
    
    n_vertices = 0
    arestas = []
    custo_total = 0

    for linha in linhas:
        # Pula linhas de cabeçalho e vazias
        if not linha or "FORMAT" in linha or "nodes" in linha.lower():
            continue
        if linha.startswith("Custo total"):
            custo_total = int(linha.split(":")[1].strip())
        elif "(" in linha and ")" in linha:
            # formato: peso(pai,filho) - ex: 60005(1,38)
            peso_str, resto = linha.split("(")
            peso = int(peso_str.strip())
            pai, filho = resto.replace(")", "").split(",")
            arestas.append((int(pai), int(filho), peso))
            # Atualiza número de vértices
            n_vertices = max(n_vertices, int(pai), int(filho))

    return n_vertices, arestas, custo_total


def ler_arquivo2(caminho):
    with open(caminho, 'r') as f:
        linhas = [l.strip() for l in f.readlines()]

    n_vertices = 0
    arestas = []
    custo_total = 0

    for linha in linhas:
        if linha.startswith("custo total"):
            custo_total = int(linha.split(":")[1].strip())
        elif "(" in linha and ")" in linha:
            # formato: pai, filho (peso = valor)
            partes = linha.split("(")
            pai, filho = partes[0].split(",")
            pai = int(pai.strip()) + 1   # ajusta para 1-based
            filho = int(filho.strip()) + 1  # ajusta para 1-based

            peso = int(partes[1].split("=")[1].replace(")", "").strip())
            arestas.append((pai, filho, peso))
            # Atualiza número de vértices
            n_vertices = max(n_vertices, pai, filho)

    return n_vertices, arestas, custo_total


def comparar(arquivo1, arquivo2):
    n1, a1, c1 = ler_arquivo1(arquivo1)
    n2, a2, c2 = ler_arquivo2(arquivo2)

    print("Comparando número de vértices...")
    print("OK" if n1 == n2 else f"Diferente: {n1} vs {n2}")

    print("\nComparando custo total...")
    print("OK" if c1 == c2 else f"Diferente: {c1} vs {c2}")

    print("\nComparando arestas...")
    
    # Normaliza arestas para comparação (ordena vértices para treating (u,v) e (v,u) como igual)
    def normalizar_arestas(arestas):
        return set((min(pai, filho), max(pai, filho), peso) for pai, filho, peso in arestas)
    
    set1 = normalizar_arestas(a1)
    set2 = normalizar_arestas(a2)

    if set1 == set2:
        print("Arestas iguais!")
    else:
        print("Diferenças encontradas:")
        print("Somente no arquivo 1:", set1 - set2)
        print("Somente no arquivo 2:", set2 - set1)


import os

# Obtém o diretório onde o script está localizado
script_dir = os.path.dirname(os.path.abspath(_file_))

# Define caminhos absolutos para os arquivos
result_path = os.path.join(script_dir, "..", "C-code", "Result2.txt")
saida_path = os.path.join(script_dir, "..", "C-code", "saida2.txt")

# uso
comparar(result_path, saida_path)