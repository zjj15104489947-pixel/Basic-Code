//Dijkstra算法 有向边
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

using ll = long long;
using pii = pair<ll, int>; // {distance, node}

/*
    Dijkstra（带路径计数）
    返回：
    dist[i]：最短距离
    ways[i]：最短路径条数
*/
pair<vector<ll>, vector<ll>> dijkstra(
    int n,
    int start,
    const vector<vector<pair<int, int>>>& adj)
{
    const ll INF = numeric_limits<ll>::max(); //定义无穷大

    vector<ll> dist(n + 1, INF); //记录起点到每个点最短距离
    vector<ll> ways(n + 1, 0); //记录起点到每个点最短路径条数
    vector<bool> visited(n + 1, false); //标记是否已确定最短路径

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[start] = 0;
    ways[start] = 1;

    pq.push({0, start});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto [v, w] : adj[u])
        {
            // 找到更短路径
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                pq.push({dist[v], v});
            }
            // 找到同样短路径（累加）
            else if (dist[u] + w == dist[v])
            {
                ways[v] += ways[u];
            }
        }
    }

    return {dist, ways};
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w}); // 有向图
    }

    auto [dist, ways] = dijkstra(n, s, adj);

    for (int i = 1; i <= n; i++)
    {
        if (i == s) continue;

        cout << dist[i] << " " << ways[i] << endl;
    }

    return 0;
}

//Floyd算法
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using ll = long long;

/*
    Floyd-Warshall 算法
    计算：所有点对之间的最短路径
*/
vector<vector<ll>> floyd(int n, vector<vector<ll>> dist)
{
    for (int k = 1; k <= n; k++)        //中间点
    {
        for (int i = 1; i <= n; i++)    //起点
        {
            for (int j = 1; j <= n; j++)//终点
            {
                if (dist[i][k] == LLONG_MAX || dist[k][j] == LLONG_MAX)
                    continue;

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;

    const ll INF = numeric_limits<ll>::max();

    //初始化邻接矩阵
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    //自己到自己距离为0
    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }

    //读入边
    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        //如果有重边，取最小
        dist[u][v] = min(dist[u][v], w);
    }

    //Floyd
    dist = floyd(n, dist);

    //输出结果
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
