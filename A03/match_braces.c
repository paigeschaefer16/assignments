//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Paige Schaefer 
//
#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node * new_node = NULL;

  new_node = (struct node *)malloc(sizeof(struct node));
  
  if(new_node == NULL){
    printf("Stack overflow n");
  }

  new_node -> sym = sym;
  new_node -> linenum = line;
  new_node -> colnum = col;

  new_node -> next = top;

  top = new_node; 
  return top;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  
  struct node* tops;

  if(top == NULL){
    printf("Struck overflow n");
  }
  else{
    
    tops = top ->sym; 
    tops = top ->linenum; 
    tops = top ->colnum; 

    tops = top -> next;
    return tops;
  }

}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node* temp;

  while (top != NULL){
    temp = top;
    top = top -> next;
    free(temp);
  }
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  struct node* current_node = top;
  while ( current_node != NULL) {
        printf("%c %d %d", current_node->sym,current_node->linenum,
                            current_node->colnum);
        current_node = current_node->next;
    }
}

int main(int argc, char* argv[]) {
  FILE *infile =  NULL;
  char ch;
  int countsym = 0;
  int line = 0;
  int col = 0;
  
  
  if (argc < 2){
    printf("Missing Filename\n");
    return(1);
  }
  else{
    printf("Filename : %s\n", argv[1]);
   }
  infile = fopen(argv[1], "r");
  char input[100];
  if(infile){
    while ((ch = fgetc(infile)) != EOF ){
      line = line + 1;
      if(ch == '{' || ch == '}'){
        printf("%c",ch);
        countsym = countsym + 1; 
        input[countsym] = ch;
      }
    }
  }
  else{
    printf("Failed to open: %s\n",argv[1]);
  }
  printf("\n");

  for(int i = 0; i < countsym + 1; i++){
    printf("%c",input[i]);
  }

  struct node* stack = NULL;
  int index = 0;
  while(input[index]){
    if(input[index] == '{'){
      push(input[index],line,col,&stack);
    }
    if(input[index] == '}'){
      if(stack == NULL){
        printf("Stack is empty");
      }
      pop(&stack);
    }
    index++;
  }
  
  return 0;
}
