#include <iostream> 

#include "Simulator.hpp"

Simulator::Simulator()
{
	mem.resize(1);	
}

Simulator::Simulator( int mmax ) 
{  
	mem.resize( mmax ) ; 
	std::fill(mem.begin(), mem.end(), true);

	size = mmax; 

	create_blocks(0, size, true); // create free memory blocks
}


void Simulator::fill_segment ( int ind, int ub , int el) 
{
	std::fill(mem.begin() + ind, mem.begin() + ub, el);
}


int Simulator::best_fit_size (int el) const 
{ 
	int cnt , chk;

	cnt = chk = 0 ;

	// find index of highest order bit to compute roof of logarithm 
	while ( el != 0 )  
	{
		if ( (el & 1) == 1 ) 
			chk +=1 ;
		el >>= 1; 
		cnt +=1; 
	}
		
	if (chk == 1 ) 
		return 1<<(cnt-1); 
 	return 1<<cnt;  
} 


void Simulator::reserve( std::string name, int request, int ind) 
{ 
	int sz = best_fit_size( request ) ; 
	int n_sz = free_mem[ind] - sz ; 

	// Update memory state
	fill_segment(ind, ind+sz, false); 

	// Update mapping with name, start position and size
	names[name] = { ind, request } ; 

	// Insert lower bound for further checking
	bounds.insert( ind ) ; 

	// Update state of free blocks
	free_mem.erase( ind ) ; 
	create_blocks( ind + sz, n_sz, false);  
}


int Simulator::find_best_fit(int request) 
{ 
	int step = best_fit_size (request) ; 
	int i; 
	
	/* For each multiple of best fit within mmax constraint, check with *bounds* set that
	 * there's available space for allocation. If so, return index. 
	 */
	for (i=0; i<size; i+= step ) 
	{ 
		auto it = bounds.upper_bound(i); 

		if ( mem[i] && (it == bounds.end() || *it > i + request - 1) 
			&& i + request - 1 < size )
			return i ; 
	} 

	return -1; 
}


STATUS Simulator::insert ( std::string name, int request)
{ 
	int fit; 

	if (request <= 0) 
		return ERR_MINSIZE; 

	if (names.count(name) > 0) 
		return ERR_NAME; 

	fit = find_best_fit(request); 

	if (fit != -1)  
	{ 
		reserve(name, request, fit) ;

		return SUCCESS; 
	}

	return ERR_SIZE; 
}


STATUS Simulator::display_memory() 
{ 

	std::cout<<"\nEstado de la memoria:\n"; 

	for(auto el : mem) 
	{
		std::cout<<el;
	}
	std::cout<<'\n';

	if ( names.size() > 0)  
	{
		std::cout<<"\nEtiquetas:\n"; 

		for(auto el : names)
			std::cout<<"id: "<<el.first<<std::endl<<"\t* posicion de memoria: "<<el.second.first
				<<" * espacio abarcado: "<<el.second.second
				<<" * espacio ocupado: "<<best_fit_size( el.second.second )<<std::endl ;
	}

	if ( free_mem.size() > 0 ) 
	{ 
		std::cout<<"\nBloques de memoria libre:\n"; 

		for(auto el : free_mem)
			std::cout<<"\t* Hay un bloque de tamaño "<<el.second<<" en la posicion "<<el.first<<'\n';

		std::cout<<'\n'; 
	}

	return SUCCESS;
}


STATUS Simulator::erase(std::string name) 
{ 
	if (names.count(name) == 0) 
		return ERR_INVLABEL; 
	int ub, bf; 

	auto pp = names[name];  

	bf = best_fit_size( pp.second );

	ub = pp.first + bf ; 

	fill_segment( pp.first, ub, true ) ; 	// erase memory segment
	bounds.erase( pp.first ) ;  			// erase from set
	names.erase( name ); 					// erase from map 
	merge_blocks( pp.first, bf );   		// merge free buddies

	return SUCCESS; 
}


std::pair<bool,int> Simulator::buddy (int pos, int size) 
{ 
	if ( (pos/size) % 2 == 0 ) 
		return std::make_pair(false,  pos + size) ;
	return std::make_pair(true, pos - size) ; 
}


void Simulator::create_blocks(int pos, int sz, bool top_down)
{
	int ref = (top_down)? sz : pos;
	int dum = 1; 

	while ( dum <= sz ) 
	{ 
		if ( (dum & ref) != 0 ) 
		{ 
			// create blocks from biggest one to smallest
			if ( top_down ) 
			{  
				ref -= dum; 
				free_mem[ ref ] = dum; 
			}
			// create blocks from smallest one to biggest
			else { 
				free_mem[ ref ] = dum; 
				ref += dum; 
			}
		}
		dum <<=1 ;
	}
}	


void Simulator::merge_blocks(int pos, int sz) 
{ 
	auto pal = buddy (pos, sz) ; 
	int current_sz = 2 * sz; 	
	int last = pos; 

	// While there's a buddy block with free memory, erase it
	while ( mem[pal.second] && pal.second + current_sz < size) 
	{ 
		free_mem.erase(pal.second); 

		last = pal.second - ((pal.first )? 0 : current_sz/2) ;

		pal = buddy (last,  current_sz); 
		current_sz *= 2 ; 		
	}

	// Then add the biggest block of continous free memory spaned
	free_mem[ last ] = current_sz/2; 
}
