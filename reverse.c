#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NODE struct node

struct node {
	int number;
	NODE *next;
};

NODE *head, *tail;

void generation(int);
void reverse(void);

int main(void) {
	int i;
	NODE *p;
	
	for(i = 1; i < 11; i++) {
		generation(i);
	}
	
	//printing
	p = head;
	for(i = 0; i < 10; i++) {
		printf("%d\t", p->number);
		p = p->next;
	}
	printf("\n");

	reverse();

	//printing
	p = head;
	for(i = 0; i < 10; i++) {
		printf("%d\t", p->number);
		p = p->next;
	}
	printf("\n");	
}

void generation(int n) {
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->number = n;
	if(head == NULL) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

void reverse() {
	NODE *q = NULL; 
	NODE *p = head; 
	NODE *z = head->next;
	while(z != NULL) {
		p->next = q;
		q = p;
		p = z;
		z = z->next;
	}
	p->next = q;
	tail = head;
	head = p;	
}



















