#include<iostream>
#include<vector>
#include <sstream>

using namespace std;

struct data{
	int valid_bit;
	int tag;	
};

int main(int argc, char* argv[]){
	printf("Hello! how are you doing?\n");  //i am fine how are you
	
	vector <struct data> cache;
    vector <int> associative_maps;	// what will this be used for 
	
	int block_size;	//number of words in a block
	int num_blocks; //Number of blocks in the cache. 
	int associativity; //(only direct mapped is needed).
	int hit_time; //(in cycles)
	int miss_time;
	int blocks_per_index;
	int hits = 0;
	int misses = 0;
	float hit_rate;
	float miss_rate;
	float AMAT;
	
		if (argc !=6){
		cerr << "usage: a.out block_size num_blocks associativity hit_time miss_time"<< endl;
		cerr << "usage: all arguments are integers"<< endl;
		cerr << "usage: for associativity 1 for direct mapped "<< endl;
		cerr << "usage: for associativity 0 for full associative mapped "<< endl;
		printf("about to exit in disgrace\n");
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
	string address;
	stringstream ss;
	int fin_address;
	while (cin >> address){
		address.erase(0,2); //ignore the 0x
		cout << "the string is " << address << "\n";
		ss << std::hex << address;
		ss >> fin_address;
		ss.clear();
		printf("Address is %d\n", fin_address);
		misses ++; //incrementing the num of misses for every address
	}
	
	hit_rate = hits/(hits + misses);
	miss_rate = misses/(hits + misses);
	AMAT = hit_time + (miss_rate * miss_time);
	cout << "Hit Rate: " << hit_rate
		<< " Miss rate: " << miss_rate
		<< " Average Memory Access Time: " << AMAT << endl;
	
	return 0;
}
