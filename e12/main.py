def get_lis(list_of_dims):
    """
    Computes the longest increasing subsequence (LIS) of 'list_of_dims'. Returns
    a list with every element of the LIS. We use dynamic programming to do this.
    Note that 'list_of_dims' is a list of tuples, w/ each tuple being of the (w, h)
    format, such that 'w' stands for width and 'h', for height.   
    """
    n = len(list_of_dims)
    list_of_dims = sorted(list_of_dims, key = lambda dim: dim[0])  # sorting the list of tuples by width

    # buids the memoization matrix (initially, it's all set up to be zero):
    memoization = [[0 for j in range(n + 1)]
                   for i in range(n + 1)]

    # we use the dynamic programming iteration to evaluate every entry of 'memoization'
    for index_curr in range(1, n + 1):
        for index_next in range(n + 1):
            if index_next != n and (list_of_dims[index_curr - 1][1] > list_of_dims[index_next][1] or index_curr - 1 >= index_next):
                memoization[index_curr][index_next] = memoization[index_curr - 1][index_next]
            else:
                memoization[index_curr][index_next] = max(
                    memoization[index_curr - 1][index_next], 1 + memoization[index_curr - 1][index_curr - 1])                       

    return trace_back(memoization, list_of_dims, n, n, n, set())

def trace_back(memoization, list_of_dims, index_curr, index_next, n, lis):
    if index_curr != 0 and index_next != 0:
        if index_next != n and (list_of_dims[index_curr - 1][1] > list_of_dims[index_next][1] or index_curr - 1 >= index_next):
            trace_back(memoization, list_of_dims, index_curr - 1, index_next, n, lis)
        else:    
            if 1 + memoization[index_curr - 1][index_curr - 1] >= memoization[index_curr - 1][index_next]:
                lis.add(list_of_dims[index_curr - 1])
                trace_back(memoization, list_of_dims, index_curr - 1, index_curr - 1, n, lis)
            else:                           
                trace_back(memoization, list_of_dims, index_curr - 1, index_next, n, lis)
    return lis            

def main():
    # get number of test cases
    num_test_cases = int(input())

    for _ in range(num_test_cases):
        # user input for one test case
        input()  # get the number of dolls 
        dims = input()  # get the dimensions as string in one line
        dims = dims.split()  # split it at space
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