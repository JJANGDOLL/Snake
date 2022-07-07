#pragma once

#include <Windows.h>

int randomInRange(int size);

bool checkSnakeIsEat(const COORD snake, const COORD feed);

bool checkSnakeHitBorder(const COORD snake, const COORD feed);

bool checkSnakeHitBody(const COORD snake, const COORD body);