#ifndef ANIMALINTERACTOR_H
#define ANIMALINTERACTOR_H

class Aphid;
class Ladybug;

class AnimalInteractor
{
    public:
        virtual bool visit(Aphid &animal) = 0;
        virtual bool visit(Ladybug &animal) = 0;
};




#endif