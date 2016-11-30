#include "RNG.h"
#include "config.h"
#include "Printer.h"
#include "Parent.h"
#include "Bank.h"
#include "WatcardOffice.h"
#include "Groupoff.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"

#include <iostream>

void uMain::main() {
  char *configfile = "soda.config";
  size_t seed;
  switch (argc) {
    case 3:
      seed = atoi(argv[2]);
      rng.set_seed(seed);    
    case 2:
      configfile = argv[1];
    default:
      break;
  }
  ConfigParms params;
  processConfigFile(configfile, params);

  cout << params.sodaCost << endl;
  cout << params.numCouriers << endl;
  cout << params.maxPurchases << endl;

  VendingMachine *machinelist = new VendingMachine[params.numVendingMachines];
  Student *studentlist = new Student[params.numStudents];

  Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
  Bank bank(params.numStudents);
  Parent parent(printer, bank, params.numStudents, params.parentalDelay);
  WATCardOffice office(printer, bank, params.numCouriers);
  Groupoff groupoff();
  NameServer nameserver();

  for (size_t numVend = 0; numVend < params.numVendingMachines; numVend++) {
    machinelist[numVend] = new VendingMachine();
  }
  
  BottlingPlant *plant = new BottlingPlant();
  
  for (size_t numStudent = 0; numStudent < params.numStudents; numStudent++) {
    studentlist[numStudent] = new Student();
  }

  for (size_t numStudent = 0; numStudent < params.numStudents; numStudent++) {
    delete studentlist[numStudent];
  }
  delete[] studentlist;

  delete plant;
  for (size_t numVend = 0; numVend < params.numVendingMachines; numVend++) {
    delete machinelist[numVend];
  }
  delete[] machinelist;
}
