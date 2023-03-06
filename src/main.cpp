#include<stdio.h> 
#include<iostream> 

#include "Client.hpp"

int main(int argc, char **argv) 
{ 
	if ( argc <= 1) 
	{ 
		std::cerr<<RED<<"Error:"<<CYAN;		
		std::cerr<<" Es necesario 1 argumento que represente la memoria total. Saliendo.\n"; 
		std::cerr<<RESET;
		exit(-1);
	}

	Client API(argv[1]);
	
	API.run();

}
