#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node *n) {
    int row_check[9][9] = {0};
    int col_check[9][9] = {0};
    int box_check[9][9] = {0};

    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            int num = n->sudo[i][j];
            if (num != 0) 
            {
                num--;  // Decrementar num 

                // Verificar filas
                if (row_check[i][num]) {
                  
                    return 0;
                }
                row_check[i][num] = 1;

                // Verificar columnas
                if (col_check[j][num]) 
                {
                    return 0;
                }
                col_check[j][num] = 1;

                // Verificar submatrices de 3x3
                int box_index = (i / 3) * 3 + (j / 3);
                if (box_check[box_index][num]) 
                {
                    return 0;
                }
                box_check[box_index][num] = 1;
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();
  int i,j;
  for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
        {
          //si encontró una casilla vacía
          if(n->sudo[i][j] == 0)
          {
            for(int k = 0; k < 9; k++)
              {
                Node *aux = copy(n);
                aux->sudo[i][j] = k + 1;
                if (is_valid(aux))
                {
                  pushBack(list, aux);
                }
              }
            return list;
          }
        }
    }
  return list;
}


int is_final(Node* n) 
{
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (n->sudo[i][j] == 0) 
            {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* pila = createStack();
  push(pila, initial);
  while(get_size(pila) != 0)
    {
      Node* n = top(pila);
      pop(pila);
      if(is_final(n))
      {
        return n;
      }
      List* list = get_adj_nodes(n);
      Node* aux = first(list);
      while(aux)
        {
          push(pila, aux);
          aux = next(list);
          
        }
      free(n);
      (*cont)++;
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