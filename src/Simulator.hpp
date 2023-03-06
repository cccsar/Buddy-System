#include<vector> 
#include<map> 
#include<set> 
#include<string> 
#include<utility>

#include "Core.hpp"

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#define ERR_NAME -1
#define ERR_SIZE -2
#define ERR_MINSIZE -3
#define ERR_INVLABEL -4

/// @brief Class representing the memory simulator
class Simulator 
{ 

public:

	/// @brief Memory map
	std::vector<bool> mem; 
	
	/// @brief Map from names to memory positions and sizes  
	std::map < std::string, std::pair<int, int> > names; 

	/// @brief Set of initial positions of each block with occupied memory.
	/// It is used to avoid linear search while searching for free memory.
	std::set< int > bounds; 

	/// @brief A map to keep track of free memory blocks
	std::map<int, int> free_mem; 

	/// @brief Total size of memory 
	int size; 

	/// @brief Uninitialized simulator. Could be better
	Simulator() ; 
	/// @brief Always receive the amount of memory to simulate 
	Simulator( int mmax ) ;  


	/// @brief Checks if insertion is valid: 
	/// There are no names asociated already with passed name.
	///	There is enough memory.
	/// And proceeds to "allocate".
	int insert (std::string name, int request);


	/// @brief Checks if deletion is valid (there is an existing name with
	/// an associated block of memory), and proceeds to "de-allocate".
	STATUS erase(std::string name); 

	
	/// @brief Shows the current memory layout 
	STATUS display_memory();


private : 

	/// @brief Performs memory allocation 
	void reserve(std::string name, int request ,int ind) ; 

	/// @brief Given a index, a size and an element, fill said size from said index 
	/// memory position with given element 
	void fill_segment ( int ind, int ub , int el) ; 

	/// @brief Returns best fit size ( upper bound for a power of 2 ) of a given amount of 
	/// memory in request
	int best_fit_size (int el ) const; 

	/// @brief Returns either the index for the next memory allocation to carry out, or -1 
	/// if not possible
	int find_best_fit(int request); 


	/// @brief Returns the position of the buddy block for a given position and size, and 
	/// a boolean that tells whether it is the left buddy for the given block 
	/// (true) or the right one.
	std::pair<bool, int> buddy (int pos, int size); 

	/// @brief Procedure to create free blocks from a given position and size 
	void create_blocks(int pos, int sz, bool tp); 

	/// @brief Procedure to merge free memory blocks after the deletion of an identifier
	/// And subsequence freeing of memory 
	void merge_blocks(int pos, int size); 

}; 

#endif
