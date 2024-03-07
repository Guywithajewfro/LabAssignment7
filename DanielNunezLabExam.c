/*
	Edited by Daniel Nunez
	2/29/24
	Computer Science 1 Lab Exam 1
*/

#include <stdio.h>
#include <stdlib.h>

static int countsAllocated = 0;

struct Node {
  int value;
  struct Node *next;
};

void printList(struct Node *head) {
  struct Node *tmp = head;
  while (tmp != NULL) {
    printf("%d ", tmp->value);
    tmp = tmp->next;
  }
  printf("\n");
}

struct Node *allocateNode(int value) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->value = value;
  node->next = NULL;
  countsAllocated++;
  return node;
}

//Edited function. This function should take data from two linked lists, insert them into a new LL, and delete the nodes from the original LLs
struct Node *mergeLists(struct Node *pNumbers1, struct Node *pNumbers2) {
	struct Node tempPoint;	//Temporary node pointer
	struct Node *tail = &tempPoint;	//Tail pointer
	tail->next = NULL;
	
	while (pNumbers1 && pNumbers2) {
		if (pNumbers1->value < pNumbers2->value) {
			tail->next = pNumbers1;
			pNumbers1 = pNumbers1->next;
		} else {
			tail->next = pNumbers2;
			pNumbers2 = pNumbers2->next;
		}
		tail = tail->next;
	}
	tail->next = pNumbers1 ? pNumbers1 : pNumbers2;
	return tail;
}	//Ends mergLists function

void insert(struct Node **pHead, int value) {
  struct Node *newNode = allocateNode(value);
  newNode->next = *pHead;
  *pHead = newNode;
}

void *freeList(struct Node **pHead) {
  struct Node *tmp = *pHead;
  while (tmp != NULL) {
    *pHead = tmp->next;
    free(tmp);
    tmp = *pHead;
    countsAllocated--;
  }

  return *pHead;
}

int main(void) {
  int i, numInputs;
  char *str;
  float average;
  int value;
  int index;
  int *numArray = NULL;
  int countOfNums1;
  int countOfNums2;
  struct Node *head1 = NULL;
  struct Node *head2 = NULL;
  struct Node *head3 = NULL;

  FILE *inFile = fopen("input.txt", "r");

  fscanf(inFile, " %d\n", &numInputs);

  while (numInputs-- > 0) {
    head1 = NULL;
    head2 = NULL;
    head3 = NULL;
    fscanf(inFile, " %d %d\n", &countOfNums1, &countOfNums2);
    for (i = 0; i < countOfNums1; i++) {
      fscanf(inFile, " %d", &value);
      insert(&head1, value);
    }
    for (i = 0; i < countOfNums2; i++) {
      fscanf(inFile, " %d", &value);
      insert(&head2, value);
    }

    printf("List 1:\n");
    printList(head1);
    printf("List 2:\n");
    printList(head2);

    printf("Memory Allocated before merge : %d\n", countsAllocated);
    head3 = mergeLists(head1, head2);
    printf("List 3:\n");
    printList(head3);

    freeList(&head3);
    printf("Memory Allocated after free : %d\n", countsAllocated);
  }

  fclose(inFile);
}