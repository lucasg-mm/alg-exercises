# Calcula a solução ótima com estratégia de prog. din. (versão iterativa)
def minimiza_troco(moedas, val_dado):
    # ordena as moedas de maneira crescente e coloca uma moeda "dummy", apenas para a correta execução do alg.
    moedas.append(0)
    moedas.sort()

    # só precisamos das moedas que tenham valor menor do que o dado
    moedas = [val_moeda for val_moeda in moedas if val_moeda <= val_dado]

    # se só existe uma moeda com o valor menor que o dado, esta é a dummy, e o problema não tem solução
    if len(moedas) == 1:
        return "sem solucao"

    # matriz de memoização para guardar nós já visitados
    M = [[float("inf") if i == 0 and j != 0 else 0 for j in range(
        val_dado + 1)] for i in range(len(moedas))]

    # faz iteração característica de problemas resolvidos por programação dinâmica
    for i in range(1, len(M)):
        for j in range(1, len(M[i])):
            custo = j // moedas[i]
            val_moeda = moedas[i]
            M[i][j] = min(custo + M[i-1][j - custo*val_moeda], M[i-1][j])

    return M[len(moedas) - 1][val_dado]  # retorna a resposta


def main():
    # entrada do usuário
    num_casos_teste = int(input())

    for _ in range(num_casos_teste):
        caso = input()
        caso = caso.split()
        val_dado = int(caso[0])
        num_moedas = int(caso[1])
        moedas = [int(caso[i+2]) for i in range(num_moedas)]

        # otimiza usando estratégia de programação dinâmica!
        print(minimiza_troco(moedas, val_dado))


if __name__ == "__main__":
    main()
