#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#define FOUND 0
#define INFNTY 1000

using namespace std;

struct state
{
    char conf[9]; // configuration of the puzzle
    int index_x;  // tells where the 'x' is in the above array
    int depth;    // the depth in the tree (if it's -1, it's a invalid state)
    int f;        // evaluation function, which is equal to the heuristic function (we're gonna take the Manhattan distance) plus depth
};

// operador de igualdade para a struct acima
bool operator==(const state &s1, const state &s2)
{
    int i;

    for (i = 0; i < 9; i++)
    {
        if (s1.conf[i] != s2.conf[i])
        {
            return false;
        }
    }
    return true;
}

// final configuration of the puzzle (when solved)
char final_conf[9] = {'1', '2', '3', '4', '5', '6', '7', '8', 'x'};

// valid moves for the x's index (considering the table as an 2D array)
int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// tells if a configuration is solvable
bool is_solvable(char conf[9])
{
    int i;
    int j;
    int inversions = 0; // holds the number of invertions in 2the passed configuration

    // counts the number of inversions
    for (i = 0; i < 9; i++)
    {
        if (conf[i] != 'x')
        {
            inversions += ((conf[i] - '0') - 1); // number of tiles that should be before of the one in conf[i]

            // subtracts the number of tiles that are already before
            for (j = 0; j < i; j++)
            {
                if (conf[j] != 'x' && conf[j] < conf[i])
                {
                    inversions--;
                }
            }
        }
    }

    // if the number of inversions is even, the puzzle is solvable
    if (inversions % 2 == 0)
    {
        return true;
    }
    else // if it's odd, it's not
    {
        return false;
    }
}

// swaps to integers
void swap(char *a, char *b)
{
    char aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

// gets the Manhattan distance of a given configuration
// the way to do that is through the following equation:
// m_dist_unit = |x_1 - x_2| + |y_1 - y_2|
// where (if we imagine the table as a 3x3 grid with (x, y) coordinates):
// x_1 -> x coordinate of where a tile is
// x_2 -> x coordinate of where the same tile should be when the puzzle is solved
// y_1 -> y coordinate of where a tile is
// y_2 -> y coordinate of where the same tile should be when the puzzle is solved
// we do this to every tile in order to get the Manhattan distance (m_dist)
int manhattan_distance(char conf[9])
{
    int m_dist = 0; // the Manhattan distance
    int i;

    for (i = 0; i < 9; i++)
    {
        if (conf[i] != 'x')
        {
            m_dist += abs((i / 3) - (((conf[i] - '0') - 1) / 3)) + abs((i % 3) - (((conf[i] - '0') - 1) % 3));
        }
    }

    return m_dist;
}

// return the next 4 (max 4, min 2) states from a given one
void next_states(state origin, state next[4])
{
    // to generate the next states, we basically have to do 4 (at max.) swapping operations (x w/ neighboor tile)
    int i;

    for (i = 0; i < 4; i++)
    {
        // we're gonna derive the next using the origin
        next[i] = origin;
        // makes the swap, if it's not out of bound
        if ((((next[i].index_x / 3) + moves[i][0]) >= 0) && (((next[i].index_x / 3) + moves[i][0]) < 3) && (((next[i].index_x % 3) + moves[i][1]) >= 0) && (((next[i].index_x % 3) + moves[i][1]) < 3))
        {
            swap(&next[i].conf[next[i].index_x], &next[i].conf[3 * ((next[i].index_x / 3) + moves[i][0]) + ((next[i].index_x % 3) + moves[i][1])]);
            next[i].index_x = 3 * ((next[i].index_x / 3) + moves[i][0]) + ((next[i].index_x % 3) + moves[i][1]); // updates where the x is
            next[i].depth = origin.depth + 1;                                                                    // updates the depth
            next[i].f = manhattan_distance(next[i].conf) + next[i].depth;
        }
        else
        {
            // if it's not possible to make the swap...
            next[i].depth = -1; // marks as invalid and continues the for loop
        }
    }
}

// searchs the final state (when solved) through a given state (node)
int search(state node, int threshold, vector<char> *path, vector<state> *visited)
{
    state next[4]; // holds the next 4 states generated through 'node'
    int min;       // holds the minimum f
    int i;
    int temp;

    // stops if it hits the threshold
    if (node.f > threshold)
    {
        return node.f;
    }

    // goal node found
    if (memcmp(node.conf, final_conf, sizeof(node.conf)) == 0)
    {
        return FOUND;
    }

    // sets the minimum f and the next four (worst case scenario) states
    min = INFNTY;
    next_states(node, next);

    // iterates over every VALID next node
    for (i = 0; i < 4; i++)
    {
        if (next[i].depth != -1 && std::find(visited->begin(), visited->end(), next[i]) == visited->end())
        {
            // figures out which path we're taking and put in 'path'
            switch (i)
            {
            case 0:
                path->push_back('u');
                break;

            case 1:
                path->push_back('d');
                break;

            case 2:
                path->push_back('l');
                break;

            case 3:
                path->push_back('r');
            }

            visited->push_back(next[i]); // holds the visited
            temp = search(next[i], threshold, path, visited);
            if (temp == FOUND)
            {
                return FOUND;
            }
            if (temp < min)
            {
                min = temp;
            }

            path->pop_back();    // removes the step if it's not right
            visited->pop_back(); // removes the last visited
        }
    }

    return min;
}

// performs an IDA* search
bool ida_star(state root, vector<char> *path)
{
    int threshold;         // the thereshold applied at the moment
    int next_threshold;    // the next threshold applied
    vector<state> visited; // the already considered states

    threshold = root.f;
    while (true)
    {
        path->clear();
        visited.clear();
        visited.push_back(root);
        next_threshold = search(root, threshold, path, &visited);
        if (next_threshold == FOUND)
        {
            return true;
        }
        if (next_threshold == INFNTY)
        {
            return false;
        }
        threshold = next_threshold;
    }
}

// the main function
int main()
{
    int i;
    unsigned int j;
    int number_of_datasets;
    state initial; // initial state of the puzzle
    vector<char> path;
    int aux;

    scanf("%d", &number_of_datasets);

    for (i = 0; i < number_of_datasets; i++)
    {
        // clears the path
        path.clear();
        j = 0;

        if (i != 0)
        {
            printf("\n");
        }

        // depth of the root
        initial.depth = 0;

        // gets the initial configuration of the puzzle
        while (true)
        {
            aux = fgetc(stdin);

            if ((aux >= '1' && aux <= '8') || (aux == 'x'))
            {
                initial.conf[j] = aux;
                if (initial.conf[j] == 'x')
                {
                    initial.index_x = j; // saves where the 'x' is
                }
                if (j == 8)
                {
                    break;
                }
                j++;
            }
        }

        // gets the f of the root
        initial.f = initial.depth + manhattan_distance(initial.conf);

        // tests if the configuration has a solution
        if (is_solvable(initial.conf))
        {
            // if it's solvable, solve it and print the solution
            // we're gonna solve it using the IDA* algorithm
            ida_star(initial, &path);
            for (j = 0; j < path.size(); j++)
            {
                printf("%c", path[j]);
            }
            printf("\n");
        }
        else
        {
            printf("unsolvable\n");
        }
    }

    // bye!
    return 0;
}