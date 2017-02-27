#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//volume control block
struct VCB{
	int sizeOfBlock;
	int numberOfBlocks;
	int freeBlocks;
	int bitmap[511];
};

//directory
struct directory {
	char *names[511];
	int startBlocks[511];
	int sizes[511];
	int entries;
};

//File Control Block
struct FCB {
	int size;
	int firstBlock;
};

//defining a tuple to help keeping track of files in the OFT
struct oftTuple {
	char fname[255];
	struct FCB fcb;
};

//Open File Table
struct OFT {
	struct oftTuple blocks[511];
	int entries;
};

//Per-process Open File Table
struct POFT {
	struct FCB blocks[511];
	int handles[511];
};

//Creating the volume conrol block for our file system(FS)
struct VCB myVCB = {
	.sizeOfBlock = 2048,
	.freeBlocks = 511,
	.numberOfBlocks = 511,
	.bitmap = {0}
};

//creating directory for our FS
struct directory myDirectory = {
	.entries = 0
};

//Creating the Open File Table for our FS
struct OFT myOFT = {
	.entries = 0
};


//Opens files for reading
void open(char *fileName){
	int i;

	//seach the directory for the file
	for(i = 0; i < myDirectory.entries; i++){
		if(strcmp(myDirectory.names[i], fileName) != 0){
			break;
		}
	}

	struct FCB newFCB = {
		.size = myDirectory.sizes[i],
		.firstBlock = myDirectory.startBlocks[i]
	};

	struct oftTuple tuple = {
		.fcb = newFCB,
		.fname = fileName
	};

	myOFT.blocks[myOFT.entries] = tuple;
	myOFT.entries++;
}

//Closes Files
void close(){

}

//Writes to files
void write(){

}

//Creates files
void create(int size, char *name){
	int free = 0;
	int startIndex = -1;
	int created = 0;
	int i;
	//check every block
	for(i = 0; i < sizeof(myVCB.bitmap) / sizeof(myVCB.bitmap[0]); i++){
		//if this block is free
		if(myVCB.bitmap[i] == 0){
			//start counting free blocks
			startIndex = i;
			free++;

			//if this set of free blocks is big enough
			if(free == size){
				int j;

				//allocate these blocks
				for(j = startIndex; j <= i; j++){
					myVCB.bitmap[j] = 1;
				}

				myDirectory.names[myDirectory.entries] = name;
				myDirectory.startBlocks[myDirectory.entries] = startIndex;
				myDirectory.sizes[myDirectory.entries] = size;
				myDirectory.entries++;
			
				created = 1;
				free -= size;
			}
		}
		
		else {
			startIndex = -1;
			free = 0;
		}
	}

	if(created == 1){
		printf("%s", "File Created!\n");
	} else {
		printf("%s", "There is not enough free space to create this file.");
	}
}

//List files in FS
//	This method will check the open file table (OFT) 
//	and use it to print all the names of files in the 
//	directory
void dir(){
	
}


//Method to check if there is enough free space
//	returns:
//		true if there is space
//		false if there is not enough space
int isFreeSpace(int blocksNeeded){
	
}

int main(int argc, char *argv[]){
	
	int quit = 0;
	
	while(!quit){
		printf("\n");
		printf("Hello! What would you like to do?\n");
		printf("	1) Create File\n");
		printf("	2) Open File\n");
		printf("	3) Close File\n");
		printf("	4) Read File\n");
		printf("	5) Write File\n");
		printf("	6) Quit\n");
		
		
		int * choice;
		scanf("%d", choice);
		
		
		switch(*choice){
			
			char * fname;

			case 1:
				printf("What is the name of your file?\n");
				scanf("%s", fname);
				printf("What is the size of the file?\n");
				int * fsize;
				scanf("%d", fsize);
				create(*fsize,fname);
				break;
			case 2:
                                printf("What is the name of your file?\n");
				scanf("%s", fname);
                                //open(fname);
                                break;
			case 3:
                                printf("What is the name of your file?\n");
				scanf("%s", fname);
                                //close(fname);
                                break;
			case 4:
                                printf("What is the name of your file?\n");
				scanf("%s", fname);
                                //read(fname);
                                break;
			case 5:
                                printf("What is the name of your file?\n");
				scanf("%s", fname);
                                //write(fname);
                                break;
			case 6:
				quit = 1;
				break;
		}
	}
}

