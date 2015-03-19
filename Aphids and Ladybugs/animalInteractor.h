#ifndef ANIMALINTERACTOR_H
#define ANIMALINTERACTOR_H

/**
 * Tells class that these classes do exist, just not here
 */
class Aphid;
class Ladybug;

/**
 * This class defines two functions to implement a visitor pattern.
 * This allows me to use one function to polymorphically choose a function
 * in ladybug and aphid class based on the parameter passed and the type of the
 * object calling it
 */
class AnimalVisitor
{
    //Public function declarations
    public:
        //Declare visit() for passing an aphid -- virtual overrideable
        virtual bool visit(Aphid &animal) = 0;
        
        //Declare visit() for passing a ladybug -- virtual overrideable
        virtual bool visit(Ladybug &animal) = 0;
};




#endif