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

typedef struct
{
   int sudo[9][9];
} Node;

int is_valid(Node *n) {
    // Verificar filas
    for (int i = 0; i < 9; i++) {
        int seen[10] = {0}; // Para números del 1 al 9
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) { // Ignorar ceros, si es que los consideramos vacíos
                if (seen[num]) {
                    return 0; // Número repetido en la fila
                }
                seen[num] = 1;
            }
        }
    }

    // Verificar columnas
    for (int j = 0; j < 9; j++) {
        int seen[10] = {0}; // Para números del 1 al 9
        for (int i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) { // Ignorar ceros, si es que los consideramos vacíos
                if (seen[num]) {
                    return 0; // Número repetido en la columna
                }
                seen[num] = 1;
            }
        }
    }

    // Verificar submatrices de 3x3
    for (int row = 0; row < 9; row += 3) {
        for (int col = 0; col < 9; col += 3) {
            int seen[10] = {0}; // Para números del 1 al 9
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = n->sudo[row + i][col + j];
                    if (num != 0) { // Ignorar ceros, si es que los consideramos vacíos
                        if (seen[num]) {
                            return 0; // Número repetido en la submatriz de 3x3
                        }
                        seen[num] = 1;
                    }
                }
            }
        }
    }

    return 1; // Todo es válido
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