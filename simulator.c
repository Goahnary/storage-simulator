#include<pthread.h>
#include<stdio.h>

FILE disk = fopen("storage","r+");
int sizeOfBlock = 2000;
int numberOfBlocks = 512;
int freeBlocks = 512;
bool[512] bitmap = {false};
char[512][3][] directory;
int directory

int main(int argc, char *argv[]){
	
}

void open(char[] fileName){

}

void create(int size){
	int freeBlocks = 0;
	int startIndex = -1;

	//check every block
	for(int i = 0; i < bitmap.length; i++){
		
		//if this block is free
		if(!bitmap[i]){
			//start counting free blocks
			startIndex = i;
			freeBlocks++;

			//if this set of free blocks is big enough
			if(freeBlocks == size){
				//allocate these blocks
				for(int j = startBlock; j <= i; j++){
					bitmap[j] = true;
				}

				
			}
		}
		
		else {
			startIndex = -1;
			freeBlocks = 0;
		}
	}
}
