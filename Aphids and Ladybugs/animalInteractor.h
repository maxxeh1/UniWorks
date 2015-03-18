#ifndef ANIMALINTERACTOR_H
#define ANIMALINTERACTOR_H

class Aphid;
class Ladybug;

class AnimalInteractor
{
    public:
        virtual void interact(Aphid &animal) = 0;
        virtual void interact(Ladybug &animal) = 0;
};




#endif