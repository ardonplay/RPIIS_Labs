#include <iostream>
#include <fstream>
#include <ctime>

#define ll long long
#define INFINITY LLONG_MAX

ll graph[5000][5000];
ll cost[5000];

ll distA[5000];
ll distB[5000];

void Dijkstra(int n, int start, ll* distances)
{
    bool visited[n];

    for(int i = 0; i < n; i++)
    {
        distances[i] = graph[start][i];
        visited[i] = false;
    }

    distances[start] = 0;
    int index = 0;

    for(int i = 0; i < n; i++)
    {
        ll min = LLONG_MAX;

        for(int j = 0; j < n; j++)
        {
            if(!visited[j] && distances[j] < min)
            {
                min = distances[j];
                index = j;
            }
        }

        visited[index] = true;

        for(int j = 0; j < n; j++)
        {
            if (!visited[j] && graph[index][j] != INFINITY && distances[index] != INFINITY && (distances[index] + graph[index][j] < distances[j]))
            {
                distances[j] = distances[index] + graph[index][j];
            }
        }
    }


}

void solve(std::ifstream& in)
{
    int n, m, k, start, end;
    in >> n >> m >> k >> start >> end;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            graph[i][j] = INFINITY;
        }

        cost[i] = INFINITY;
    }

    ll a, b, c;

    for(int i = 0; i < k; i++)
    {
        in >> a >> b;
        cost[a - 1] = b;
    }

    for(int i = 0; i < m; i++)
    {
        in >> a >> b >> c;
        graph[a - 1][b - 1] = c;
        graph[b - 1][a - 1] = c;
    }

    Dijkstra(n, start - 1, distA);
    Dijkstra(n, end - 1, distB);

    ll min = LLONG_MAX;

    for(int i = 0; i < n; i++)
    {
        if(cost[i] != INFINITY)
        {
            min = std::min(min, distA[i] + cost[i] + distB[i]);
        }
    }
    std::ofstream file;
    file.open("../Output.txt",std::ios::app);
    std::cout << min << std::endl;
    file << min << std::endl;
    file.close();
}

int main()
{
    for(int i = 1; i <= 20; i++)
    {
        clock_t start_of_time = clock();
        std::ifstream is("../Tests/" + std::to_string(i) + ".in");
        solve(is);
        is.close();
        clock_t end_of_time = clock();
        double seconds = (double)(end_of_time - start_of_time) / CLOCKS_PER_SEC;
        std::cout<<seconds<<std::endl;
    }

    return 0;
}