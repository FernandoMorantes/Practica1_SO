#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <math.h>
#include <limits.h>

int REGISTROS;
int SIZE = 1999;
int lastHashIndex[2000];

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
	int prevHashIndex;
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

void findByIndex(struct DogType *ap, int index, FILE *f){
	
	struct DogType reg;
	int d = fseek(f, index * sizeof(struct DogType), SEEK_SET);
	if (d == -1){
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
}

int countRecords(){
	FILE *f;
	f = fopen("structures.dat", "ab+");

	if (f == NULL)
	{
		perror("Could not open a file");
		exit(-1);
	}
	int r;
	//r = fseek(f,0*sizeof( struct DogType ), SEEK_SET);
	if (r == -1)
	{
		printf("error al mover al index\n");
	}
	struct DogType perro = {"", "", 0, "", 0, 0.0, 'f', 0, 0};
	int count = 0;
	while (fread(&perro, sizeof(struct DogType), 1, f) != 0)
	{
		count++;
	}
	fclose(f);
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

void writeHash(){
	int status = remove("hash.dat");
	if (status == 0)
	{
		printf("Hash file deleted\n");
	}

	FILE *f;
	f = fopen("hash.dat", "ab+");

	if (f == NULL)
	{
		perror("Could not open file");
		exit(-1);
	}

	int r = fwrite(lastHashIndex, sizeof(lastHashIndex), 1, f);

	if (r == 0)
	{
		perror("Could not write Struct");
		exit(-1);
	}
	fclose(f);
}

void readHash(){

	FILE *f;
	f = fopen("hash.dat", "rb");
	int d = fseek(f, 0 * sizeof(struct DogType), SEEK_SET);
	if (d == -1)
	{
		printf("error al mover al index\n");
	}
	int test[2000];

	if (f == NULL)
	{
		perror("Could not open file");
		exit(-1);
	}

	int r = fread(test, sizeof(test), 1, f);

	if (r == 0)
	{
		perror("Could not read Struct hash");
		exit(-1);
	}

	for (int i = 0; i < 2000; i++){
		lastHashIndex[i] = test[i];
		printf(" %d", test[i]);
	}

	fclose(f);
}

int main(){

	//readHash();

	FILE *f;
	f = fopen("structures.dat", "rb+");

	if (f == NULL){
		perror("Could not open a file");
		exit(-1);
	}

	struct DogType test;

	findByIndex(&test, 9000, f);

	printf("\n\ntest ->");
	printf("\nname: %s\n", test.name);
	printf("type: %s\n", test.type);
	printf("age: %d\n", test.age);
	printf("breed: %s\n", test.breed);
	printf("height: %d\n", test.height);
	printf("weight: %.2lf\n", test.weight);
	printf("sex: %c\n", test.sex);
	printf("index: %d\n", test.index);
	printf("prev hash index: %d\n\n", test.prevHashIndex);

	findByIndex(&test, 8000, f);

	printf("\n\ntest ->");
	printf("\nname: %s\n", test.name);
	printf("type: %s\n", test.type);
	printf("age: %d\n", test.age);
	printf("breed: %s\n", test.breed);
	printf("height: %d\n", test.height);
	printf("weight: %.2lf\n", test.weight);
	printf("sex: %c\n", test.sex);
	printf("index: %d\n", test.index);
	printf("prev hash index: %d\n\n", test.prevHashIndex);

	printf("\nHay %d registros\n", countRecords());

	fclose(f);
	return 0;
}