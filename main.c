#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <math.h>


int REGISTROS;
int SIZE = 1010;

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

int writeRegister(void *ap, int position){
	
	struct DogType *dato;
	dato = ap;
	FILE *f;

	f = fopen("structures.dat", "ab+");
	int d = fseek(f, position * sizeof(struct DogType), SEEK_SET);
	if (f == NULL)
	{
		perror("Could not open a file");
		exit(-1);
	}
	int r = fwrite(dato, sizeof(struct DogType), 1, f);

	if (r == 0)
	{
		perror("Could not write Struct");
		exit(-1);
	}
	fclose(f);
	return 0;
}

void findByIndex(struct DogType *ap, int index){
	FILE *f;

	struct DogType reg;
	f = fopen("structures.dat", "rb+");

	if (f == NULL)
	{
		perror("Could not open a file");
		exit(-1);
	}
	int d = fseek(f, index * sizeof(struct DogType), SEEK_SET);
	if (d == -1)
	{
		printf("error al mover al index\n");
	}
	int r = fread(&reg, sizeof(struct DogType), 1, f);
	if (r == 0)
	{
		perror("Could no read structure");
		exit(-1);
	}

	strcpy(ap->name, reg.name);
	strcpy(ap->type, reg.type);
	ap->age = reg.age;
	strcpy(ap->breed, reg.breed);
	ap->height = reg.height;
	ap->weight = reg.weight;
	ap->sex = reg.sex;
	ap->deleted = reg.deleted;
	ap->index = reg.index;
	ap->prevHashIndex = reg.prevHashIndex;

	fclose(f);
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