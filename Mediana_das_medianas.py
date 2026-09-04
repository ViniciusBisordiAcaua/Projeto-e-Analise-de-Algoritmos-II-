def mediana_das_medianas(A, k):
    n = len(A)
    if not (1 <= k <= n):
        raise ValueError(f"k deve estar entre 1 e {n} (recebeu k={k})")
    return _selecao(A, k)
 
 
def _selecao(A, k):
    n = len(A)
    if n < 15:
        return sorted(A)[k - 1]

    medianas = []
    for i in range(0, n, 5):
        grupo = sorted(A[i:i + 5])
        medianas.append(grupo[len(grupo) // 2]) 
 

    posicao_mediana_de_M = (len(medianas) + 1) // 2
    m = _selecao(medianas, posicao_mediana_de_M)
 
    L1 = [x for x in A if x < m]
    L2 = [x for x in A if x == m]
    L3 = [x for x in A if x > m]

    if len(L1) >= k:
        return _selecao(L1, k)
    elif len(L1) + len(L2) >= k:
        return m
    else:
        return _selecao(L3, k - len(L1) - len(L2))
 
if __name__ == "__main__":
    import random
 
    print("=" * 70)
    print("Exemplo simples")
    print("=" * 70)
    A = [2, 4, 1, 9, 5, 3, 8, 6, 7, 10, 11, 0, 15, 14, 13, 12]
    for k in range(1, len(A) + 1):
        resultado = mediana_das_medianas(A, k)
        esperado = sorted(A)[k - 1]
        status = "OK" if resultado == esperado else "ERRO"
        print(f"[{status}] {k}-ésimo menor = {resultado} (esperado {esperado})")
 
    print()
    print("=" * 70)
    print("A entrada não é modificada pela chamada")
    print("=" * 70)
    A_original = [5, 3, 8, 1, 9, 7, 2, 6, 4, 10, 12, 11, 13, 14, 15, 16]
    A_antes = list(A_original)
    mediana_das_medianas(A_original, 4)
    print("Antes:", A_antes)
    print("Depois:", A_original)
    print("Igual?", A_antes == A_original)
 
    print()
    print("=" * 70)
    print("Testes aleatórios (vetores de tamanhos e valores variados,")
    print("incluindo listas com muitos elementos repetidos)")
    print("=" * 70)
    random.seed(2)
    todos_corretos = True
    for _ in range(200):
        n = random.randint(1, 500)
        A = [random.randint(-20, 20) for _ in range(n)] 
        k = random.randint(1, n)
        resultado = mediana_das_medianas(A, k)
        esperado = sorted(A)[k - 1]
        if resultado != esperado:
            todos_corretos = False
            print(f"[ERRO] n={n}, k={k}")
    if todos_corretos:
        print("Todos os 200 testes aleatórios passaram!")
 
    print()
    print("=" * 70)
    print("Caso que é PIOR CASO para o Quickselect comum (vetor ordenado)")
    print("Aqui o algoritmo continua rápido, pois a escolha do pivô não")
    print("depende da posição dos elementos no vetor.")
    print("=" * 70)
    n = 5000
    A = list(range(n))
    k = n // 2
    resultado = mediana_das_medianas(A, k)
    print(f"{k}-ésimo menor de um vetor ordenado de 0 a {n-1} = {resultado} "
          f"(esperado {k - 1})")
    print("OK!" if resultado == k - 1 else "ERRO!")
 