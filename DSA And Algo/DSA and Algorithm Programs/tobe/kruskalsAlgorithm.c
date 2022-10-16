#include <stdio.h>
//*Number of vertex in graph
#define nEdge 6
//*Maximum number of edges in given graph
#define MAX 99

struct edge
{
  int u;//Stores vertex number from to travel
  int v;//Stores vertex number togo to in travel
  int w;//Stores value of Graph uv
};
struct edge_list 
{
  struct edge data[MAX];//Stores the index number of edges connecting two vertexs and the weight of the connecting edge
  int n;//Helps to move in the array's index
};
//Values of weights of edges of graph(Ajacency Matrix)
int Graph[MAX][MAX]={
//   0  1  2  3  4  5   
    {0, 4, 4, 0, 0, 0},
    {4, 0, 2, 0, 0, 0},
    {4, 2, 0, 3, 2, 0},
    {0, 0, 3, 0, 0, 3},
    {0, 0, 2, 0, 0, 3},
    {0, 0, 4, 3, 3, 0}};

int main()
{
    struct edge_list elist;
    elist.n = 0;
    printf("%d", nEdge);
    for(int i=0;i<nEdge;i++)
    {
        for(int j=0;j<nEdge;j++)
        {
            if(Graph[i][j] != 0) 
            {
                elist.data[elist.n].u = i;
                elist.data[elist.n].v = j;
                elist.data[elist.n].w = Graph[i][j];
                elist.n++;
            }
      }
    }
    //Sorting Algorithm for arranging weights of edges in increasing order
    struct edge temp;
    for (int i=1;i<elist.n;i++)//1st
      {
          //By help of 2nd loop change is made only between two values or indexs, so that if last index's value is small than first index's value than the last index's value would not come to first index by the help of only 2nd loop and to make it possible we will use the 1st for loop which will make this 2nd loop changes on large scale
          for (int j=0;j<elist.n-1;j++)//2nd
          {
              if (elist.data[j].w > elist.data[j + 1].w)
              {
                  temp = elist.data[j];
                  elist.data[j] = elist.data[j + 1];
                  elist.data[j + 1] = temp;
              }
          }
      }
    
    //Storing Process
    int belongs[MAX];//Stores not linked vertexs of graph
    //At first all the index are equal to their original value as at first no vertex are linked and all are have to be linked 
    for(int i=0;i<nEdge;i++)//Oth
    {
       belongs[i] = i;
    }
    //For storing final arrangment of an spanning tree
    struct edge_list spanlist;
    //Make it start from the begining
    spanlist.n = 0;

    int parentVertexNum; //Stores vertex number from to travel
    int childVertexNum;//Stores vertex number togo to in travel

    //Loop for storing the sorted and lined data in the mannerd form
    for(int i=0;i<elist.n;i++)//1st
    {
        parentVertexNum = belongs[elist.data[i].u];
        childVertexNum = belongs[elist.data[i].v];
        //Only runs when the parent's and child's vertex are different, They are not different when the both are visited
        if(parentVertexNum != childVertexNum) 
        {
            //Here we had maked the new struct spanlist which is empty and in which we will make store the final arrangment to make an spanning tree by sorting and taking the data from the elist
            spanlist.data[spanlist.n] = elist.data[i];
            spanlist.n = spanlist.n + 1;
            
            //Applying union
            for(int j=0;j<nEdge;j++)//2nd
            {
                //if belongs[j] becomes equal to childVertexNum than make the belongs[j] equal to the parentVertexNum, hence now when we want to access the child's index in the belongs than it will automatically transfer us to its parent value which is not being linked in spanning tree, if the transfered value is linked to another than it will again transfer us to another, due to this the linking between the already linked vertex does not occur again, And when the parentVertexNum becomes equal to the childVertexNum than the editing stops, And that time all the vertexs are connected to each other, And hence spanning tree is completed no more changes!!

                //And when the if condition is not completed the addition of the data in the spanlist stops
                if(belongs[j] == childVertexNum)
                {
                    belongs[j] = parentVertexNum;
                }
            }
        }
    }
    // Printing the result(finally spanning tree)
    int cost = 0;
    for (int i=0;i<spanlist.n;i++) 
    {
        printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
        cost = cost + spanlist.data[i].w;
    }
    printf("\nSpanning tree cost: %d", cost);
}

// -->Input can also be taken by the user, by first asking the number of vertex in the graph, max. number of the edges in graph, And than taking the value of the weights for each vertex by the help of the two for loops the data will be taken in the format as follow, for this case(At every starting of line, enter is pressed by user):
// 6
// 99
// 0 4 4 0 0 0
// 4 0 2 0 0 0
// 4 2 0 3 2 0
// 0 0 3 0 0 3
// 0 0 2 0 0 3
// 0 0 4 3 3 0