#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "ErrorHandler.h"

graph* constructGraphFromInput(char* inputFilePath){
    graph* G = (graph*) malloc(sizeof(graph));
    int n, i, j, k;
    int* list;
    FILE* graph_file = fopen(inputFilePath, "rb");
    assertMemoryAllocation(G);
    assertFileOpen(graph_file, inputFilePath);
    assertFileRead(fread(&n, sizeof(int), 1, graph_file), 1, inputFilePath);
    list = malloc(sizeof(int) * n);
    assertMemoryAllocation(list);
    G->n = n;
    G->M = 0;
    G->spAdjMat = spmat_allocate_list(n);
    G->adjMat = createMatrix(n);

    for(i=0; i < n; ++i){
        assertFileRead(fread(&k, sizeof(int), 1, graph_file), 1, inputFilePath);
        assertFileRead(fread(list, sizeof(int), k, graph_file), k, inputFilePath);
        G->M += k;
        while(k>0){
            --k;
            j = list[k];
            setVal(G->adjMat, i, j, 1);
        }
        G->spAdjMat->add_row(G->spAdjMat, G->adjMat->values[i], i);
    }
    fclose(graph_file);
    free(list);

    return G;
}

graph* constructGraphFromMatrix(double* adjMatrix, int n){
    graph* G = (graph*) malloc(sizeof(graph));
    int i, j;
    assertMemoryAllocation(G);
    G->n = n;
    G->M = 0;
    G->spAdjMat = spmat_allocate_list(n);
    G->adjMat = createMatrix(n);

    for(i=0; i < n; ++i){
        for(j=0; j < n; ++j) {
            setVal(G->adjMat, i, j, adjMatrix[i*n+j]);
        }
        G->M += G->adjMat->rowSums[i];
        G->spAdjMat->add_row(G->spAdjMat, G->adjMat->values[i], i);
    }

    return G;
}

void destroyGraph(graph* G){
    G->spAdjMat->free(G->spAdjMat);
    freeMatrix(G->adjMat);
    free(G);
}

int getEdge(graph* G, int i, int j){
    return readVal(G->adjMat, i, j);
}

void printGraph(graph* G){
    printMatrix(G->adjMat);
}

int getDegree(graph* G, int i){
    return G->adjMat->rowSums[i];
}
