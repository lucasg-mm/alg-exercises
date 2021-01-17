from string import ascii_lowercase


def levenshtein(string1, string2):
    """Returns the Levenshtein distance between the two strings passed as parameters"""

    n = len(string1)
    m = len(string2)

    # buids the memoization matrix (initially, it's all set up to be zero):
    M = [[0 for j in range(n)] for i in range(m)]

    # dynamic programming iteration
    for j in range(n):
        for i in range(m):
            if i == 0 and j == 0:
                idelta = (i + 1) * (ascii_lowercase.index(string2[i]) + 1)
                jdelta = (j + 1) * (ascii_lowercase.index(string1[j]) + 1)
                M[i][j] = min(abs(ascii_lowercase.index(string1[j]) - ascii_lowercase.index(
                    string2[i])), 1 + ascii_lowercase.index(string1[j]) + idelta, 1 + ascii_lowercase.index(string2[i]) + jdelta)
                continue
            elif i == 0 and j != 0:
                jdelta = (j + 1) * (ascii_lowercase.index(string1[j]) + 1)
                M[i][j] = min(abs(ascii_lowercase.index(string1[j]) - ascii_lowercase.index(
                    string2[i])) + jdelta, 1 + ascii_lowercase.index(string1[j]) + M[i][j-1], 1 + ascii_lowercase.index(string2[i]) + jdelta)
                continue    
            elif i != 0 and j == 0:
                idelta = (i + 1) * (ascii_lowercase.index(string2[i]) + 1)
                M[i][j] = min(abs(ascii_lowercase.index(string1[j]) - ascii_lowercase.index(
                    string2[i])) + idelta, 1 + ascii_lowercase.index(string1[j]) + idelta, 1 + ascii_lowercase.index(string2[i]) + M[i-1][j])
                continue    
            else:
                M[i][j] = min(abs(ascii_lowercase.index(string1[j]) - ascii_lowercase.index(
                    string2[i])) + M[i-1][j-1], 1 + ascii_lowercase.index(string1[j]) + M[i][j-1], 1 + ascii_lowercase.index(string2[i]) + M[i-1][j])

    return M[m-1][n-1]


def main():
    string1 = input()
    string2 = input()
    print(levenshtein(string1, string2))


if __name__ == "__main__":
    main()
