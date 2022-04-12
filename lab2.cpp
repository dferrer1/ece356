#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct data{
	int valid_bit;
	int tag;	
};

// generate index mask
int gen_index_mask(int index_size, int offset_size = 0);

int main(int argc, char* argv[]){
	vector <vector<struct data>> cache;	
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
	//seed the random generator
	srand(time(NULL));

	if (argc !=6){
		cerr << "usage: a.out block_size num_blocks associativity hit_time miss_time"<< endl;
		cerr << "usage: all arguments are integers"<< endl;
		cerr << "usage: for associativity 1 for direct mapped "<< endl;
		cerr << "usage: for associativity n for n way associativity "<< endl;
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
	cache.resize(num_blocks/associativity);
	//initialize the cache
	for (int i = 0; i < num_blocks/associativity;i++){
		cache.at(i).resize(associativity);
		for (int j = 0; j < associativity; j++){
			cache[i][j].tag = 0;
			cache[i][j].valid_bit = 0;
		}
	}
	string address;
	stringstream ss;
	int fin_address;
	//try to generate the bitmasks
	int total_address_mask = 0;
	int block_offset_upperbound = 0;
	int index_offset_upperbound = 0;
	for (int i = 0; i < 20; i++){
		total_address_mask |= (1 << i);
	}
	
	//calculate the block offset and mark the upperbound
	printf("calculating the log base 2 of %d\n",block_size);
	block_offset_upperbound = log2(block_size)/log2(2);
	index_offset_upperbound = (log2(num_blocks)/log2(2)) + block_offset_upperbound;
	printf("the block upperbound is %d, the index upperbound is %d\n", block_offset_upperbound, index_offset_upperbound);

	//for now, read in one address and process it
	while (cin >> address){
		//ignore the 0x
		address.erase(0,2);
		//cout << "the string is " << address << "\n";
		ss << std::hex << address;
		ss >> fin_address;
		ss.clear();
		//extract the mask
		//printf("calling with params %d and %d\n",block_offset_upperbound,index_offset_upperbound-block_offset_upperbound);
		int index_extraction = gen_index_mask(index_offset_upperbound-block_offset_upperbound,block_offset_upperbound);
		int tag_extraction = gen_index_mask(20-index_offset_upperbound,index_offset_upperbound);
		//pull out the index and tag and shift the index right so that the lowest bit is 2^0, not whatever it was
		//printf("The index bitmask is %d and the tag bitmask is %d\n",index_extraction,tag_extraction);
		int index = fin_address & index_extraction;
		index = index >> block_offset_upperbound;
		int tag = fin_address & tag_extraction;
		tag = tag >> index_offset_upperbound;
		//the index needs to be divided by the associativity
		index = index / associativity;
		printf("the index is %d and the tag is %d\n", index, tag);

		int cur_miss = 1;
		for (int i = 0; i < associativity; i++){
			if (cache[index][i].valid_bit == 1){
				if(cache[index][i].tag == tag){
					hits++;
					cur_miss = 0;
				}
			}
		}
		//if there was a miss, find a spot to insert
		if(cur_miss == 1){
			misses++;
			//flag to check if a random insertion is needed
			int rand_flag = 1;
			//check to see if any of them are empty
			for (int i = 0; i < associativity; i++){
				if(cache[index][i].valid_bit == 0){
					cache[index][i].valid_bit = 1;
					cache[index][i].tag = tag;
					rand_flag = 0;
					break;
				}
			}
			if (rand_flag){
				int insertion_index = rand() % associativity;
				printf("inserting randomly; index %d of set %d\n",index,insertion_index);
				cache[index][insertion_index].valid_bit = 1;
				cache[index][insertion_index].tag = tag;
			}
		}
	}
	
	printf("%d hits, %d misses\n",hits,misses);
	hit_rate = (float) hits/(hits + misses);
	miss_rate = (float) misses/(hits + misses);
	AMAT = hit_time + (miss_rate * miss_time);
	cout << "Hit Rate: " << hit_rate
		<< " Miss rate: " << miss_rate
		<< " Average Memory Access Time: " << AMAT << endl;
	return 0;
}

// generate index mask: this function should generate a decimal value that can be used as a mask for finding the value of the index
int gen_index_mask(int index_size, int offset_size) {
	int mask = 0;
	// 
	for (int i = 0; i < (index_size+offset_size); i++) {
		// ignore offset bits
		if (i >= offset_size && i > 1) {
			mask += (1<<i);
		} else if (i >= offset_size && i == 0) {
			mask += 1;
		} else if (i >= offset_size && i == 1) {
			mask += 2;
		}
	}
	return mask;
}
