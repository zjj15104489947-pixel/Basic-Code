//DFS,BFS模板
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/*
    深度优先搜索 DFS
    用于：
    - 遍历图
    - 找连通分量
    - 树遍历
*/
void dfs(int node,
         const vector<vector<int>>& adj,
         vector<bool>& visited)
{
    visited[node] = true;
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, adj, visited);
        }
    }
}

/*
    广度优先搜索 BFS
    用于：
    - 无权图最短路径
    - 层次遍历
*/
vector<int> bfs(int start,
                const vector<vector<int>>& adj)
{
    int n = adj.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> visited(n + 1, false);

    // DFS 示例
    dfs(1, adj, visited);

    // BFS 示例
    vector<int> dist = bfs(1, adj);
  
    return 0;
}
