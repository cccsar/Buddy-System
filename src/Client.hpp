#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cassert>

#include "Core.hpp"
#include "Parser.hpp"
#include "Simulator.hpp"

/// @brief TODO explain 
class Client 
{
public:
    /// @brief Initialices necessary objects for main API.
    /// @param mx Requested amount of memory to allocate 
    Client(const char* mx) ;

    /// @brief Start app
    STATUS run();

private:
    Simulator _sim;
    const std::string INTRO = "Simulador de manejo de memoria";
    const std::string DIALOG = "Que deseas hacer?: \n * RESERVAR <nombre> <cantidad>\n * LIBERAR <nombre>\n * MOSTRAR \n * SALIR\n";

    /// @brief Parse provided input
    /// @param ss Input string
    STATUS _parse_input(std::string &ss);

    /// @brief Display information concerning to specific errors 
    /// such as those defined in "simulator.hpp"
    /// @param err Error code
    void _error_handle(STATUS err) const;

};

#endif