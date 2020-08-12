#include <stdio.h>
#include <stdlib.h>

typedef struct _edge {
    int v;
    int w;
} Edge;

typedef struct _graph {
    int nV;
    int nE;
    Edge *edges;
} *Graph;

Graph newGraph(int v) {
    Graph new = malloc(sizeof(struct _graph));
    new->nV = v;
    new->nE = 0;
    new->edges = malloc(sizeof(Edge));
    return new;
}

void freeGraph(Graph graph) {
    free(graph->edges);
    free(graph);
}

int checkValidEdge(Graph graph, int v, int w) {
    if (v < graph->nV && w < graph->nV) {
        return 1;
    }
    return 0;
}

int checkEdgeExists(Graph graph, int v, int w) {
    if (!checkValidEdge(graph,v,w)) return 0;
    for (int i = 0; i < graph->nE; i++) {
        if ((v == graph->edges[i].v && w == graph->edges[i].w) || (w == graph->edges[i].v && v == graph->edges[i].w)) {
            return 1;
        }
    }
    return 0;
}

Graph insertEdge(Graph g, int v, int w) {
    if (!checkValidEdge(g,v,w)) return g;
    if (checkEdgeExists(g,v,w)) return g;

    Edge edge;
    edge.v = v;
    edge.w = w;

    g->edges = realloc(g->edges, sizeof(g->edges)+sizeof(Edge));
    g->edges[g->nE] = edge;
    g->nE++;

    return g;
}

Graph deleteEdge(Graph graph, int v, int w) {
    if (!checkValidEdge(graph,v,w)) return graph;
    if (!checkEdgeExists(graph,v,w)) return graph;

    for (int i = 0; i < graph->nE; i++) {
        if ((v == graph->edges[i].v && w == graph->edges[i].w) || (w == graph->edges[i].v && v == graph->edges[i].w)) {
            graph->edges[i] = graph->edges[graph->nE-1];
            graph->nE--;
        }
    }
    return graph;
}

void showGraph(Graph g) {
    for (int i = 0; i < g->nE; i++) {
        printf("%d <-> %d\n", g->edges[i].v, g->edges[i].w);
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
    deleteEdge(g, 2, 3);
    showGraph(g);
    return 0;
}