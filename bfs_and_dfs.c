#include <stdio.h>
#include <stdlib.h>

// implementation of DFS and BFS for learning purposes

#define N 7

int main(void)
{
    // adjacency matrix to represent a graph
    int graph[N][N] = {
                        {0, 1, 0, 1, 0, 0, 0},
                        {1, 0, 1, 1, 0, 1, 1},
                        {0, 1, 0, 1, 1, 1, 0},
                        {1, 1, 1, 0, 1, 0, 0},
                        {0, 0, 1, 1, 0, 0, 1},
                        {0, 1, 1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 1, 0, 0}
        };



    return EXIT_SUCCESS;
}

int dfs(int graph[N][N])
{
    return EXIT_SUCCESS;
}

int bfs(int graph[N][N])
{
    return EXIT_SUCCESS;
}