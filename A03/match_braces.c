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
  struct node* new_node = NULL; 

  new_node = (struct node *)malloc(sizeof(struct node));
  
  if(new_node == NULL){
    printf("Failed to insert element. Out of memory");
    exit(1);
  }
  if(top == NULL){
    new_node -> sym = sym;
    new_node -> linenum = line;
    new_node -> colnum = col;
    new_node -> next = NULL;
    return new_node;
  }
  new_node -> sym = sym;
  new_node -> linenum = line;
  new_node -> colnum = col;
  new_node -> next = top;

  return new_node;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  
  struct node* saveTop = top;

  if(top == NULL){
    printf("Stack overflow \n");
    return NULL;
  }
  saveTop = top;
  top = top -> next; 
  free(saveTop);
  return top;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node* current = top;
  struct node* temp = top; 

  while (current != NULL){
    current = current -> next;
    free(temp);
    temp = current; 
  }
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  struct node* current = top;
  if(top == NULL) {
    printf("Empty stack\n");
    return;
  }
  while(current != NULL){
    printf("Unmatched brace on Line %d and Column %d\n", current->linenum,current->colnum);
		current = current->next;
  }
}

int main(int argc, char* argv[]) {
  FILE *infile =  NULL;
  char current[32];
  int line = 1; 
  int col = 1;
  char c = ' ';

  struct node* top = NULL; 

  if (argc < 2){
    printf("Missing Filename\n");
    return(1);
  }
  else{
    printf("Filename : %s\n", argv[1]);
  }

  infile = fopen(argv[1], "r");

  if(infile == NULL){
    printf("Cannot open file: %s\n",argv[1]);
  }
  
  while(c = fgetc(infile)) {
		if (feof(infile) || c == '\0') {
			break;
		}
		if (c == '{') {
			top = push(c, line, col, top);		
		} 
    else if (c == '}') {
			if (top != NULL) {
				printf("Found matching braces: (%d, %d) -> (%d, %d)\n", top->linenum, top->colnum, line, col);
				top = pop(top);
			} 
			else {
				printf("Unmatched brace on Line %d and Column %d\n", line, col);
			}
		} 
    else if (c == '\n') {
			line++;
			col = 1;
			continue;
		}
		col++;	
	}
	print(top);
	fclose(infile);
	clear(top);
	return 0;
}
