Project:
CS22510 Assignment 1
Aphids and Ladybugs

Author: 
Max Atkins (mta2) 130017927

C++ Standard required: C++11

Necessary files:
Run.cpp (Main file)
Manager.h (Class Definition)
Manager.cpp (Class Implementation)
Grid.h (Class Definition)
Grid.cpp (Class Implementation)
Animal.h (Class Definition)
Animal.cpp (Class Implementation)
Aphid.cpp (Class Implementation)
Ladybug.cpp (Class Implementation)
AnimalVisitor.h (Visitor Pattern Definition)

Config files:
config.txt 
Format:
10 10 //Grid size
3     //Number of aphids
0 0   //Position of aphid
1 1   //Position of aphid
2 2   //Position of aphid
2     //Number of ladybugs
0 9   //Position of ladybug
1 8   //Position of ladybug

aphidConfig.txt
Format:
0.8   //Probability to move
0.2   //Probability to fight
0.1   //Probability to fight as group
0.3   //Probability to reproduce

ladybugConfig.txt
Format:
0.8   //Probability to move
0.2   //Probability to fight
0.4   //Probability to change preferred direction
0.1   //Probability to reproduce

Libraries included:
<iostream>
<string>
<fstream>
<vector>
<utility>
<chrono>
<thread>
<iomanip>
<time.h>
<stdlib.h>
<stdio.h>
std

Instructions:
Compile Run.cpp, with all files in the same directory, including the resource files, according to
the C++11 standard. 
