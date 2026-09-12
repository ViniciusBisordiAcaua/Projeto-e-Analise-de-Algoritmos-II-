def karatsuba(x: int, y: int) -> int:

    sinal = 1
    if x < 0:
        sinal *= -1
        x = -x
    if y < 0:
        sinal *= -1
        y = -y

    resultado = _karatsuba_recursivo(x, y)
    return sinal * resultado


def _karatsuba_recursivo(x: int, y: int) -> int:
    if x < 10 or y < 10:
        return x * y


    n = max(len(str(x)), len(str(y)))
    m = n // 2  # m = n/2, arredondado para baixo


    potencia = 10 ** m
    a, b = divmod(x, potencia)   # a = x // 10^m ; b = x mod 10^m
    c, d = divmod(y, potencia)   # c = y // 10^m ; d = y mod 10^m


    ac = _karatsuba_recursivo(a, c)
    bd = _karatsuba_recursivo(b, d)
    u = _karatsuba_recursivo(a + b, c + d)

    ad_mais_bc = u - ac - bd

    return ac * (10 ** (2 * m)) + ad_mais_bc * potencia + bd


if __name__ == "__main__":
    import random
    import time

    print("=" * 70)
    print("Exemplo do slide 42: 5678 x 1234")
    print("=" * 70)
    x, y = 5678, 1234
    resultado = karatsuba(x, y)
    esperado = x * y
    print(f"karatsuba({x}, {y}) = {resultado}")
    print(f"esperado (5678*1234)  = {esperado}")
    print("OK!" if resultado == esperado else "ERRO!")

    print()
    print("=" * 70)
    print("Outros exemplos simples")
    print("=" * 70)
    exemplos = [
        (12, 34),
        (0, 999),
        (-123, 456),
        (123, -456),
        (-123, -456),
        (999999999, 1),
        (123456789, 987654321),
    ]
    for x, y in exemplos:
        resultado = karatsuba(x, y)
        esperado = x * y
        status = "OK" if resultado == esperado else "ERRO"
        print(f"[{status}] {x} * {y} = {resultado}")

    print()
    print("=" * 70)
    print("Teste com números aleatórios grandes (comparando com x*y do Python)")
    print("=" * 70)
    random.seed(42)
    todos_corretos = True
    for i in range(20):
        num_digitos = random.randint(1, 300)
        x = random.randint(10 ** (num_digitos - 1), 10 ** num_digitos - 1)
        y = random.randint(10 ** (num_digitos - 1), 10 ** num_digitos - 1)
        resultado = karatsuba(x, y)
        esperado = x * y
        if resultado != esperado:
            todos_corretos = False
            print(f"[ERRO] falhou para números com ~{num_digitos} dígitos")
    if todos_corretos:
        print("Todos os 20 testes aleatórios (até 300 dígitos) passaram!")

    print()
    print("=" * 70)
    print("Comparação de tempo: Karatsuba vs multiplicação nativa do Python")
    print("(apenas para fins didáticos - o operador `*` do Python já é")
    print(" extremamente otimizado, então isso NÃO mede a vantagem teórica")
    print(" do algoritmo, só mostra que o resultado é o mesmo)")
    print("=" * 70)
    num_digitos = 2000
    x = random.randint(10 ** (num_digitos - 1), 10 ** num_digitos - 1)
    y = random.randint(10 ** (num_digitos - 1), 10 ** num_digitos - 1)

    inicio = time.time()
    resultado_karatsuba = karatsuba(x, y)
    tempo_karatsuba = time.time() - inicio

    inicio = time.time()
    resultado_nativo = x * y
    tempo_nativo = time.time() - inicio

    print(f"Números com {num_digitos} dígitos")
    print(f"Karatsuba : {tempo_karatsuba:.4f} s")
    print(f"Nativo (*): {tempo_nativo:.6f} s")
    print("Resultados iguais?", resultado_karatsuba == resultado_nativo)