/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Error
*/

#ifndef ERROR_H
#define ERROR_H

#include <iostream>

class Error {
public:
    Error(int ac, char **args);
    ~Error() = default;

    void handling();
private:
    int _ac;
    char **_args;
};

#endif //ERROR_H
