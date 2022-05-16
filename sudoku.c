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

int is_valid(Node* n){
  for(int i=0;i<9;i++){
    int filaAux[10]={0};
    for(int j=0;j<9;j++){
      if(filaAux[n->sudo[i][j]]){
        return 0;
      }
      if(filaAux[n->sudo[i][j]]==0 && n->sudo[i][j]!=0){
        filaAux[n->sudo[i][j]]=1;
      }
    }
  }
  for(int i=0;i<9;i++){
    int columAux[10]={0};
    for(int j=0;j<9;j++){
      if(columAux[n->sudo[i][j]!=0]){
        return 0;
      }
      if(columAux[n->sudo[i][j]]==0 && n->sudo[i][j]!=0){
        columAux[n->sudo[i][j]]=1;
      }
    }
  }
  for ( int i = 0 ; i < 9 ; i++){
    int subAux[10] = {0};
    int k = i;
    for ( int j = 0 ; j < 9 ; j++){
      int z = 3*(k/3) + (j/3);
      int w = 3*(k%3) + (j%3);
      if ( subAux[n->sudo[z][w]] != 0) return 0;
      if ( subAux[n->sudo[z][w]] == 0 && n->sudo[z][w] != 0) subAux[n->sudo[z][w]] = 1;
    }
  }  

  return 1;
}


List* get_adj_nodes(Node* n){
  List*aux=createList();
  int  i,j,k;
  for(i = 0; i<9 ; i++){
    for(j = 0; j<9 ; j++){
      if(n->sudo[i][j]==0){
        for(k = 1; k<10 ; k++){
          n->sudo[i][j]=k;
          if(is_valid(n)){
            Node*adj = copy(n);
            pushBack(aux,adj);
          }
        }
        n->sudo[i][j]= 0;
        return aux;
      }
    }
  }    
  return aux;
}


int is_final(Node* n){
  for(int i=0 ;i<9;i++){
    for (int j =0;j<9;j++){
      //printf("[%i,%i] = %i\n",i,j,n->sudo[i][j]);
      if(n->sudo[i][j]==0) return 0;
    }
  }
    return 1;

}

Node* DFS(Node* initial, int* cont){
  Stack* aux=createStack();
  push(aux,initial);
  while(get_size(aux)!=0){
    Node* nodAux=top(aux);
    pop(aux);
    if(is_final(nodAux)) return nodAux;
    List* lista=get_adj_nodes(nodAux);
    Node* lisAux=first(lista);
    while(lisAux){
      push(aux,lisAux);
      lisAux=next(lista);
    }
    free(nodAux);
    cont++;
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