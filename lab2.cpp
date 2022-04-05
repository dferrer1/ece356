#include<iostream>
#include<vector>
#include <sstream>
#include <math.h>
using namespace std;

struct data{
	int valid_bit;
	int tag;	
};

// generate index mask
int gen_index_mask(int index_size, int offset_size = 0);
int gen_tag_mask(int tag_size, int index_size, int offset_size = 0);

int main(int argc, char* argv[]){
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
	cache.resize(num_blocks);
	//initialize the cache
	for (int i = 0; i < num_blocks;i++){
		cache.at(i).tag = 0;
		cache.at(i).valid_bit = 0;
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
		printf("the index is %d and the tag is %d\n", index, tag);
		if (cache.at(index).valid_bit == 1){
			if(cache.at(index).tag == tag){
				printf("hit\n");
				hits++;
			}
			else{
				cache.at(index).tag = tag;
				printf("miss\n");
				misses++;
			}
		}
		else{
			cache.at(index).valid_bit = 1;
			cache.at(index).tag = tag;
			misses++;
			printf("miss\n");
		}
	}
	printf("%d hits, %d misses\n",hits,misses);
	hit_rate = (float) hits/(hits + misses);
	miss_rate = (float) misses/(hits + misses);
	AMAT = hit_time + (miss_rate * miss_time);
	cout << "Hit Rate: " << hit_rate
		<< " Miss rate: " << miss_rate
		<< " Average Memory Access Time: " << AMAT << endl;
	gen_index_mask(5);
	gen_index_mask(5, 2);

	gen_tag_mask(4, 4);
	gen_tag_mask(4, 4, 4);

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
	//printf("Returned mask: 0x%x\n", mask);
	
	return mask;
}


int gen_tag_mask(int tag_size, int index_size, int offset_size) {
	int mask = 0;

    //
    for (int i = 0; i < (tag_size+index_size+offset_size); i++) {
        // ignore offset bits
        if (i >= index_size+offset_size && i > 1) {
            mask += (1<<i);
        } else if (i >= index_size+offset_size && i == 0) {
            mask += 1;
        } else if (i >= index_size+offset_size && i == 1) {
            mask += 2;
        }
    }
    //printf("Returned mask: 0x%x\n", mask);


	return mask;
}
