#include "Parser.hpp"
#include <iostream>


bool isInt (const std::string & ss) 
{ 
	bool chk = true ;
	for (auto character : ss)  
		chk = chk && isdigit ( (int) character ) ; 	

	return chk ;
}


void words(std::vector<std::string> &wd, std::string &ss) 
{  
	size_t  curr; 

	std::string separator = " "; 

	while ( (curr = ss.find( separator ) ) != std::string::npos ) 
	{

		if ( curr == 0 ) 
			ss.erase(0,1) ; 
		else {  
			wd.push_back ( ss.substr(0,curr) ) ; 
		 	ss.erase(0, curr) ; 
		}
	}

    wd.push_back ( ss.substr(0,curr) ) ; 	
} 


bool parse_input(std::string &ss, Simulator &sim) 
{ 
	std::vector<std::string> wd; 

	words(wd, ss) ; 

	if (wd.size() == 3) 
	{ 

		if ( wd[0].compare(RESERVAR) == 0 && isInt( wd[2] ) ) 
		{ 
			int errn = sim.insert( wd[1], stoi ( wd[2] ) )  ; 

			switch (errn) { 
				case ERR_NAME : 
					printf("El nombre proporcionado ya tiene memoria asignada\n"); 
					break ;
				case ERR_SIZE : 
					printf("Memoria insufciente\n"); 
					break; 
				case ERR_MINSIZE : 
					printf("Solicito una cantidad invalida de memoria. Debe ser mayor a 0\n"); 
			}
					
		}
		else 
			return false; 

	}
	else if ( wd.size() == 2) 
	{ 

		if (wd[0].compare(LIBERAR) == 0 ) { 
			bool errn = sim.erase( wd[1] ) ;  

			if ( !errn )  
				printf("El nombre proporcionado no tiene memoria asociada.\n");
		}

		else 
			return false; 

	}
	else if ( wd.size() == 1) 
	{ 

		if (ss.compare(MOSTRAR) == 0)  
			sim.display_memory(); 
		else if ( ss.compare(SALIR) == 0 ) { 
			exit(1); 
			return true; 
		}
		else 
			return false; 
	}
	else 
		return false; 

	return true; 
}