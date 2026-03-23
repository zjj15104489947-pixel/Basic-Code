//Kruskal算法 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//并查集
class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank;  // 按秩合并（优化）

public:
    UnionFind(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return false;

        // 按秩合并
        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true;
    }
};


//边结构
struct Edge
{
    int u, v, weight;

    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // 按权重排序
    sort(edges.begin(), edges.end());

    UnionFind uf(n);

    int totalCost = 0;
    int edgesUsed = 0;

    for (const auto& e : edges)
    {
        if (uf.unite(e.u, e.v))
        {
            totalCost += e.weight;
            edgesUsed++;

            if (edgesUsed == n - 1)
                break;
        }
    }

    if (edgesUsed != n - 1)
    {
        cout << -1 << endl; // 不连通
    }
    else
    {
        cout << totalCost << endl;
    }

    return 0;
}

//Prim算法 
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

using pii = pair<int, int>; // {weight, node}

/*
    Prim算法（最小生成树）
    返回：
    - 最小生成树权重
    - 若图不连通返回 -1
*/
int prim(int n, const vector<vector<pii>>& adj)
{
    vector<bool> visited(n + 1, false);

    // 最小堆：{边权, 节点}
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    pq.push({0, 1}); // 从节点1开始

    int totalWeight = 0;
    int count = 0;

    while (!pq.empty())
    {
        auto [weight, u] = pq.top();
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        totalWeight += weight;
        count++;

        for (const auto& [w, v] : adj[u])
        {
            if (!visited[v])
            {
                pq.push({w, v});
            }
        }
    }

    // 如果没有覆盖所有点 →图不连通
    if (count != n)
        return -1;

    return totalWeight;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    int result = prim(n, adj);

    if (result == -1)
        cout << -1 << endl;
    else
        cout << result << endl;

    return 0;
}
