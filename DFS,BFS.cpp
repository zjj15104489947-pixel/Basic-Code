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
    vector<int> dist(n + 1, -1); //记录起点到节点i的距离
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


//DFS，BFS例题

//DFS，判断是否存在欧拉回路 
#include <iostream>
#include <vector>

using namespace std;

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

bool hasEulerCircuit(int n, int m)
{
    vector<vector<int>> adj(n + 1);
    vector<int> degree(n + 1, 0);
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        degree[u]++;
        degree[v]++;
    }

    int startNode = 1;

    while (startNode <= n && adj[startNode].empty())
    {
        startNode++;
    }

    if (startNode > n)
    {
        return false;
    }

    dfs(startNode, adj, visited);

    for (int i = 1; i <= n; i++)
    {
        if (!adj[i].empty() && !visited[i])
        {
            return false;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (degree[i] % 2 != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, m;

    cin >> n >> m;

    if (hasEulerCircuit(n, m))
        cout << "存在欧拉回路" << endl;
    else
        cout << "不存在欧拉回路" << endl;

    return 0;
}

//DFS遍历所有节点后回溯 (点亮所有灯之后回到起点) 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int node,
         const vector<vector<int>>& adj,
         vector<bool>& visited,
         vector<int>& path)
{
    visited[node] = true;
    path.push_back(node);

    for (int next : adj[node])
    {
        if (!visited[next])
        {
            dfs(next, adj, visited, path);
            path.push_back(node);   // 回溯路径
        }
    }
}

int main()
{
    int N, M, S;
    cin >> N >> M >> S;

    vector<vector<int>> adj(N + 1);
    vector<bool> visited(N + 1, false);
    vector<int> path;

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 保证编号小的优先访问
    for (int i = 1; i <= N; i++)
    {
        sort(adj[i].begin(), adj[i].end());
    }

    dfs(S, adj, visited, path);

    bool allVisited = true;

    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
        {
            allVisited = false;
            break;
        }
    }

    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1 || !allVisited)
        {
            cout << " ";
        }
    }

    if (!allVisited)
    {
        cout << 0;
    }

    cout << endl;

    return 0;
}


//BFS六度空间(计算每个结点距离不超过6的结点数占总数比)
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip> 

using namespace std;

/*
    BFS：计算从 start 出发的最短距离（无权图）
*/
vector<int> bfs(int start, const vector<vector<int>>& adj)
{
    int n = adj.size() - 1;

    vector<int> dist(n + 1, -1);  // -1 表示未访问
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
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++)
    {
        vector<int> dist = bfs(i, adj);

        int count = 0;

        for (int j = 1; j <= N; j++)
        {
            if (dist[j] != -1 && dist[j] <= 6)
            {
                count++;
            }
        }

        double percentage = (double)count / N * 100;

        cout << i << ": "
             << fixed << setprecision(2)
             << percentage << "%" << endl;
    }

    return 0;
}
