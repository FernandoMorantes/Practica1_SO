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
	
	srand(time(NULL));
	
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
	


int main(int argc, char *argv[]) {
	
	struct DogType sample;
	generateRegister(&sample);
	
	printf( "Sample name : %s\n", sample.name);
	printf( "Sample type : %s\n", sample.type);
	printf( "Sample age : %d\n", sample.age);
	printf( "Sample breed : %s\n", sample.breed);
	printf( "Sample height : %d\n", sample.height);
	printf( "Sample weight : %.2lf\n", sample.weight);
	printf( "Sample sex : %c\n", sample.sex);
	printf( "Sample deleted : %d\n", sample.deleted);
	printf( "Sample index : %d\n", sample.index);
	
	
	return 0;
}
