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
   for (int i = 0; i < 9; i++)
   {
      int numerosFila[10] = {0};
      for (int k = 0 ; k < 9 ; k++)
            if (n->sudo[i][k] != 0)
            {
               if (numerosFila[n->sudo[i][k]] == 1) return 0;
               else numerosFila[n->sudo[i][k]] = 1;
            }
   }

   for (int i = 0; i < 9; i++)
   {
      int numerosColumna[10] = {0};
      for (int k = 0 ; k < 9 ; k++)
         if (n->sudo[k][i] != 0)
         {
            if (numerosColumna[n->sudo[k][i]] == 1) return 0;
            else numerosColumna[n->sudo[k][i]] = 1;
         }
   }

   for (int submatriz = 0 ; submatriz < 9 ; submatriz++)
   {
      int numerosSubmatriz[10] = {0};
      for(int p = 0; p < 9; p++)
      {
         int i = 3 * (submatriz / 3) + (p / 3);
         int j = 3 * (submatriz % 3) + (p % 3);
         if (n->sudo[i][j] != 0)
         {
            if (numerosSubmatriz[n->sudo[i][j]] == 1) return 0;
            else numerosSubmatriz[n->sudo[i][j]] = 1;
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
            for (int j = 1 ; j <= 9 ; j++)
               {
                  Node *adjunto = copy(n);
                  adjunto->sudo[i][k] = j;
                  if (is_valid(adjunto))
                  {
                     pushBack(list, adjunto);
                     
                  }
                     pushBack(list, adjunto);
               }
      }
   
   return list;
}

int is_final(Node *n)
{
   for (int i = 0 ; i < 9 ; i++)
      for (int k = 0 ; k < 9 ; k++)
         if (n->sudo[i][k] == 0) return 0;
   
   return 1;
}

/*
.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
*/

Node *DFS(Node *initial, int *cont)
{
   // Cree un stack S (pila) e inserte el nodo.
   Stack *S = createStack();
   push(S, initial);

   // Mientras el stack S no se encuentre vacío:
   while (!is_empty(S))
   {
      // a) Saque y elimine el primer nodo de S.
      Node *n = top(S);
      pop(S);

      // b) Verifique si corresponde a un estado final, si es así retorne el nodo.
      if (is_final(n)) return n;

      // c) Obtenga la lista de nodos adyacentes al nodo.
      List *list = get_adj_nodes(n);

      // d) Agregue los nodos de la lista (uno por uno) al stack S.
      Node *aux = first(list);
      while (aux)
      {
         push(S, aux);
         aux = next(list);
      }
      
      // e) Libere la memoria usada por el nodo.
      free(n);
   }
   
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