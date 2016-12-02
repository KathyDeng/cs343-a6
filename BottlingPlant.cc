#include "BottlingPlant.h"
#include "RNG.h"
#include "VendingMachine.h"

BottlingPlant::BottlingPlant() :
  printer(prt),
  nameserver(nameServer),
  nummachines(numVendingMachines),
  maxshipstock(maxShippedPerFlavour),
  maxstock(maxStockPerFlavour),
  shippingtime(timeBetweenShipments),
  closed(false) {
  stock = new size_t[VendingMachine::Flavours::COUNT];
  for (size_t i = 0; i < VendingMachine::Flavours::COUNT; ++i) {
    stock[i] = 0;
  }
}

BottlingPlant::~BottlingPlant() {
  delete[] stock;
  if (truck != nullptr) {
    delete truck; // does task delete itself when  main is completed?
  }

  printer.print(Printer::Kind::BottlingPlant, 'F');
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
  if (closed) {
    _Throw Shutdown();
  }

  // transfer stock to cargo and reset stock
  for (size_t i = 0; i < VendingMachine::Flavours::COUNT; i++) {
    cargo[i] = stock[i];
    stock[i] = 0;
  }
  printer.print(Printer::Kind::BottlingPlant, 'P');
}


void BottlingPlant::main() {
  printer.print(Printer::Kind::BottlingPlant, 'S');
  truck = new Truck(); 
  
  for (;;) {
    //produce
    yield(shippingtime);

    int produceCount = 0;
    for (size_t i = 0; i < VendingMachine::Flavours::COUNT; ++i) {
      stock[i] = rng(maxshipstock);
      produceCount += stock[i];
    } 
    printer.print(Printer::Kind::BottlingPlant, 'G', produceCount);

    _Accept(~BottlingPlant) {
      closed = true;
      _Accept(getShipment); // wait for truck to arrive
    } or _When(!closed) _Accept(getShipment); 

    //wait for truck to come pick up
    Accept(getShipment);
  }
}
