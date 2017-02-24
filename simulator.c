#include<pthread.h>
#include<stdio.h>

//volume control block
int sizeOfBlock = 2048;
int numberOfBlocks = 512;
int freeBlocks = 512;
int bitmap[511] = {0};


//directory
char *directoryNames[511];
int directoryStarts[511];
int directorySizes[511];
int directoryEntries = 0;

void open(char fileName[]){

}

void close(){

}

void write(){

}

void create(int size, char *name){
	int freeBlocks = 0;
	int startIndex = -1;
	int created = 0;
	int i;

	//check every block
	for(i = 0; i < sizeof(bitmap) / sizeof(bitmap[0]); i++){
		
		//if this block is free
		if(bitmap[i] == 0){
			//start counting free blocks
			startIndex = i;
			freeBlocks++;

			//if this set of free blocks is big enough
			if(freeBlocks == size){
				int j;

				//allocate these blocks
				for(j = startIndex; j <= i; j++){
					bitmap[j] = 1;
				}

				directoryNames[directoryEntries] = name;
				directoryStarts[directoryEntries] = startIndex;
				directorySizes[directoryEntries] = size;
				directoryEntries++;
			
				created = 1;
				freeBlocks -= size;
			}
		}
		
		else {
			startIndex = -1;
			freeBlocks = 0;
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