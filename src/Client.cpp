#include <iostream>

#include "Client.hpp"

Client::Client(const char* mx)
{
	long int mx_size = strtol(mx, NULL, 10);

	assert( mx_size != 0L && errno != ERANGE
			&& "El texto ingresado no corresponde a un número valido de memoria total.\n");

	_sim = Simulator( (int) mx_size ) ; 

}

STATUS Client::run()
{
    std::cout<< Client::INTRO << '\n';

    std::string line;

	STATUS chk = SUCCESS;

	do
	{
		std::cout<< Client::DIALOG << '\n'; 
		std::cout<<"Siguiente eleccion: "; 

		std::getline(std::cin, line); 

		chk = _parse_input(line);

		if (chk != EXIT && chk != SUCCESS)
		{
			_error_handle(chk);
		}

	} while (chk != EXIT);

	return SUCCESS;
}

STATUS Client::_parse_input(std::string &ss) 
{ 
	std::vector<std::string> wd; 

	words(wd, ss) ; 

	switch (wd.size()) 
	{
		case 3:
			if ( wd[0].compare(RESERVAR) == 0 && isInt( wd[2] ) ) 
			{ 
				return Client::_sim.insert( wd[1], stoi ( wd[2] ) ) ;
			}
			else 
			{
				return ERROR; 
			}
			break;

		case 2:

			if (wd[0].compare(LIBERAR) == 0 ) 
			{ 
				return Client::_sim.erase( wd[1] ) ;
			}
			else 
			{
				return ERROR; 
			}
			break;

		case 1:
			if (ss.compare(MOSTRAR) == 0)  
			{
				return Client::_sim.display_memory(); 
			}
			else if ( ss.compare(SALIR) == 0 ) 
			{ 
				return EXIT; 
			}
			else 
			{
				return ERROR;
			}
			break;
		default:
			return ERROR; 
	}

	return ERROR; 
}


void Client::_error_handle(STATUS err) const
{
	std::cerr<<RED<<"Error: "<<CYAN;
	switch (err)
	{
		case ERROR :
			std::cerr<<"Opcion no reconocida. Ingrese una opcion correcta\n";
			break;
		case ERR_NAME : 
			std::cout<<"El nombre proporcionado ya tiene memoria asignada\n"; 
			break ;
		case ERR_SIZE : 
			std::cout<<"Memoria insufciente\n"; 
			break; 
		case ERR_MINSIZE : 
			std::cout<<"Solicito una cantidad invalida de memoria. Debe ser mayor a 0\n"; 
			break;
		case ERR_INVLABEL :
			std::cout<<"El nombre proporcionado no tiene memoria asociada.\n";
			break;
	}
	std::cerr<<RESET;
}