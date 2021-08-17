/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** main
*/

#include <vector>
#include <string>
#include <iostream>
#include "Error/Error.hpp"
#include "GameManager/Game.hpp"
#include "Core/Core.hpp"

int main(int ac, char **av)
{
    Error er(ac, av);

    try {
        er.handling();
        Core()();
    } catch(std::exception &e) {
        std::cerr << "Error in Indie: " << e.what() << std::endl;
        return 84;
    }
}