#include <pthread.h>
#include <string.h>
#include <stdio.h>

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

struct VCB myVCB;
myVCB.sizeOfBlock = 2048;
myVCB.freeBlocks = 511;
myVCB.numberOfBlocks = 511;
myVCB.bitmap = {0};

struct directory myDirectory;
myDirectory.entries = 0;

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
		if(bitmap[i] == 0){
			//start counting free blocks
			startIndex = i;
			free++;

			//if this set of free blocks is big enough
			if(freeBlocks == size){
				int j;

				//allocate these blocks
				for(j = startIndex; j <= i; j++){
					myVCB.bitmap[j] = 1;
				}

				myDirectory.names[directoryEntries] = name;
				myDirectory.startBlocks[directoryEntries] = startIndex;
				myDirectory.sizes[directoryEntries] = size;
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