#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <limits.h>
#define V 10
#define MAX_DIST 25
#define PROBABILITY_THRESHOLD 1.0 - (float)MAX_DIST/((float)V * 10)
#define MAX MAX_DIST * MAX_DIST

void PrintGraph(int dist[][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == MAX)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void FloydWarshall (int graph[][V])
{
    int dist[V][V], i, j, k;
 
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

 
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    PrintGraph(dist);
}

int CreateGraph(int graph[][V]){

  srand(0);
  
  for(int i=0; i<V; i++){
    for(int j=0; j<V; j++){
      
      float edge_probability = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

      if(edge_probability > PROBABILITY_THRESHOLD) graph[i][j] = rand()%MAX_DIST + 1;
      else graph[i][j] = MAX;

    }

  }

  PrintGraph(graph);

}

int main()
{

    int graph[V][V];

    printf("GRAPH:\n");
    CreateGraph(graph);
    printf("\n");

    printf("DISTANCES:\n");
    FloydWarshall(graph);
    printf("\n");

    return 0;
}

