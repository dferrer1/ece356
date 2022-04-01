#include<iostream>
#include<vector>

using namespace std;

struct data{
	int valid_bit;
	int tag;	
}

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
		if (argc !=6){
		cerr << "usage: a.out block_size num_blocks associativity hit_time miss_time"<< endl;
		cerr << "usage: all arguments are integers"<< endl;
		cerr << "usage: for associativity 1 for direct mapped "<< endl;
		cerr << "usage: for associativity 0 for full associative mapped "<< endl;
		return;
	}else{
		block_size = argv[1];
		num_blocks = argv[2];
		associativity = argv[3];
		hit_time = argv[4];
		miss_time = argv[5];
	} 
	vector <vector <data> > cache;
		
		
    blocks_per_index = num_blocks / block_size; // this should be the number of blocks in each set
}
