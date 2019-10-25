/*
Part A - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
	int i = 0;
	int block_size = 0;
	access_cache(0); //access first address so its not cold anymore
	while (access_cache(i)){
		//while access hit
		i++; //iterate to the next address
	}
	block_size = i; //size is the number of hits from the loop
	return block_size; //return
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
	int cache_size = 0;
	int i = block_size; 
	flush_cache(); //starte with a fresh empty cache
	access_cache(0); //avoid cold cache miss
	while (access_cache(0)){
		//while it hits
		cache_size = block_size; //cache size = the size of the block
		while (cache_size <= i){
			//while the cache is less than or equal to the block 
			cache_size += block_size; //add the block size to the result
			access_cache(cache_size); //access the cache at the new size
		}
		i += block_size; // add block size to the iterator
	}
	return cache_size; //return
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
	int cache_assoc = 0;
	int size = 1;
	int i = 0;
	flush_cache(); //start with fresh cache
	access_cache(0); //warm it up
	while (access_cache(0)){
		//while it hits
		i = cache_size; //first index = size of the cache
		cache_assoc = 0; //start with no associativity
		while (i <= size){
			//while the first index is less than or equal to size
			i += cache_size; 
			cache_assoc++;
			access_cache(i);
		}
		size += cache_size;
	}
	return cache_assoc;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
