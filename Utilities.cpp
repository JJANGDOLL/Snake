#include "Utilities.h"

#include <ctime>
//#include <cstdlib>
#include <random>
#include "World.h"

using namespace std;

int randomInRange(int size)
{
//     std::srand(std::time(nullptr));
//     int randomVar = std::rand() / ((RAND_MAX + 1u) / size);
// 
//     return randomVar;
//     
//     
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size);

    return dist(gen);
}

bool checkSnakeIsEat(const COORD snake, const COORD feed)
{
    if(snake.X == feed.X && snake.Y == feed.Y)
        return true;
    return false;
}

bool checkSnakeHitBorder(const COORD snake, const COORD border)
{
    if(snake.X == border.X && snake.Y == border.Y)
        return true;
    return false;
}

bool checkSnakeHitBody(const COORD snake, const COORD body)
{
    if(snake.X == body.X && snake.Y == body.Y)
        return true;
    return false;
}

