#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>


typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

void InsertEdge(Graph G, int a, int b);
Graph CreateGraph(int* nodes, int i);
void DeleteGraph(Graph G);

struct _Queue
{
   int* key;
   int first;
   int rear;
   int qsize;
   int max_queue_size;
};

struct _Graph
{
   int size;
   int *node;
   int** matrix;
};


Graph CreateGraph(int* nodes, int max){
   max= max+1;
   Graph g = (Graph )malloc(sizeof(Graph));
   g->size = max;
   g->matrix = (int **)malloc(sizeof(int*)*max);

   for( int i = 0; i<max;i++)
   {
      g->matrix[i] = (int *)malloc(sizeof(int)*max);
      memset(g->matrix[i] , 0 , sizeof(int)*max);
   }
   for( int k = 1 ; k< max; k++)
   {
      g->matrix[0][k] = nodes[k-1];
      g->matrix[k][0] = nodes[k-1];
   }
   return g;
}

void InsertEdge(Graph G, int a, int b){
   int q=0;
   int w=0;

   for(q=0;q<G->size;q++)
   {
      if(a == G->matrix[0][q])
         break;
   }
   for(w=0; w<G->size; w++)
   {
      if(b == G->matrix[w][0])
         break;
   }
   G->matrix[q][w]++;



}

//void DeleteGraph(Graph G){
//
//
//}

int main(int argc, char **argv){
   FILE *fp = fopen(argv[1],"r");
   int Node_Of_Numbers[10000];
   int Temp;
   Graph G;
   int i = 0;
   int a, Minus, b;
   
   while(i<10)
   {   
      fscanf(fp, "%d", &Temp);
      Node_Of_Numbers[i] = Temp;
      i++;   
      fscanf(fp, "%c", &Temp);
      if(Temp == 10)
         break;
   }

   G=CreateGraph(Node_Of_Numbers,i);
   while(!feof(fp))
   {
      fscanf(fp, "%d", &a);
      fscanf(fp, "%c", &Minus);
      fscanf(fp, "%d ",&b);
      InsertEdge(G,a,b);   
   }
   for(int j = 0; j<i+1; j++)
   {
      for(int z = 0; z<i+1; z++)
         {
            if(j==0 && z==0)
               printf("  ");
            else
               printf( "%d ", G->matrix[j][z]);
         }
      printf("\n");
   }
   


   return 0;

}
