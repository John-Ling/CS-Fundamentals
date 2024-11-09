#ifndef BFS_And_DFS_H
#define BFS_And_DFS_H
#include <stdio.h>
#include <stdlib.h>

#include "queues.h"
#include "stacks.h"

#define N 7
int dfs(int graph[N][N], int start);
int bfs(int graph[N][N], int start);
static int get_adjacent(int graph[N][N], int adjacent[N - 1], int* count, int node);

#endif