#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "RNG.h"
#include "Watcard.h"
#include "Printer.h"
#include <vector>

using namespace std;

_Task Groupoff {
    Printer &printer;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupOffDelay;
    vector<WATCard::FWATCard *> *unusedWatCards; // vector of giftcards that have not been given out
    vector<WATCard::FWATCard *> *usedWatCards; // vector of giftcards that have been given out

    void main();
  public:
    Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupOffDelay);
    ~Groupoff();
    WATCard::FWATCard giftCard();
};

#endif // __GROUPOFF_H__
