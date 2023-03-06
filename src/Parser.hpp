#include<vector> 
#include<string> 
#include<string> 

#include "Simulator.hpp"

#define RESERVAR "RESERVAR"
#define LIBERAR "LIBERAR"
#define MOSTRAR "MOSTRAR"
#define SALIR "SALIR"

#ifndef PARSER_HPP
#define PARSER_HPP

/// @brief Checks if a string of characters is an integer.
bool isInt (const std::string & ss); 

/// @brief Breaks a string terminated on '\n' into a vector of space separated words.
void words(std::vector<std::string> &wd, std::string &ss); 

/// @brief Given a string and a simulator, parses the string and acts on behalf
/// of the parsed request.
bool parse_input(std::string &ss, Simulator &sim) ; 

#endif
