#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <math.h>


int REGISTROS;

struct DogType{
	char name[32];
	char type[32];
	int age;
	char breed[16];
	int height;
	double weight;
	char sex;
	bool deleted;
	int index;
};

int writeRegister(void* ap, int position){
	struct DogType* dato;
	dato = ap;
	FILE* f;

	f = fopen("structures.dat", "ab+");
	int d = fseek(f, position*sizeof(struct DogType), SEEK_SET);
	if(f == NULL){
		perror("Could not open a file");
		exit(-1);
	}
	int r = fwrite(dato, sizeof(struct DogType), 1, f);

	if(r == 0){
		perror("Could not write Struct");
		exit(-1);
	}
	return 0;
}

int findByIndex(struct DogType* ap, int index){
	FILE* f;
	f = fopen("structures.dat", "ab+");

	if(f == NULL){
		perror("Could not open a file");
		exit(-1);
	}
	int d = fseek(f, index*sizeof(struct DogType), SEEK_SET);
	if( d == -1){
		printf("error al mover al index\n");
	}
	int r =  fread(ap, sizeof(struct DogType), 1 , f);
	if (r == 0){
        perror("Could no read structure");
        exit(-1);
    }

	printf("Name Read: %s\n", ap->name);
	return 0;
}

int countRecords(){
	FILE* f;
	f = fopen("structures.dat", "ab+");

	if(f == NULL){
		perror("Could not open a file");
		exit(-1);
	}
    int r;
    r = fseek(f,0*sizeof( struct DogType ), SEEK_SET);
    if(r == -1){
		printf("error al mover al index\n");
    }
    struct DogType perro={ "", "",  0, "", 0, 0.0, 'f', 0, 0 };
    int count =0;
    while(fread(&perro, sizeof(struct DogType), 1, f )!=0){
        count++;
		printf("name %s\n", perro.name);
    }
    return count;
}

struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList *node; //Define node as pointer of data type struct LinkedList

node createNode(){
    node temp;                                      // declare a node
    temp = (node) malloc(sizeof(struct LinkedList)); // allocate memory using malloc()
    temp->next = NULL;                              // make next point to NULL
    return temp;                                    //return the new node
}

node createList(int initialValue){
    node head = createNode();
    head->data = initialValue;
}

void addNode(node head, int value){
    node temp, p;        // declare two nodes temp and p
    temp = createNode(); //createNode will return a new node with data = value and next pointing to NULL.
    temp->data = value;  // add element's value to data part of node

    p = head; //assign head to p
    while (p->next != NULL){
        p = p->next; //traverse the list until p is the last node.The last node always points to NULL.
    }
    p->next = temp; //Point the previous last node to the new node created.
}

unsigned int calculateHash (const char *word) {
    unsigned int hash = 0, c;

    for (size_t i = 0; word[i] != '\0'; i++) {
        c = (unsigned char)word[i];
        hash = (hash << 3) + (hash >> (sizeof(hash) * CHAR_BIT - 3)) + c;
    }
    return hash % SIZE;
}



int main(){

}