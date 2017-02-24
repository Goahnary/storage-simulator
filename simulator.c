#include<pthread.h>
#include<stdio.h>

//volume control block
struct VCB{
	int sizeOfBlock = 2048;
	int numberOfBlocks = 512;
	int freeBlocks = 512;
	int bitmap[511] = {0};
};

//directory
struct directory {
	char *names[511];
	int startBlocks[511];
	int sizes[511];
	int entries = 0;
}

struct FCB {
	int size;
	int firstBlock;
}

struct OFT {
	char name[255];
	int firstBlock;
}

struct POFT {
	char name[];
	int handle;
}

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
	for(i = 0; i < sizeof(VCB.bitmap) / sizeof(VCB.bitmap[0]); i++){
		
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
					VCB.bitmap[j] = 1;
				}

				directory.names[directoryEntries] = name;
				directory.startBlocks[directoryEntries] = startIndex;
				directory.sizes[directoryEntries] = size;
				directory.entries++;
			
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