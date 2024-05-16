#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct
{
   int sudo[9][9];
} Node;

Node* createNode()
{
  Node *n = (Node*)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n)
{
    Node *new = (Node *)malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name)
{
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++)
  {
       for(j=0;j<9;j++)
       {
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node *n)
{
    int i,j;
    for(i=0;i<9;i++)
    {
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node *n)
{
   // Se ubica en una de las submatriz 3x3
   for (int submatriz = 0 ; submatriz < 9 ; submatriz++)
   {
      // Comienza a recorrer los numeros del 1 al 9
      for (int num = 1 ; num <= 9 ; num++)
      {
         int enSubmatriz = 0;
         // Recorre la submatriz verificando si el numero esta
         for(int p = 0 ; p < 9 ; p++)
         {
            // Se posiciona en la fila y columna de la submatriz
            int i = 3 * (submatriz / 3) + (p / 3);
            int j = 3 * (submatriz % 3) + (p % 3);

            // Si el numero es igual al de pos en matriz y ya estaba antes
            if (n->sudo[i][j] == num && enSubmatriz == 1) return 0;
            else enSubmatriz = 1;
         }
      }
      
   }

    return 1;
}


List *get_adj_nodes(Node *n)
{
    List* list=createList();

   for (int i = 0 ; i < 9 ; i++)
      for (int k = 0 ; k < 9 ; k++)
      {
         if (n->sudo[i][k] == 0)
         {
            for (int j = 1 ; j <= 9 ; j++)
               {
                  Node *adjunto = copy(n);
                  adjunto->sudo[i][k] = j;
                  //print_node(adj);
                  //if (is_valid(adjunto))
                     pushBack(list, adjunto);
               }
         }
      }
   
   return list;
}


int is_final(Node *n)
{
    return 0;
}

Node *DFS(Node *initial, int *cont)
{
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/

/*
List *get_adj_nodes(Node *n)
{
    List* list=createList();

   for (int i = 0 ; i < 9 ; i++)
      for (int k = 0 ; k < 9 ; k++)
      {
         if (n->sudo[i][k] == 0)
         {
            for (int j = 1 ; j <= 9 ; j++)
               {
                  Node *adj = copy(n);
                  adj->sudo[i][k] = j;
                  if (is_valid(adj))
                     pushBack(list, adj);
               }
         }
      }
   
    return list;
}
*/