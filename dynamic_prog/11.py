def subset_sum(weights, cutoff):
    """
    Computes the weighted subset sum of a set with the same elements of 'weights', considering 'cutoff' as the limit.
    We do this iteratively, using a memoization matrix.
    """
    
    n = len(weights)
    weights.append(0)  # dummy weight; 'n' is now the original length of this list    
    weights.sort()  # to solve it using dynamic programming, the weights have to be sorted

    # buids the memoization matrix (initially, it's all set up to be zero):
    memoization = [[0 for j in range(cutoff + 1)]
                   for i in range(n + 1)]

    # we use the dynamic programming iteration to evaluate every entry of 'memoization'
    # it basicailly applies the recursion 6.8, page 269 of the book Algorithm Design (Kleinberg, Tardos)
    for weight_index in range(1, n + 1):
        for max_weight in range(cutoff + 1):
            if max_weight < weights[weight_index]:
                memoization[weight_index][max_weight] = memoization[weight_index - 1][max_weight]
            else:
                memoization[weight_index][max_weight] = max(
                    memoization[weight_index - 1][max_weight], weights[weight_index] + memoization[weight_index - 1][max_weight-weights[weight_index]])

    # in this case, we just return the sum of the weights in the optimal subset, but we could use the memoization matrix to trace back every element of the optimal subset
    return memoization[n][cutoff] 


def main():
    # get number of test cases
    num_test_cases = int(input())

    for _ in range(num_test_cases):
        # user input for one test case
        weights = input()  # get everything as string in one line
        weights = weights.split()  # split it at space
        weights = [int(weight) for weight in weights]  # parse everything to int

        # one of the conditions for a "YES": the sum of 'weights' has to be even
        sum_weights = sum(weights)
        if not sum_weights % 2:
            # to solve the problem we're going to find the weighted subset sum, with cutoff being half the sum of all weights
            cutoff = sum_weights / 2

            # if the maximum weight under the cutoff is cutoff itself, then we have a yes
            if subset_sum(weights, int(cutoff)) == cutoff:
                print("YES")
            else:
                print("NO")
        else:
            print("NO")


if __name__ == "__main__":
    main()
