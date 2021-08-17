/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(int ac, char **args): _ac(ac), _args(args)
{
}

void Error::handling()
{
    if (_ac != 1) {
        throw(std::invalid_argument("needs 1 arg to start"));
    }
}