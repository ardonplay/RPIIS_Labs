#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <ctime>
using namespace std;

const int INF = 1e5;

vector<pair<int, int>> graph[1000000];


int dijkstra(int start, int end, int n){

    int ans[1000000];
    for (int i = 0; i < n; i++) {
        ans[i] = INF;
    }

    ans[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    q.push({0, start});

    while (!q.empty()) {
        pair<int, int> c = q.top();
        q.pop();

        int dst = c.first, v = c.second;

        if (ans[v] < dst) {
            continue;
        }

        for (pair<int, int> e: graph[v]) {
            int u = e.first, len_vu = e.second;

            int n_dst = dst + len_vu;
            if (n_dst < ans[u]) {
                ans[u] = n_dst;
                q.push({n_dst, u});
            }
        }
    }
    return ans[end];
};
int main(int argc, char *argv[]) {
    clock_t start_of_time = clock();
    string destination = "../Tests/16.in";

    if(argv[1] != NULL) {
        destination = argv[1];
    }

    ifstream file;
    file.open(destination);
    //Ввод графа и вершин start и end.
    int n, m, k;
    file >> n >> m >> k;


    int start, end;
    file >> start >> end;
    start--;
    end--;


    int vertex, outex, weight;
    vector <pair<int, int >> Z_moment;
    int input_1, input_2;
    for(int count = 0; count < k; count++){
        file>>input_1>>input_2;
        Z_moment.emplace_back(input_1, input_2);
    }


    for(int index = 0; index < m; index++) {
        file >> vertex >> outex >> weight;
        vertex--;
        outex--;
        graph[vertex].emplace_back(outex, weight);
        graph[outex].emplace_back(vertex, weight);
    }

    int *output = new int[k];
    for(int index = 0; index < k; index++){
        output[index] = dijkstra(start, Z_moment[index].first-1, n) + Z_moment[index].second;
    }
    for(int index = 0; index < k; index++){
        output[index]+=dijkstra(Z_moment[index].first-1, end, n);
    }
    int min = output[0];
    for(int index =0; index < k; index++){
        if(min > output[index]) {
            min = output[index];
        }
    }
    file.close();
    ofstream save;
    save.open("../Output.txt", ios::app);
    cout<<min<<endl;
    save << min << endl;
    clock_t end_of_time = clock();
    double seconds = (double)(end_of_time - start_of_time) / CLOCKS_PER_SEC;
    cout<<seconds<<endl;
}
