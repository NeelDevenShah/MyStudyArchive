#include<stdio.h>
#include<limits.h>

// number of vertices in graph
#define V 6

// create a 2d array of size vxv
//for adjacency matrix to represent graph
int adjacencyMatrix[V][V] = {
 {0, 4, 4, 0, 0, 0},
    {4, 0, 2, 0, 0, 0},
    {4, 2, 0, 3, 2, 0},
    {0, 0, 3, 0, 0, 3},
    {0, 0, 2, 0, 0, 3},
    {0, 0, 4, 3, 3, 0}};

int main() 
{
  int no_edge;  // number of edge

  // create a array to track selected vertex
  int selected[V];

  for(int i=0;i<V;i++)
  {
    selected[i]=0;
  }
  
  // set number of edge to 0
  no_edge = 0;

  // the number of egde in minimum spanning tree will be
  // always less than (V -1), where V is number of vertices in
  //graph

  // choose 0th vertex and make it true
  selected[0] = 1;

  int x;  //  row number
  int y;  //  col number

  // print for edge and weight
  printf("Edge : Weight\n");

  while (no_edge < V - 1) 
  {
    int min =INT_MAX;
    x = 0;
    y = 0;

    for (int i = 0; i < V; i++)
    {
      if (selected[i])
      {
        for (int j = 0; j < V; j++)
        {
          if (!selected[j] && adjacencyMatrix[i][j])
          {
            if (min > adjacencyMatrix[i][j])
            {
              min = adjacencyMatrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    printf("%d - %d : %d\n", x, y, adjacencyMatrix[x][y]);
    selected[y] = 1;
    no_edge++;
  }
  return 0;
}