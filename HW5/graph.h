#ifndef GRAPH_H
#define GRAPH_H


#include <limits.h>
#include "random_generator.h"

#include <iostream>

using namespace std;
class graph
{
private:
    int no_vert;   // Number of vertices
    int no_edges;  // Number of edges
    int weights;   // Weight interval
    int **m_edge;  // Adjacency matrix
    int *dist;     // Distance array for algorithms like Bellman-Ford
    int *parent;   // Parent array for algorithms like Bellman-Ford

public:
    // Constructors and Destructor
    graph(int n, int m, int w);
    graph(int n);
    ~graph();

    // Other member functions
    void initialize();
    bool set_edge(int u, int v, int w);
    void init_single_source(int s);
    void relax(int u, int v, int w);
    bool bellmanFord(int s);
    void floyd_warshall();
    void random_graph();
    bool edges_complete();
    void permutation(int *perm, int n);
    void output();
    void output_matrix(int **D);
    void allocateMemory();
    void deleteMatrix(int **matrix);
};

#endif // GRAPH_H
