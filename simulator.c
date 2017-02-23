#include<pthread.h>
#include<stdio.h>

int sizeOfBlock = 2000;
int numberOfBlocks = 512;
int freeBlocks = 512;
int bitmap[512] = {0};
char directoryNames[512][255];
int directoryStarts[512];
int directorySizes[512];
int directoryEntries = 0;

int main(int argc, char *argv[]){
	
}

void open(char fileName[]){

}

void create(int size, char name[]){
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
