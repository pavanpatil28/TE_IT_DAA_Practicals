#include <bits/stdc++.h>
using namespace std;

const int maximum = 15; // Maximum number of cities, change this value as needed

// Function to copy temporary solution to the final solution
void copy(int cpath[], int fpath[], int N) 
{
    for (int i = 0; i < N; i++)
        fpath[i] = cpath[i];
    fpath[N] = cpath[0];
}

// Function to find the minimum edge cost having an end at the vertex i
int Min_1(int adj[][maximum], int i, int N) 
{
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

// Function to find the two minimum edge cost having an end at the vertex i
int Min_2(int adj[][maximum], int i, int N)
{
    int one = INT_MAX, two = INT_MAX;
    for (int j = 0; j < N; j++) 
    {
        if (i == j)
            continue;
        if (adj[i][j] <= one) 
        {
            two = one;
            one = adj[i][j];
        } 
        else if (adj[i][j] <= two && adj[i][j] != one)
            two = adj[i][j];
    }
    return two;
}

// Function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight -> stores the weight of the path so far
// level -> current level while moving in the search space tree
// cpath[] -> where the solution is being stored which would later be copied to fpath[]

void TSPRecursive(int adj[][maximum], int curr_bound, int curr_weight, int level, int cpath[], int fpath[], bool visited[], int N, int& final_res) 
{
    // Base case is when we have reached level N which means we have covered all the nodes once
    if (level == N) 
    {
        // Check if there is an edge from the last vertex in path back to the first vertex
        if (adj[cpath[level - 1]][cpath[0]] != 0) {
            int curr_res = curr_weight + adj[cpath[level - 1]][cpath[0]];
            if (curr_res < final_res) {
                copy(cpath, fpath, N);
                final_res = curr_res;
            }
            return;
        }
    }

    // For any other level, iterate for all vertices to build the search space tree recursively
    for (int i = 0; i < N; i++) 
    {
        // Consider the next vertex if it is not the same (diagonal entry in adjacency matrix) and not visited already
        if (adj[cpath[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[cpath[level - 1]][i];

            // Different computation of curr_bound for level 2 from the other levels
            if (level == 1)
                curr_bound -= ((Min_1(adj, i, N) + Min_1(adj, cpath[level - 1], N)) / 2);
            else
                curr_bound -= ((Min_2(adj, i, N) + Min_2(adj, cpath[level - 1], N)) / 2);

            // curr_bound + curr_weight is the actual lower bound for the node that we have arrived on
            // If the current lower bound < final_res, we need to explore the node further
            if (curr_bound + curr_weight < final_res) {
                cpath[level] = i;
                visited[i] = true;
                TSPRecursive(adj, curr_bound, curr_weight, level + 1, cpath, fpath, visited, N, final_res);
            }

            // Else, we have to prune the node by resetting all changes to curr_weight and curr_bound
            curr_weight -= adj[cpath[level - 1]][i];
            curr_bound = temp;

            // Also reset the visited array
            visited[i] = false;
            for (int j = 0; j < level; j++)
                visited[cpath[j]] = true;
        }
    }
}

// This function sets up fpath[]
void TSP(int adj[][maximum], int N) 
{
    int cpath[maximum + 1];
    bool visited[maximum];

    // Initialize final_res to a large value
    int final_res = INT_MAX;
    int fpath[maximum + 1];

    // Calculate initial lower bound for the root node
    int curr_bound = 0;
    memset(cpath, -1, sizeof(cpath));
    memset(visited, 0, sizeof(visited));

    // Compute initial bound
    for (int i = 0; i < N; i++)
        curr_bound += (Min_1(adj, i, N) + Min_1(adj, i, N));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    // We start at vertex 0, so the first vertex in cpath[] is 0
    visited[0] = true;
    cpath[0] = 0;

    // Call TSPRecursive for curr_weight equal to 0 and level 1
    TSPRecursive(adj, curr_bound, 0, 1, cpath, fpath, visited, N, final_res);

    // Print the result
    cout<<"\n --> Minimum cost = "<<final_res;
    cout<<"\n\n --> Path : ";
    for (int i = 0; i <= N; i++)
        cout<<fpath[i]<<" -> ";
        
    cout<<"\n\n";    
}

int main() 
{
    int N;
    
    cout<<"\n\n \t\t ***** Traveling Salesman Problem ***** \n\n\n";
    
    cout << " >> Enter the No of Places = ";
    cin >> N;

    // Adjacency matrix for the given graph
    int adj[maximum][maximum];
    cout << "\n >>> Enter the Adjacency Matrix :- \n\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
        	cout<<" >> Enter for adj["<<i+1<<"]["<<j+1<<"]:";
            cin >> adj[i][j];
        }
    }

    // Call the TSP function
    TSP(adj, N);

    return 0;
}

