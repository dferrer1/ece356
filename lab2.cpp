#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char* argv[]){
	vector <vector>cache;
    vector <int>set;
	int block_size;
	int num_blocks; //Number of blocks in the cache. 
	int associativity; //(only direct mapped is needed).
	int hit_time; //(in cycles)
	int miss_time;
    int blocks_per_index;
	
	if (argc !=6){
		fprintf(stderr,"usage: ./lab2 block_size num_blocks associativity(d or a) hit_time miss_time\n");
		return;
	}else{
		block_size = argv[1];
		num_blocks = argv[2];
		associativity = argv[3];
		hit_time = argv[4];
		miss_time = argv[5];
	} 
	
    blocks_per_index = num_blocks / block_size; // this should be the number of blocks in each set
}
