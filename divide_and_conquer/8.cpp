#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// merge two lists, order them, and count the inversions
vector<int> merge_and_count(vector<int> first_half, vector<int> second_half, int *num_inversions)
{
    vector<int> merged; // holds the vector after the merge process
    unsigned int i = 0;
    unsigned int j = 0;

    // merge and counts the inversions
    while (i < first_half.size() && j < second_half.size())
    {
        if (first_half[i] < second_half[j])
        {
            merged.push_back(first_half[i]);
            i++;
        }
        else
        {
            merged.push_back(second_half[j]);
            j++;
            *num_inversions = *num_inversions + (first_half.size() - i);  // we have an inversion every time an element from the second half comes first
        }
    }

    // once the above block is done, there will only be a part of one of the halves to be integrated into
    // the merged array
    while (i < first_half.size())
    {
        merged.push_back(first_half[i]);
        i++;
    }
    while (j < second_half.size())
    {
        merged.push_back(second_half[j]);
        j++;
    }

    return merged;
}

// divide  the list of numbers and call the function to merge it and
// count the numbers of inversions
vector<int> sort_and_count(vector<int> list_of_numbers, int *num_inversions)
{
    if (list_of_numbers.size() != 1)
    { // if the size of the list is 1, there's nothing we can do
        // divide the list in two halves
        std::size_t const half_size = list_of_numbers.size() / 2;
        std::vector<int> first_half(list_of_numbers.begin(), list_of_numbers.begin() + half_size);
        std::vector<int> second_half(list_of_numbers.begin() + half_size, list_of_numbers.end());

        // call the recursion in both halves
        first_half = sort_and_count(first_half, num_inversions);
        second_half = sort_and_count(second_half, num_inversions);

        // merge the two halves (counting the inversions and ordering)
        list_of_numbers = merge_and_count(first_half, second_half, num_inversions);
    }

    return list_of_numbers;
}

int main()
{
    int num_test_cases;
    int num_elements; // number of elements in the list
    vector<int> list_of_elements;
    int num_inversions = 0; // the number of inversions in a list (aka, the answer)
    int i;
    int j;
    int aux;

    scanf("%d", &num_test_cases);

    for (i = 0; i < num_test_cases; i++)
    {
        scanf("%d", &num_elements);

        for (j = 0; j < num_elements; j++)
        {
            scanf("%d", &aux);
            list_of_elements.push_back(aux);
        }

        sort_and_count(list_of_elements, &num_inversions);
        printf("%d\n", num_inversions);

        // reset variables
        list_of_elements.clear();
        num_inversions = 0;
    }

    return 0;
}