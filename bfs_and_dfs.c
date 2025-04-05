#include "bfs_and_dfs.h"

// implementation of DFS and BFS for learning purposes

int main(void)
{
    int graph[N][N] = {
    //   0  1  2  3  4  5  6
        {0, 1, 0, 1, 0, 0, 0}, // 0
        {1, 0, 1, 1, 0, 1, 1}, // 1
        {0, 1, 0, 1, 1, 1, 0}, // 2
        {1, 1, 1, 0, 1, 0, 0}, // 3
        {0, 0, 1, 1, 0, 0, 1}, // 4
        {0, 1, 1, 0, 0, 0, 0}, // 5
        {0, 1, 0, 0, 1, 0, 0} //  6
    };

    puts("DFS");
    dfs(graph, 0);
    
    puts("BFS");
    bfs(graph, 0);

    return EXIT_SUCCESS;
}

int dfs(int graph[N][N], int start)
{
    if (start > N || start < 0)
    {
        return EXIT_FAILURE;
    }

    // keep track of visited nodes
    int visited[N] = {0};
    
    // keep track of nodes in frontier efficiently
    int inFrontier[N] = {0};

    visited[start] = 1;
    inFrontier[start] = 1;

    // create stack with inital value of start
    Stack* frontier = LibStack.create(NULL, 0, sizeof(int));
    LibStack.push_int(frontier, start);
    int currentNode = start;

    // keep going until there are no more nodes to explore
    while (!LibStack.is_empty(frontier))
    {
        LibStack.pop(frontier, &currentNode); // get top of stack to update current node
        printf("%d ", currentNode);
        visited[currentNode] = 1; // mark node as visited
        inFrontier[currentNode] = 0; // node is no longer in frontier

        int adjacent[N - 1];
        int adjacentCount = 0;
        get_adjacent(graph, adjacent, &adjacentCount, currentNode);

        // put adjacent nodes into frontier
        for (int i = 0; i < adjacentCount; i++)
        {
            if (visited[adjacent[i]] == 1 || inFrontier[adjacent[i]] == 1)
            {
                // node has already been visited
                continue;
            }

            LibStack.push_int(frontier, adjacent[i]);
            inFrontier[adjacent[i]] = 1;
        }        
    }
    putchar('\n');

    LibStack.free(frontier, NULL);

    return EXIT_SUCCESS;
}

int bfs(int graph[N][N], int start)
{
    if (start > N || start < 0)
    {
        return EXIT_FAILURE;
    }

    // keep track of visited nodes
    int visited[N] = {0};
    
    // keep track of nodes in frontier efficiently
    int inFrontier[N] = {0};

    visited[start] = 1;
    inFrontier[start] = 1;

    // create queue with inital value of start
    Queue* frontier = LibQueue.create(NULL, 0, sizeof(int));
    LibQueue.enqueue_int(frontier, start);
    int currentNode = start;

    // keep going until there are no more nodes to explore
    while (!LibQueue.is_empty(frontier))
    {
        LibQueue.dequeue(frontier, &currentNode); // get front of queue to update current node
        printf("%d ", currentNode);
        visited[currentNode] = 1; // mark node as visited
        inFrontier[currentNode] = 0; // node is no longer in frontier

        // get adjacent
        int adjacent[N - 1];
        int adjacentCount = 0;
        get_adjacent(graph, adjacent, &adjacentCount, currentNode);

        // put adjacent nodes into frontier
        for (int i = 0; i < adjacentCount; i++)
        {
            if (visited[adjacent[i]] == 1 || inFrontier[adjacent[i]] == 1)
            {
                // node has already been visited
                continue;
            }

            LibQueue.enqueue_int(frontier, adjacent[i]);
            inFrontier[adjacent[i]] = 1;
        }   
    }
    putchar('\n');
    LibQueue.free(frontier, NULL);

    return EXIT_SUCCESS;
}

// populate array adjacent with nodes connected to node
static int get_adjacent(int graph[N][N], int adjacent[N - 1], int* count, int node)
{
    if (node > N)
    {
        return EXIT_FAILURE;
    }

    int j = 0;
    for (int i = 0; i < N; i++)
    {
        if (graph[node][i] == 1)
        {
            adjacent[j] = i; // add node to adjacent
            *count += 1;
            j++;
        }
    }
    return EXIT_SUCCESS;
}