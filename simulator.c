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
	char *fname;
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
	.sizeOfBlock = 548,
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

//this is the actual content of the files
char blockContent[511][2000];

//Opens files for reading
void open(char *fileName, struct OFT pOFT, int thread){
	int i;

	//seach the directory for the file
	for(i = 0; i < myDirectory.entries; i++){
		if(strcmp(myDirectory.names[i], fileName) == 0){
			break;
		}
	}

	//create an fcb 
	struct FCB newFCB = {
		.size = myDirectory.sizes[i],
		.firstBlock = myDirectory.startBlocks[i]
	};

	//create a tuple for the oft
	struct oftTuple tuple = {
		.fcb = newFCB,
		.fname = fileName
	};

	myOFT.blocks[myOFT.entries] = tuple;
	myOFT.entries++;

	//per process
	if(thread == 1){
 		//search all entries of the process OFT
 		for(i = 0; i < pOFT.entries; i++){
 
 			//if the file names match, remove from myOFT
 			if(strcmp(pOFT.blocks[i].fname, fileName) == 0){
 				pOFT.blocks[i] = tuple;
 				pOFT.entries++;
 				break;
 			}
 		}
 	}
}

//Closes Files
void close(char *fileName, struct OFT pOFT, int thread){
	int i;

	//search all entries of myOFT
	for(i = 0; i < myOFT.entries; i++){

		//if the file names match, remove from myOFT
		if(strcmp(myOFT.blocks[i].fname, fileName) == 0){
			struct oftTuple t;
			myOFT.blocks[i] = t;
			myOFT.entries--;
			break;
		}
	}

	//per process
	if(thread == 1){
 		//search all entries of the process OFT
 		for(i = 0; i < pOFT.entries; i++){
 
 			//if the file names match, remove from myOFT
 			if(strcmp(pOFT.blocks[i].fname, fileName) == 0){
 				struct oftTuple pt;
 				pOFT.blocks[i] = pt;
 				pOFT.entries--;
 				break;
 			}
 		}
 	}
}

//Writes to files
void write(char *fileName, char *content){
	int i;

	//search myOFT to find index of filename
	for(i = 0; i < myOFT.entries; i++){
		if(strcmp(myOFT.blocks[i].fname, fileName) == 0){
			break;
		}
	}

	int size = myOFT.blocks[i].fcb.size;
	int firstBlock = myOFT.blocks[i].fcb.firstBlock;
	int currentBlock = myOFT.blocks[i].fcb.firstBlock;

	//while the string is not null, write 2000 characters to the block and increment the block index
	while(strcmp(content, "\0") != 0 && size+firstBlock > currentBlock){
		strncpy(blockContent[currentBlock], content, 2000);
		currentBlock++;

		//if length of content < 2000, all content is written
		if(strlen(content) < 2000){
			break;
		} else {
			//remove first 2000 chars from content
			char *temp = strdup(content + 2000);
			content = temp;
		}
	}
}

void read(char *fileName){
	int i;

	//search myOFT to find index of filename
	for(i = 0; i < myOFT.entries; i++){
		if(strcmp(myOFT.blocks[i].fname, fileName) == 0){
			break;
		}
	}

	//don't read if file not found
	if(i == myOFT.entries){
		return;
	}

	else{
		//create char array and allocate memory needed
		char content[2000*myOFT.blocks[i].fcb.size];
		memset(content, 0, 2000*myOFT.blocks[i].fcb.size);
		
		int j;

		//concatenate each bloack to the string
		for(j = myOFT.blocks[i].fcb.firstBlock; j < myOFT.blocks[i].fcb.size; j++){
			strcat(content, blockContent[j]);
		}

		//print
		printf(content);
		printf("\n");
	}
}

//Creates files
void create(int size, char *name){
	int free = 0;	//the number of free blocks found in a row
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

				//updated directory
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

//the thread 1 function
void *thread1(void* params){
 	struct OFT oft = {.entries = 0};
 
 	create(2, "file1");
 	open("file1", oft, 1);
 	write("file1", "This is a test of the write and read functions of the simulator.");
	 close("file1", oft, 1);

 	create(1, "file2");
 	open("file2", oft, 1);
 	write("file2", "A second test.");
 	close("file2", oft, 1);
 
 	pthread_exit(0);
 }
 
 //the thread 2 function
 void *thread2(void* params){
 	struct OFT oft = {.entries = 0};
 
 	open("file1", oft, 1);
 	read("file1");
 	close("file1", oft, 1);
 
 	pthread_exit(0);
 }
 
 //the thread 3 function
 void *thread3(void* params){
 	struct OFT oft = {.entries = 0};

 	open("file2", oft, 1);
 	read("file2");
 	close("file2", oft, 1);
 
 	pthread_exit(0);
 }
 
 //this method runs the simulation of the file system with several threads
 void simulate(){
 
 	pthread_attr_t attr; /* set of thread attributes */
 	pthread_t tid1; /* the thread identifier */
 	pthread_t tid2; /* the thread identifier */
 	pthread_t tid3; /* the thread identifier */
 
 	/* get default attribute */
 	pthread_attr_init(&attr);
 
 	/*create the intitial thread */
 	pthread_create(&tid1, &attr, thread1, NULL);
 	pthread_join(tid1, NULL);
 
 	//create the next two threads
 	pthread_create(&tid2, &attr, thread2, NULL);
 	pthread_create(&tid3, &attr, thread3, NULL);
 
 	pthread_join(tid2, NULL);
 	pthread_join(tid3, NULL);
 }

int main(int argc, char *argv[]){
	simulate();
}