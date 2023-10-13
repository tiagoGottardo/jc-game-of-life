#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SPACE_WIDTH 20
#define SPACE_HEIGTH 20

void showUp (short **space) {
  printf("\n\n");
  for(int i = 0; i < SPACE_HEIGTH; i++) {
    printf("   %2d", SPACE_HEIGTH - i);
    for(int j = 0; j < SPACE_WIDTH; j++) {
      if(space[i][j])
        printf("⬛️");
      else
        printf("⬜️");
    }
    printf("\n");
  }
}

typedef struct Node {
  short i;
  short j;
  struct Node* next;
} Node;

void insertOnHead(Node** head, short i, short j) {
  if(!*head) {
    *head = (Node*) malloc(sizeof(Node));
    (*head)->i = i;
    (*head)->j = j;
  } else {
    Node* node = (Node*) malloc(sizeof(Node)); 
    node->i = i;
    node->j = j;
    node->next = *head;
    *head = node;
  }
}

void deleteOnHead(Node** head) {
  if(!(*head)) {
    *head = NULL;
    return;
  } else {
    if(!((*head)->next)) {
      *head = NULL;
      free(*head);
      return;
    }
    Node* ref = (*head)->next;
    *head = NULL;
    free(*head);
    *head = ref;
  }
}

void showList(Node* list) {
  Node* iterator = list;

  while(iterator) {
    printf("(%d;%d) ", iterator->i, iterator->j);
  
    iterator = iterator->next;
  }
  printf("\n");
}

short isSquareValid(short i, short j) {
  if(i < 0 || i >= SPACE_HEIGTH) return 0;
  if(j < 0 || j >= SPACE_WIDTH) return 0;

  return 1;
}

short flipBit(short num) {
  if(num == 0) return 1;
  else if(num == 1) return 0;
  return -1;
}

void applyChanges(short** space, Node** list) {
  printf("Inside before: ");
  showList(*list);
  while(*list) {
    if(isSquareValid((*list)->i, (*list)->j)) {
      space[(*list)->i][(*list)->j] = flipBit(space[(*list)->i][(*list)->j]);
    } 
    deleteOnHead(list);
  }
  printf("Inside after: ");
  showList(*list);
}

short countNeighborsAlive (short** space, short i, short j) {
  short count = 0;
  for(int x = -1; x <= 1; x++) {
    for(int y = -1; y <= 1; y++) {
      if(y != 0 || x != 0) {
        if(isSquareValid(i + x, j + y)) {
          count += space[i + x][j + y];
        }
      }
    }
  }

  return count;
}

short checkCellCases (short isAlive, short numberOfNeighborsAlive) {
  if(isAlive) {
    if(numberOfNeighborsAlive < 2 || numberOfNeighborsAlive >= 4)
      return 1;
    else
      return 0;
  } else {
    if(numberOfNeighborsAlive == 3)
      return 1;
    else
      return 0;
  }
} 

void verifyAllSquares(short** space, Node** list) {
  showList(*list);  
  for(short i = 0; i < SPACE_HEIGTH; i++) {
    for(short j = 0; j < SPACE_WIDTH; j++) {
      if(checkCellCases(space[i][j], countNeighborsAlive(space, i, j))) {
        insertOnHead(list, i, j);
      }
    }
  }
  showList(*list);  
  printf("\n");
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int main() {
  Node* list = NULL;

  short **space = (short**) calloc(SPACE_WIDTH, sizeof(short*));

  for(int i = 0; i < SPACE_WIDTH; i++) {
    space[i] = (short*) calloc(SPACE_HEIGTH, sizeof(short));
  }

  insertOnHead(&list, 4, 4);
  insertOnHead(&list, 4, 5);
  insertOnHead(&list, 4, 6);
  insertOnHead(&list, 5, 3);
  insertOnHead(&list, 6, 3);
  insertOnHead(&list, 7, 3);
  
  insertOnHead(&list, 9, 4);
  insertOnHead(&list, 9, 5);
  insertOnHead(&list, 9, 6);
  insertOnHead(&list, 5, 8);
  insertOnHead(&list, 6, 8);
  insertOnHead(&list, 7, 8);

  while (list) {
    applyChanges(space, &list);
    verifyAllSquares(space, &list);
    system("clear");
    showUp(space);
    delay(1000);    
    showList(list);
  } 

  return 0;
}
