#include <vector>
#include <iostream>
#include "Manager.h"
#include "Grid.h"
using namespace std;

void Manager::setVectors(vector<Aphid> newAphids, vector<Ladybug> newLadys)
{
    currentAphids = newAphids;
    currentLadys = newLadys;
}

void Manager::updateAll()
{
    for (vector<Aphid>::iterator itA = this->currentAphids.begin();  
                itA != this->currentAphids.end(); ++itA)
    {
        (*itA).update();
        this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
        cin.get();
    }
    for (vector<Ladybug>::iterator itL = this->currentLadys.begin();  
                itL != this->currentLadys.end(); ++itL)
    {
        (*itL).update();
        this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
        cin.get();
    }
}
