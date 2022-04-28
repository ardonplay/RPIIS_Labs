#include <iostream>
#include <ctime>
#include <fstream>
// a structure to represent a unweighted edge in graph
struct Edge
{
    int src, dest;
};
 
// a structure to represent a connected, undirected
// and unweighted graph as a collection of edges.
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
 
// Function prototypes for union-find (These functions are defined
// after kargerMinCut() )
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
 
// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always
int kargerMinCut(struct Graph* graph)
{
    // Get data of given graph
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;
 
    // Allocate memory for creating V subsets.
    struct subset *subsets = new subset[V];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Initially there are V vertices in
    // contracted graph
    int vertices = V;
 
    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices > 2)
    {
       // Pick a random edge
       int i = rand() % E;
 
       // Find vertices (or sets) of two corners
       // of current edge
       int subset1 = find(subsets, edge[i].src);
       int subset2 = find(subsets, edge[i].dest);
 
       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
         continue;
 
       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
          printf("Contracting edge %d-%d\n",
                 edge[i].src, edge[i].dest);
          vertices--;
          Union(subsets, subset1, subset2);
       }
    }
 
    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2)
          cutedges++;
    }
 
    return cutedges;
}
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent =
             find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
 
// Driver program to test above functions
int main()
{
    /* Let us create following unweighted graph
        0------1
        | \    |
        |   \  |
        |     \|
        2------3   */
    int V;  // Number of vertices in graph
    int E;  // Number of edges in graph
    std::ifstream input;
    input.open("../input3.in");
    input>>V>>E;
    struct Graph* graph = createGraph(V, E);
    for(int i =0; i < E;i++){
        input>>graph->edge[i].src>>graph->edge[i].dest;
    }
 
    // Use a different seed value for every run.
    srand(time(nullptr));

    int *mass = new int [V*1000];
    int N = V*1000;
    int maxcount(1), nn(-1);
    for(int j = 0; j < N;j++){
        mass[j]=kargerMinCut(graph);
    }
    //перебираем все элементы массива
    for (int i = 0; i < N; i++)
    {
        int count(0);
        //перебираем все элементы от i до конца
        for (int j = i; j < N; j++)
            //если элемент i совпадает с одним из последующих (j), то увеличиваем число
            if (mass[i] == mass[j])
                count++;

        //если число больше ранее сохраненного - перезаписываем
        if (maxcount < count)
        {
            maxcount = count;
            nn = i;
        }
    }

    //выводим
    if (nn > -1)
        std::cout<<"Cut found by Karger's randomized algo is "<<mass[nn]<<std::endl;
    else
        //или то, что повторяющихся элементов нет
        std::cout << std::endl << "No repeating elements" << std::endl;
    return 0;
}