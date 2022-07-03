#pragma once

class Physics
{
public:
    Physics& getInstance();

private:
    Physics() {};

    Physics(const Physics&);
    Physics& operator=(const Physics&);
};

