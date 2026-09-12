def soma_matriz(A, B):
    n = len(A)
    return [[A[i][j] + B[i][j] for j in range(n)] for i in range(n)]


def subtrai_matriz(A, B):
    n = len(A)
    return [[A[i][j] - B[i][j] for j in range(n)] for i in range(n)]


def divide_matriz(M):
    n = len(M)
    m = n // 2
    a = [linha[:m] for linha in M[:m]]
    b = [linha[m:] for linha in M[:m]]
    c = [linha[:m] for linha in M[m:]]
    d = [linha[m:] for linha in M[m:]]
    return a, b, c, d


def junta_matriz(r, s, t, u):
    m = len(r)
    n = 2 * m
    C = [[0] * n for _ in range(n)]
    for i in range(m):
        for j in range(m):
            C[i][j] = r[i][j]
            C[i][j + m] = s[i][j]
            C[i + m][j] = t[i][j]
            C[i + m][j + m] = u[i][j]
    return C


def multiplica_ingenuo(A, B):
    n = len(A)
    p = len(B[0])
    k_max = len(B)
    C = [[0] * p for _ in range(n)]
    for i in range(n):
        for j in range(p):
            soma = 0
            for k in range(k_max):
                soma += A[i][k] * B[k][j]
            C[i][j] = soma
    return C




def _strassen_recursivo(A, B, limiar):
    n = len(A)


    if n <= limiar:
        return multiplica_ingenuo(A, B)


    a, b, c, d = divide_matriz(A)
    e, f, g, h = divide_matriz(B)

    P1 = _strassen_recursivo(a, subtrai_matriz(f, h), limiar)
    P2 = _strassen_recursivo(soma_matriz(a, b), h, limiar)
    P3 = _strassen_recursivo(soma_matriz(c, d), e, limiar)
    P4 = _strassen_recursivo(d, subtrai_matriz(g, e), limiar)
    P5 = _strassen_recursivo(soma_matriz(a, d), soma_matriz(e, h), limiar)
    P6 = _strassen_recursivo(subtrai_matriz(b, d), soma_matriz(g, h), limiar)
    P7 = _strassen_recursivo(subtrai_matriz(a, c), soma_matriz(e, f), limiar)


    r = soma_matriz(subtrai_matriz(soma_matriz(P5, P4), P2), P6)  # P5+P4-P2+P6
    s = soma_matriz(P1, P2)                                       # P1+P2
    t = soma_matriz(P3, P4)                                       # P3+P4
    u = subtrai_matriz(subtrai_matriz(soma_matriz(P5, P1), P3), P7)  # P5+P1-P3-P7

    return junta_matriz(r, s, t, u)


def _proxima_potencia_de_dois(n):
    potencia = 1
    while potencia < n:
        potencia *= 2
    return potencia


def _preenche_com_zeros(M, tamanho):
    n = len(M)
    nova = [[0] * tamanho for _ in range(tamanho)]
    for i in range(n):
        for j in range(n):
            nova[i][j] = M[i][j]
    return nova


def strassen(A, B, limiar=32):
    n = len(A)
    if not (n == len(A[0]) == len(B) == len(B[0])):
        raise ValueError(
        )

    tamanho = _proxima_potencia_de_dois(n)
    A_pad = _preenche_com_zeros(A, tamanho)
    B_pad = _preenche_com_zeros(B, tamanho)

    C_pad = _strassen_recursivo(A_pad, B_pad, limiar)

    return [linha[:n] for linha in C_pad[:n]]

if __name__ == "__main__":
    import random
    import time

    def matriz_aleatoria(n, minimo=-10, maximo=10):
        return [[random.randint(minimo, maximo) for _ in range(n)] for _ in range(n)]

    def imprime_matriz(M, titulo):
        print(titulo)
        for linha in M:
            print(" ", linha)

    print("=" * 70)
    print("Exemplo pequeno (2x2)")
    print("=" * 70)
    A = [[1, 2], [3, 4]]
    B = [[5, 6], [7, 8]]
    resultado = strassen(A, B)
    esperado = multiplica_ingenuo(A, B)
    imprime_matriz(A, "A =")
    imprime_matriz(B, "B =")
    imprime_matriz(resultado, "Strassen(A, B) =")
    print("Esperado (ingênuo):", esperado)
    print("OK!" if resultado == esperado else "ERRO!")

    print()
    print("=" * 70)
    print("Testes aleatórios com tamanhos variados (inclusive não potência de 2)")
    print("=" * 70)
    random.seed(0)
    todos_corretos = True
    for n in [1, 2, 3, 4, 5, 7, 8, 10, 15, 16, 20]:
        A = matriz_aleatoria(n)
        B = matriz_aleatoria(n)
        resultado = strassen(A, B)
        esperado = multiplica_ingenuo(A, B)
        if resultado != esperado:
            todos_corretos = False
            print(f"[ERRO] falhou para n={n}")
        else:
            print(f"[OK] n={n}")
    if todos_corretos:
        print("\nTodos os testes aleatórios passaram!")

    print()
    print("=" * 70)
    print("Comparação de tempo: Strassen vs multiplicação ingênua (n=64)")
    print("(em Python puro, o Strassen só compensa para matrizes MUITO")
    print(" grandes por causa do overhead de criar sub-listas; aqui é só")
    print(" para conferir que os dois dão o mesmo resultado)")
    print("=" * 70)
    n = 64
    A = matriz_aleatoria(n, -5, 5)
    B = matriz_aleatoria(n, -5, 5)

    inicio = time.time()
    resultado_strassen = strassen(A, B, limiar=32)
    tempo_strassen = time.time() - inicio

    inicio = time.time()
    resultado_ingenuo = multiplica_ingenuo(A, B)
    tempo_ingenuo = time.time() - inicio

    print(f"Matrizes {n}x{n}")
    print(f"Strassen : {tempo_strassen:.4f} s")
    print(f"Ingênuo  : {tempo_ingenuo:.4f} s")
    print("Resultados iguais?", resultado_strassen == resultado_ingenuo)