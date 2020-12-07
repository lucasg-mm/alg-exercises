def num_op(string1, string2):
    """Returns the number of operations needed to convert 'string1' to 'string2' (both representing a sequnce of numbers)"""

    n = len(string1)  # both strings have the same size, as the problem states

    # buids the memoization matrix (initially, it's all set up to be zero):
    M = [[0 for j in range(n)] for i in range(n)]

    # dynamic programming iteration
    for j in range(n):
        for i in range(n):
            if string1[j] == string2[i]:
                if i == 0 and j == 0:
                    M[i][j] = 0  # M[-1][-1]
                    continue
                elif i == 0 and j != 0:
                    M[i][j] = j  # M[-1][j-1]
                    continue
                elif i != 0 and j == 0:
                    M[i][j] = i  # M[j-1][-1]
                    continue
                else:
                    M[i][j] = M[i - 1][j - 1]
            else:
                if i == 0 and j == 0:
                    M[i][j] = 2  # min(1 + M[0][-1], 1 + M[-1][0])
                    continue
                elif i == 0 and j != 0:
                    # min(1 + M[-1][j], 1 + M[i][j-1])
                    M[i][j] = min(2 + j, 1 + M[i][j - 1])
                    continue
                elif i != 0 and j == 0:
                    # min(1 + M[i][-1], 1 + M[i-1][j])
                    M[i][j] = min(2 + i, 1 + M[i - 1][j])
                    continue
                else:
                    M[i][j] = min(1 + M[i - 1][j], 1 + M[i][j - 1])

    return M[n-1][n-1]


def main():
    num_test_cases = int(input())

    for case in range(num_test_cases):
        input()
        string1 = input().split()
        string2 = input().split()
        print(f"Case {case + 1}: {num_op(string1, string2)}")


if __name__ == "__main__":
    main()
