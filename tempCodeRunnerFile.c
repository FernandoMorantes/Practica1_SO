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