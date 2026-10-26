#ifndef GRAPH_H
#define GRAPH_H

#define INF 999

int graph[7][7] =
{
    {0,4,3,7,INF,INF,INF},
    {4,0,2,INF,5,INF,INF},
    {3,2,0,4,6,INF,INF},
    {7,INF,4,0,2,5,INF},
    {INF,5,6,2,0,3,4},
    {INF,INF,INF,5,3,0,5},
    {INF,INF,INF,INF,4,5,0}
};

void dijkstra(int source, int destination)
{
    int dist[7], visited[7], parent[7];

    for(int i = 0; i < 7; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for(int i = 0; i < 7; i++)
    {
        int u = -1, minimum = INF;

        for(int j = 0; j < 7; j++)
        {
            if(!visited[j] && dist[j] < minimum)
            {
                minimum = dist[j];
                u = j;
            }
        }

        if(u == -1)
            break;

        visited[u] = 1;

        for(int v = 0; v < 7; v++)
        {
            if(graph[u][v] != INF && !visited[v] &&
               dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if(dist[destination] == INF)
    {
        cout << "No route available.\n";
        return;
    }

    int path[7], count = 0;

    for(int v = destination; v != -1; v = parent[v])
        path[count++] = v;

    cout << "Shortest Path: ";

    for(int i = count - 1; i >= 0; i--)
    {
        cout << path[i];

        if(i > 0)
            cout << " -> ";
    }

    cout << "\nShortest Distance: "
         << dist[destination] << " km\n";
}

#endif