#include "limits.h"
#include "graph.h"
#include <list>
#include <iostream>

using namespace std;

#include <cassert>

graph::graph(int n, int m, int w)
{
    assert(n > 2 && "Alert! Enter n > 2");
    assert(m > 1 && "Alert! Enter m > 1");

    int max_edges = n * n - n;
    assert(m <= max_edges && "Alert! Enter m <= (n*n - n)");

    no_vert = n;
    no_edges = m;
    weights = w;

    allocateMemory();
}

void graph::allocateMemory()
{
    m_edge = new int *[no_vert];

    for (int i = 0; i < no_vert; i++)
        m_edge[i] = new int[no_vert];

    initialize();

    dist = new int[no_vert];
    parent = new int[no_vert];
}

/*
 * constructor 2
 */
graph::graph(int n)
{
    assert(n >= 1 && "Alert! Enter n > 2");

    no_vert = n;
    allocateMemory();
}

/*
 * destructor
 */

graph::~graph()
{
    for (int i = 0; i < no_vert; i++)
    {
        delete[] m_edge[i];
    }
    delete[] m_edge;

    delete[] dist;
    delete[] parent;
}

/*
 * initialize adjacency matrix
 */
void graph::initialize()
{
    for (int i = 0; i < no_vert; i++)
    {
        for (int j = 0; j < no_vert; j++)
        {
            m_edge[i][j] = INT_MAX;
        }
    }
}

/*
 * set edges in case of a static graph
 */
bool graph::set_edge(int u, int v, int w)
{
    if (u > no_vert - 1 || v > no_vert - 1 || u < 0 || v < 0)
    {
        cout << "Please enter valid nodes." << endl;
        return false;
    }
    else
    {
        m_edge[u][v] = w;
        return true;
    }
}

/*
 * initialization for Bellman-Ford
 */

void graph::init_single_source(int s)
{
    if (s > no_vert - 1 || s < 0)
    {
        cout << "Invalid source node." << endl;
        return;
    }
    for (int i = 0; i < no_vert; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = INT_MAX;
    }
    dist[s] = 0;
}

void graph::relax(int u, int v, int w)
{
    if (u < 0 || u >= no_vert || v < 0 || v >= no_vert)
    {
        cout << "Invalid nodes." << endl;
        return;
    }

    if (dist[u] != INT_MAX && dist[v] > (dist[u] + w))
    {
        cout << "-------------------------" << endl;
        cout << "Relaxing Edge (" << u << "," << v << "):" << endl;
        dist[v] = dist[u] + w;
        cout << "Changing distance of Vertex[" << v << "] to : " << dist[v] << endl;
        parent[v] = u;
    }
}

bool graph::bellmanFord(int s)
{
    if (s < 0 || s >= no_vert)
    {
        cout << "Please enter a valid source node." << endl;
        return false;
    }

    init_single_source(s);

    for (int k = 0; k < no_vert - 1; k++)
    {
        cout << endl;
        cout << "Pass : " << k << endl;

        for (int i = 0; i < no_vert; i++)
        {
            for (int j = 0; j < no_vert; j++)
            {
                if (m_edge[i][j] != INT_MAX)
                {
                    relax(i, j, m_edge[i][j]);
                }
            }
        }
    }

    for (int i = 0; i < no_vert; i++)
    {
        for (int j = 0; j < no_vert; j++)
        {
            if (m_edge[i][j] != INT_MAX && dist[j] > dist[i] + m_edge[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

/*
 * Floyd-Warshall Algorithm for all-pairs shortest path
 */

void graph::floyd_warshall()
{
    int **D = new int *[no_vert];
    int **P = new int *[no_vert];

    for (int i = 0; i < no_vert; i++)
    {
        D[i] = new int[no_vert];
        P[i] = new int[no_vert];
    }

    // Initialization
    for (int i = 0; i < no_vert; i++)
    {
        for (int j = 0; j < no_vert; j++)
        {
            P[i][j] = (i != j && m_edge[i][j] < INT_MAX) ? i : INT_MAX;
            D[i][j] = (i != j) ? m_edge[i][j] : 0;
        }
    }

    // Floyd-Warshall Algorithm
    for (int k = 0; k < no_vert; k++)
    {
        for (int i = 0; i < no_vert; i++)
        {
            for (int j = 0; j < no_vert; j++)
            {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX)
                {
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                    P[i][j] = (D[i][j] == D[i][k] + D[k][j]) ? P[k][j] : P[i][j];
                }
            }
        }
    }

    // Output matrices
    cout << "Floyd-Warshall: Shortest Distance Matrix:" << endl;
    output_matrix(D);
    cout << "Floyd-Warshall: Predecessor Matrix:" << endl;
    output_matrix(P);

    // Deallocate memory
    deleteMatrix(D);
    deleteMatrix(P);
}

// Function to delete a matrix
void graph::deleteMatrix(int **matrix)
{
    for (int i = 0; i < no_vert; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}


void graph::random_graph()
{
    random_generator rg;
    int *perm = new int[no_vert];

    while (!edges_complete())
    {
        permutation(perm, no_vert);

        for (int i = 0; i < (no_vert - 2) && !edges_complete(); i++)
        {
            int v1 = perm[i];
            int v2 = perm[i + 1];

            if (m_edge[v1][v2] == INT_MAX)
            {
                int randomWeight = rand() % (2 * weights + 1) + (-weights);
                m_edge[v1][v2] = randomWeight;
            }
        }
    }

    delete[] perm;
}

bool graph::edges_complete()
{
    int count = 0;

    for (int i = 0; i < no_vert; i++)
    {
        for (int j = 0; j < no_vert; j++)
        {
            if (m_edge[i][j] != INT_MAX)
            {
                count++;
            }
        }
    }

    return count == no_edges;
}

void graph::permutation(int *perm, int n)
{
    for (int i = 0; i < n; i++)
        perm[i] = i;

    for (int i = 0; i < n; i++)
    {
        int p_pos = rand() % (n - i) + i;

        int p_tmp = perm[i];
        perm[i] = perm[p_pos];
        perm[p_pos] = p_tmp;
    }
}

void graph::output_matrix(int **matrix)
{
    cout << endl;
    cout << "[";
    for (int i = 0; i < no_vert; i++)
    {
        cout << "[\t";
        for (int j = 0; j < no_vert; j++)
        {
            if (matrix[i][j] == INT_MAX)
                cout << "Inf\t";
            else
                cout << matrix[i][j] << "\t";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
    cout << endl;
}

void graph::output()
{
    output_matrix(m_edge);
}
