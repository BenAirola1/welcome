/* Ben Airola
 * COEN 11
 * Lab 6
 * Wednesday 5:00 PM
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 20
#define SIZE 4
#define NODE struct node
#define LIST struct list

struct node {
	char name[LENGTH];
	int size;
	NODE *next;
};

struct list {
	NODE *head;
	NODE *tail;
};

LIST list[SIZE];

void insert(void);
void delete(void);
void list_groups(void);
void search_size(void);
void clear(void);
void change_size(void);
int check_duplicate(char*);

int main() {
	int input, j;
	//initializing list to NULL
	for(j = 0; j < SIZE; j++) {
		list[j].head = NULL;
		list[j].tail = NULL;
	}
	
	printf("\nWelcome to the Surf Lesson Scheduler!\n\n");
	printf("(1) Schedule Appointment\n");
	printf("(2) Remove Appointment\n");
	printf("(3) List Schedule\n");
	printf("(4) Search Parties of a Desired Size\n");
	printf("(5) Change a party's size\n");
	printf("(0) Exit\n\n");

	while(1) {
		scanf("%d", &input);
		
		switch(input) {
			case 0:
				clear();
				return 1;
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				list_groups();
				break;
			case 4:
				search_size();
				break;
			case 5:
				change_size();
				break;
			default:
				printf("That command is not valid.\n");
				printf("1, 2, 3, 4, or 5 are valid commands.\n\n");
				break;
		}
	}
	return 1;
}
void insert() {
	//variable instantiation
	char name[LENGTH];
	int size;
	LIST *z;
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	if(temp == NULL) {
		printf("Memory Allocation Error.");
		return;
	}
	
	//getting user input	
	printf("Name: ");
	scanf("%s", name);
	if(check_duplicate(name) == 1) {
		printf("This group is already on our waitlist.\n");
		return;
	}
	printf("Group Size: ");
	scanf("%d", &size);

	//copying input to new NODE temp
	strcpy(temp->name, name);
	temp->size = size;
	temp->next = NULL;

	//finding proper location in array
	switch(size) {
		case 1:
		case 2:
			z = list;
			break;
		case 3:
		case 4:
			z = list+1;
			break;
		case 5:
		case 6:
			z = list+2;
			break;
		default:
			z = list+3;
			break;
	}

	//cases
	if(z->head == NULL) {
		z->head = temp;
		z->tail = temp;
	}
	else {
		z->tail->next = temp;
		z->tail = temp;
	}
	printf("Done.\n");
}

void delete() {
	//variable instantiation
	int minSize = 1, count = 0, openingSize, i;
	NODE *p, *q;
	LIST *z = list;
	
	//checking if list is empty
	for(i = 0; i < SIZE; i++, z++) {
		if(z->head != NULL)
			count++;
	}
	if(count == 0) {
		printf("The waiting list is empty.\n");
		return;
	}

	//user input
	printf("Size of opening: ");
	scanf("%d", &openingSize);
	
	//looping until size is below the minimum group size in a given row OR loop reaches the end
	z = list;
	printf("\n\tRemoved Groups:\n");
	while(openingSize >= minSize) {
		p = q = z->head;
		//traversing linked list
		while(p != NULL && p->size > openingSize) {
			q = p;
			p = p->next;
		}

		//cases
		if(p == NULL) {
			if(minSize == 7)
				break;
			z++;
			minSize += 2;
		}
		else if(p == z->head) {
			z->head = z->head->next;
			openingSize = openingSize - p->size;
			printf("\t%s\n", p->name);
		}	
		else if(p == z->tail) {
			q->next = NULL;
			z->tail = q;
			openingSize = openingSize - p->size;
			printf("\t%s\n", p->name);
		}
		else {
			q->next = p->next;
			openingSize = openingSize - p->size;
			printf("\t%s\n", p->name);
		}
		free(p);
	}
	printf("\nOpening size has been minimized and all available parties removed from the list.\n");

}	



void list_groups() {
	//variable instantiation
	int count = 0, range = 1, i;
	LIST *z = list;
	NODE *p = z->head; 

	//checking if list is empty
	for(i = 0; i < SIZE; i++, z++) {
		if(z->head != NULL)
			count++;
	}
	if(count == 0) {
		printf("The waiting list is empty.\n");
		return;
	}
	
	//traversing linked list and printing
	z = list;
	for(i = 0; i < SIZE; i++, z++, range++) {
		printf("\n\t   Range %d\n", range);
		printf("-----------------------------\n");
		printf("Name:\t\t\tSize:\n");
		p = z->head;
		while(p != NULL) {
			printf("%s\t\t\t   %d\n", p->name, p->size);
			p = p->next;
		}
	}
	printf("\n");	
}

void search_size() {
	//variable instantiation
	LIST *z = list;
	NODE *p;
	int count = 0, minSize = 1, size, i;

	//checking if list is empty
	for(i = 0; i < SIZE; i++, z++) {
		if(z->head != NULL)
			count++;
	}
	if(count == 0) {
		printf("The waiting list is empty.\n");
		return;
	}

	//getting user input
	printf("Size: ");
	scanf("%d", &size);
		
	//traversing linked list
	printf("\nAll groups of size %d and lower:\n", size);
	printf("--------------------------------\n");
	printf("Name:\t\t\tSize:\n");
	z = list;
	for(i = 0; i < SIZE; i++, z++, minSize+=2) {
		if(minSize > size)
			break;
		p = z->head;
		while(p != NULL) {
			if(p->size <= size) {
				printf("%s\t\t\t   %d\n", p->name, p->size);
			}
			p = p->next;
		}
	}
	printf("\n");
}

int check_duplicate(char *name) {
	//variable instantiation
	LIST *z = list;
	NODE *p;
	int count = 0, i;

	//traversing linked list
	for(i = 0; i < SIZE; i++, z++) {
		p = z->head;
		while(p != NULL) {
			if(strcmp(p->name, name) == 0)
				count++;
			p = p->next;
		}
	}

	//cases
	if(count > 0)
		return 1;
	else
		return 0;
}

void clear(void) {
	//frees all nodes before program exit
	LIST *z = list;
	NODE *p, *q;
	int i;
	for(i = 0; i < SIZE; i++, z++) {
		p = q = z->head;
		while(p != NULL) {
			p = p->next;
			free(q);
			q = p;
		}
	}
}

void change_size(void) {
	//variable instantiation
	char name[LENGTH];
	int old_size, new_size;
	LIST *z;
	NODE *p, *q;	

	//user input
	printf("Name:\n");
	scanf("%s", name);
	printf("Current size:\n");
	scanf("%d", &old_size);
	printf("New size:\n");
	scanf("%d", &new_size);

	//finding appropriate linked list
	switch(old_size) {
		case 1:
		case 2:
			z = list;		
			break;
		case 3:
		case 4:
			z = list+1;
			break;
		case 5:
		case 6:
			z = list+2;
			break;
		default:
			z = list+3;
			break;
	}
	
	//finding specified party
	q = p = z->head;
	while(p != NULL) {
		if(strcmp(p->name, name) == 0)
			break;
		q = p;
		p = p->next;
	}
	
	//checking existence
	if(p == NULL) {
		printf("The name and size you specified do not match with any existing party in our database.\n");
		return;
	}
	
	//changing size and re-ordering list
	if(p == z->head) {
		z->head = p->next;
	}
	else {
		q->next = p->next;
	}
	p->size = new_size;
	p->next = NULL;	
	
	//finding new list based on new size
	switch(new_size) {
		case 1:
		case 2:
			z = list;
			break;
		case 3:
		case 4:
			z = list+1;
			break;
		case 5:
		case 6:
			z = list+2;
			break;
		default:
			z = list+3;
			break;
	}

	//cases
	if(z->head == NULL) {
		z->head = p;
		z->tail = p;	
	}
	else {
		z->tail->next = p;
		z->tail = p;	
	}
	printf("Done.\n");
}











