#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

//вместо visited массив меток обычно называют used.
int main() {
    ifstream input;
    int V, E;
    input.open("../input3.in");
    input >> V >> E;
    vector<int> graph[2*E];
    bool used[1000];
    for(int i  = 0; i < E; i++){
        int a, b;
        input >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<int> q;
    q.push(0);              //в качестве начальной вершины используем 0.
    used[0] = true;
    int countStart =0, countSecond = 0;
    while (!q.empty()) {
        int cur = q.front();  //извлекаем из очереди текущую вершину
        q.pop();
        //Здесь должна быть обработка текущей вершины.
        cout << "BFS at vertex " << cur << endl;
        for (int neighbor: graph[cur]) {    //добавляем всех непосещённых соседей.
            if (!used[neighbor]) {
                q.push(neighbor);
                used[neighbor] = true;
                countStart++;
            }
        }
        cout<<countStart<<endl;

    }
}