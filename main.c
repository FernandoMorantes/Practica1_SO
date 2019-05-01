#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <math.h>

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

char types[2][32] = {"Dog", "Cat"};
char sexes[2] = {'M', 'F'};

void generateDogRegister (struct DogType *);
void getRegName (struct DogType *);
void getRegBreed (struct DogType *, char);

void getRegName(struct DogType *sample){
	
	FILE *file;
    char line[256];
    char* filename = "names.txt";
 
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Could not open file %s",filename);
    }
    
    int i = 0;
    int nameNumber = rand() % 1417 + 1;
    
    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i == nameNumber){
        	strtok(line, "\n");
        	strcpy(sample->name, line);
        	break;
		}   
    }
    
    fclose(file);
}

void getRegBreed(struct DogType *sample, char type){
	
	FILE *file;
    char line[256];
    char* filename;
    int breedNumber;
    
    if(type == 'D'){
    	filename = "dogBreeds.txt";
    	breedNumber = rand() % 89 + 1;
	}else{
		filename = "catBreeds.txt";
		breedNumber = rand() % 58 + 1;
	}
    
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Could not open file %s",filename);
    }
    
    int i = 0;
    
    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i == breedNumber){
        	strtok(line, "\n");
        	strcpy(sample->breed, line);
        	break;
		}   
    }
    
    fclose(file);
}

void generateRegister(struct DogType *sample){
	
	
	
	int typeNumber = rand() % 2 + 1;
	int ageNumber = rand() % 19;
	int heightNumber = rand() % 120 + 20;
	
	double weightNumber;
	if(typeNumber == 1){
		weightNumber = 4.0 + ((double)rand() / RAND_MAX)*(60.0-4.0);
	}else{
		weightNumber = 3.5 + ((double)rand() / RAND_MAX)*(19.0-3.5);
	}

	int sexNumber = rand() % 2 + 1;
	
	getRegName(sample);
	strcpy(sample->type, types[typeNumber-1]);
	sample->age = ageNumber;
	
	if(typeNumber == 1){
		getRegBreed(sample, 'D');
	}else{
		getRegBreed(sample, 'C');
	}
	
	sample->height = heightNumber;
	sample->weight = roundf(weightNumber * 100) / 100;;
	sample->sex = sexes[sexNumber-1];
	sample->deleted = false;
	sample->index = 1;	//Aqui pues coloca un autoincremental
}

int writeRegister(void* ap, int position){
	struct DogType* dato;
	dato = ap;
	FILE* f;
	f = fopen("structures.dat", "ab+");

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

///
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
	

int registros;
int main(int argc, char *argv[]) {
	srand(time(NULL));
	struct DogType* sampleRead;
	sampleRead = malloc(sizeof(struct DogType));
	struct DogType test = { "", "",  0, ' ', 0, 0.0, ' ', 0, 0 };
	
	registros = countRecords();
	printf("Hay %d registros\n", registros);
	int find = findByIndex( &test, 15);
	
	
	for(int i = 0; i < 5; i++){
		registros = countRecords();
		struct DogType sample;
		generateRegister(&sample);
		int write = writeRegister(&sample, registros); 
	}
	registros = countRecords();
	printf("Ahora hay %d registros\n", registros);
	find = findByIndex( &test, 15);
	free(sampleRead);
	/*
	para crear registros nuevos borrar archivo, cambiar rb+ a ab+ en fopen
	for(int i = 0; i < 20; i++){
		struct DogType sample;
		generateRegister(&sample);
		int write = writeRegister(&sample, f); 
	}
	*/
	return 0;
}
