#include<iostream>
#include<vector>

using namespace std;

int find_block(int address);

int main(int argc, char* argv[]){
	
	int block_size;
	int num_blocks; //Number of blocks in the cache. 
	int associativity; //(only direct mapped is needed).
	int hit_time; //(in cycles)
	int miss_time;
	
	if (argc !=6){
		fprintf(stderr,"usage: ./lab2 block_size num_blocks associativity(d or a) hit_time miss_time\n");
		return;
	}else{
		Block_size = argv[1];
		num_blocks = argv[2];
		associativity = argv[3];
		hit_time = argv[4];
		miss_time = argv[5];
	} 
	
}

int find_block() {
    return -1;
}