#pragma once

#include <cstdlib>
#include <ctime>

int randomInRange(int size)
{
    std::srand(std::time(nullptr));
    int randomVar = std::rand() / ((RAND_MAX + 1u) / size);

    return randomVar;
}