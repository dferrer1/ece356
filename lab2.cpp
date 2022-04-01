#include<stdlib.h>
#include<vector>

using namespace std;

int main(int argc, char* argv[]){
	
	int block_size;
	int num_blocks; //Number of blocks in the cache. 
	int associativity; //(only direct mapped is needed).
	int hit_time; //(in cycles)
	int miss_time;
	
	if (argc !=5){
		
	}else{
		Block_size = argv[0];
		num_blocks = argv[1];
		associativity = argv[2];
		hit_time = argv[3];
		miss_time = argv[4];
	} 
	
}
