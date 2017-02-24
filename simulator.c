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

struct FCB {
	char name[255];
	int size;
	int firstBlock;
};

struct OFT {
	struct FCB blocks[511];
};

struct POFT {
	struct FCB blocks[511];
	int handles[511];
};

struct VCB myVCB = {
	.sizeOfBlock = 2048,
	.freeBlocks = 511,
	.numberOfBlocks = 511,
	.bitmap = {0}
};

struct directory myDirectory = {
	.entries = 0
};

struct OFT myOFT;

void open(char fileName[]){

}

void close(){

}

void write(){

}

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

int main(int argc, char *argv[]){

	create(3,"file1");
}