def get_lis(arr):
    """
    Find the longest increasing subsequence using a dynamic programming approach.
    """
    n = len(arr)
    arr = sorted(arr, key = lambda dim: dim[0])  # sorting the list of tuples by width

    # buids the memoization matrix (initially, it's all set up to be zero):
    M = [[0 for j in range(n)]
                   for i in range(n)]

    # we use the dynamic programming iteration to evaluate every entry of 'M'
    for i in range(n):
        if i == 0:
            for j in range(i, n):
                if j < n - 1 and (arr[i][1] >= arr[j+1][1] or arr[i][0] == arr[j+1][0]):
                    M[i][j] = 0
                else:
                    M[i][j] = 1    
        else:
            for j in range(i, n):
                if j < n - 1 and (arr[i][1] >= arr[j+1][1] or arr[i][0] == arr[j+1][0]):
                    M[i][j] = M[i-1][j]
                else:
                    M[i][j] = max(M[i-1][j], 1 + M[i-1][i-1])

    return trace_back_iterative(M, arr) # returns a set with every element of the lis                            
            
def trace_back_iterative(M, arr):
    lis = set()
    n = len(arr)
    i = n - 1
    j = n - 1

    while i >= 0 and j >= 0:
        if j >= i:
            if i == 0:
                if j < n - 1 and (arr[i][1] >= arr[j+1][1] or arr[i][0] == arr[j+1][0]):
                    i -= 1
                else:
                    lis.add(arr[i])
                    i -= 1
                    j = i           
            else:
                if j < n - 1 and (arr[i][1] >= arr[j+1][1] or arr[i][0] == arr[j+1][0]):
                    i -= 1
                else:
                    if 1 + M[i-1][i-1] >= M[i-1][j]:
                        lis.add(arr[i])
                        i -= 1
                        j = i
                    else:
                        i -= 1

    return lis

def main():
    # get number of test cases
    num_test_cases = int(input())

    for _ in range(num_test_cases):
        # user input for one test case
        num_dolls = int(input())  # get the number of dolls 
        dims = input()  # get the dimensions as string in one line
        dims = dims.split()  # split it at space
        while len(dims) / 2 != num_dolls:
            aux_dims = input()  # when the dimensions are given in different lines
            aux_dims = aux_dims.split()
            dims.extend(aux_dims)
        dims = [int(dim) for dim in dims]  # parse everything to int
        dims = [(dims[i], dims[i+1]) for i in range(0, len(dims) - 1, 2)]  # put every couple of dimensions (width and height) in a tuple 
        
        min_doll_number = 0
        while dims:
            to_remove = get_lis(dims)  # get the elements in the longest increasing subsequence in a set
            aux = []
            for i in range(len(dims)):  # delete them from the original list
                if dims[i] not in to_remove:
                    aux.append(dims[i])
                else:
                    to_remove.remove(dims[i])    
            dims = aux        
            min_doll_number += 1
        print(min_doll_number)  # prints the answer

if __name__ == "__main__":
    main()