#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _graph {
    int nV;
    int **edges;
} *Graph;

Graph newGraph(int v) {
    Graph new = malloc(sizeof(struct _graph));
    new->nV = v;
    new->edges = malloc(sizeof(int*) * v);
    for (int i = 0; i < v; i++) {
        new->edges[i] = malloc(sizeof(int)*v);
        for (int j = 0; j < v; j++) {
            new->edges[i][j] = 0;
        }
    }
    return new;
}

void freeGraph(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g);
}


int checkValidEdge(Graph graph, int v, int w) {
    if (v < graph->nV && w < graph->nV) {
        return 1;
    }
    return 0;
}


Graph insertEdge(Graph g, int v, int w) {
    if (!checkValidEdge(g,v,w)) return g;

    g->edges[v][w] = 1;
    g->edges[w][v] = 1;

    return g;
}

Graph removeEdge(Graph g, int v, int w) {
    if (!checkValidEdge(g,v,w)) return g;

    g->edges[v][w] = 0;
    g->edges[w][v] = 0;

    return g;
}

int dfsPathCheck(Graph g, int src, int dest, int *visited) {
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[src][dest] == 1) {
            visited[dest] = src;
            return 1;
        } else {
            if (visited[i] == -1) {
                visited[i] = src;
                if (dfsPathCheck(g, i, dest, visited)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int findPath(Graph g, int src, int dest) {
    int *visited = malloc(sizeof(int)*g->nV);
    visited[src] = src;
    for (int i = 1; i < g->nV; i++) visited[i] = -1;
    if (!dfsPathCheck(g, src, dest, visited)) return 0;
    for (int i = dest; i != src; i = visited[i]) {
        printf("->%d\n", i);
    }
    printf("->%d\n", src);
    return 1;
}

int hasPath(Graph g, int src, int dest) {
    int *visited = malloc(sizeof(int)*g->nV);
    visited[src] = src;
    for (int i = 1; i < g->nV; i++) visited[i] = -1;
    return dfsPathCheck(g, src, dest, visited);

}

void showGraph(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        for (int j = 0; j < g->nV; j++) {
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    // Initialise Graph
    int graphSize = 0;
    printf("Enter graph size: ");
    scanf("%d", &graphSize);
    Graph g = newGraph(graphSize);

    int v = 0;
    int w =0;

    printf("v: ");
    scanf("%d", &v);
    printf("w: ");
    scanf("%d", &w);

    while (v != -1 && w != -1) {
        insertEdge(g, v, w);
        showGraph(g);
        printf("v: ");
        scanf("%d", &v);
        printf("w: ");
        scanf("%d", &w);
    }
    if(hasPath(g, 1, 5)) {
        printf("A path exists!\n");
    } else {
        printf("No path exists!\n");
    }

    return 0;
}