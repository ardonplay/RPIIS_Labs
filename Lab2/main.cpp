#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define MAXV 5100

class EdgeNode{
public:
    int key;
    int weight;
    EdgeNode *next;
    EdgeNode(int, int);
};

EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->next = nullptr;
}

class Graph{
    bool directed;
public:
    EdgeNode *edges[MAXV + 1];
    Graph(bool);
    ~Graph();
    void insert_edge(int, int, int, bool);
    void print();
};

Graph::Graph(bool directed){
    this->directed = directed;
    for(int i = 1; i < (MAXV + 1); i ++){
        this->edges[i] = nullptr;
    }
}

Graph::~Graph(){
    //to do
}

void Graph::insert_edge(int x, int y, int weight, bool directed){
    if(x > 0 && x < (MAXV + 1) && y > 0 && y < (MAXV + 1)){
        EdgeNode *edge = new EdgeNode(y, weight);
        edge->next = this->edges[x];
        this->edges[x] = edge;
        if(!directed){
            insert_edge(y, x, weight, true);
        }
    }
}

void init_vars(bool discovered[], int distance[], int parent[]){
    for(int i = 1; i < (MAXV + 1); i ++){
        discovered[i] = false;
        distance[i] = std::numeric_limits<int>::max();
        parent[i] = -1;
    }
}

void dijkstra_shortest_path(Graph *g, int parent[], int distance[], int start){

    bool discovered[MAXV + 1];
    EdgeNode *curr;
    int v_curr;
    int v_neighbor;
    int weight;
    int smallest_dist;

    init_vars(discovered, distance, parent);

    distance[start] = 0;
    v_curr = start;

    while(discovered[v_curr] == false){

        discovered[v_curr] = true;
        curr = g->edges[v_curr];

        while(curr != nullptr){

            v_neighbor = curr->key;
            weight = curr->weight;

            if((distance[v_curr] + weight) < distance[v_neighbor]){
                distance[v_neighbor] = distance[v_curr] + weight;
                parent[v_neighbor] = v_curr;
            }
            curr = curr->next;
        }

        //set the next current vertex to the vertex with the smallest distance
        smallest_dist = std::numeric_limits<int>::max();
        for(int i = 1; i < (MAXV + 1); i ++){
            if(!discovered[i] && (distance[i] < smallest_dist)){
                v_curr = i;
                smallest_dist = distance[i];
            }
        }
    }
}

int print_distances(int start, int distance[], int i){
            return distance[i];
}

int main(int argc, char *argv[]){
    string destination = argv[1] ;
    //cout<<destination<<endl;
    Graph *g = new Graph(false);
    int *temp = new int [10];
    int parent[MAXV + 1];
    int distance[MAXV + 1];
    int distance_from_A_to_Z;
    int N, M, K;
    int A, B, first_edge, second_edge, weight;
    vector<pair<int,int>> Z_moment;
    ifstream file;
    file.open(destination);
    if(!file){
        cout<<"file is not opened!"<<endl;
        return 0;
    }
    file >> N >> M >> K;
    file >> A >> B;
    int cache, cache2;
    int Default_Vertex = A;

    for(int i = 0; i < K; i++) {
        file >> cache >> cache2;
        Z_moment.emplace_back(cache, cache2);
    }

    for(int i = 0; i < M; i++){
        file >> first_edge >> second_edge >> weight;
        g->insert_edge(first_edge, second_edge, weight, false);
    }
    file.close();
    dijkstra_shortest_path(g, parent, distance, Default_Vertex);
    for(int i = 0; i < K; i++) {
        distance_from_A_to_Z = print_distances(Default_Vertex, distance, Z_moment[i].first);
        //cout << distance_from_A_to_Z + Z_moment[i].second << endl;
        temp[i] = distance_from_A_to_Z + Z_moment[i].second;
    }
    int min = temp[0], location = 0;
    for(int j = 0; j < K; j++){
        if(min >= temp[j]){
            min = temp[j];
            location = Z_moment[j].first;
        }
    }
    //cout<<"The shortest of the shortest is " << min << " from " << A << " to " << location<<endl;

    Default_Vertex = location;
    dijkstra_shortest_path(g, parent, distance, Default_Vertex);
   int distance_from_Z_to_B = print_distances(Default_Vertex, distance, B);
    distance_from_Z_to_B = distance_from_Z_to_B + min;

    //cout<< distance_from_Z_to_B << endl;
    ofstream save;
    save.open("../Output.txt", ios::app);
    save << distance_from_Z_to_B<<endl;
    save.close();
    delete g;
    return 0;
}