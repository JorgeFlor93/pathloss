#include "RandomIdClient.hpp"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int RandomIdClient::getRandom(){
    srand((unsigned)time(NULL));
    int n = rand()%1001; // números aleatorios entre 0 y 1000
    std::cout << "Petición " << n << std::endl;
    return n;
}