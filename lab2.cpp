#include<iostream>
#include<vector>

using namespace std;

struct data{
	int valid_bit;
	int tag;	
};

int main(int argc, char* argv[]){
	printf("Hello!\n");
	vector <struct data> cache;
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
		return 1;
	}else{
		block_size = atoi(argv[1]);
		num_blocks = atoi(argv[2]);
		associativity = atoi(argv[3]);
		hit_time = atoi(argv[4]);
		miss_time = atoi(argv[5]);
	} 
			
    int total_num_index = num_blocks / block_size; // this should be the number of sets in the cache
	cache.resize(blocks_per_index);
<<<<<<< HEAD
	string address;
	int hits = 0, misses = 0;
	while (cin >> address){
		//ignore the 0x
		address.erase(0,2);
		int fin_address = stoi(address);
		printf("the int is %d\n", fin_address);
	}
	}
}
=======
}
>>>>>>> 6962b5342fc4e1f767725ac2d13ed9d4ef112e5a
