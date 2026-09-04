def particiona(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1
 
 
def _select(A, p, r, k):
    if p == r:
        return A[p]
 
    q = particiona(A, p, r)
    m = q - p + 1  
 
    if k == m:
        return A[q]
    elif k < m:
        return _select(A, p, q - 1, k)
    else:
        return _select(A, q + 1, r, k - m)
 
 
def quickselect(A, k):

    n = len(A)
    if not (1 <= k <= n):
        raise ValueError(f"k deve estar entre 1 e {n} (recebeu k={k})")
 
    copia = list(A)
    return _select(copia, 0, n - 1, k)
 
if __name__ == "__main__":
    import random
 
    print("=" * 70)
    print("Exemplo simples")
    print("=" * 70)
    A = [2, 4, 1, 9, 5, 3, 8, 6, 7]
    for k in range(1, len(A) + 1):
        resultado = quickselect(A, k)
        esperado = sorted(A)[k - 1]
        status = "OK" if resultado == esperado else "ERRO"
        print(f"[{status}] {k}-ésimo menor de {A} = {resultado} (esperado {esperado})")
 
    print()
    print("=" * 70)
    print("A[k] não é modificado pela chamada (trabalha em cópia)")
    print("=" * 70)
    A_original = [5, 3, 8, 1, 9]
    A_antes = list(A_original)
    quickselect(A_original, 2)
    print("Antes:", A_antes)
    print("Depois:", A_original)
    print("Igual?", A_antes == A_original)
 
    print()
    print("=" * 70)
    print("Testes aleatórios (vetores de tamanhos e valores variados)")
    print("=" * 70)
    random.seed(1)
    todos_corretos = True
    for _ in range(200):
        n = random.randint(1, 200)
        A = [random.randint(-1000, 1000) for _ in range(n)]
        k = random.randint(1, n)
        resultado = quickselect(A, k)
        esperado = sorted(A)[k - 1]
        if resultado != esperado:
            todos_corretos = False
            print(f"[ERRO] n={n}, k={k}")
    if todos_corretos:
        print("Todos os 200 testes aleatórios passaram!")
 
    print()
    print("=" * 70)
    print("Caso adversário: vetor já ordenado (pior caso Θ(n²) do slide 62)")
    print("Ainda assim o RESULTADO deve estar correto, só fica mais lento.")
    print("Aqui aumentamos o limite de recursão do Python, porque o pior")
    print("caso do Quickselect (pivô sempre no extremo) recursa n vezes,")
    print("uma para cada elemento removido.")
    print("=" * 70)
    import sys
    sys.setrecursionlimit(5000)
    n = 3000
    A = list(range(n))  # já ordenado -> pivô (último elemento) é sempre o maior
    k = n // 2
    resultado = quickselect(A, k)
    print(f"{k}-ésimo menor de um vetor ordenado de 0 a {n-1} = {resultado} "
          f"(esperado {k - 1})")
    print("OK!" if resultado == k - 1 else "ERRO!")
 