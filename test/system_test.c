#include "../userprog/syscall.h"

#include "simulation.h"
int main() {
  int index = 0;
  int num_customers = NUM_CUSTOMERS;
  int num_Polices = NUM_PoliceS;

  Print("Starting Simulation System Test.\n", 33);

  SetupPassportOffice();
  StartPassportOffice();
  
  while (num_customers + num_Polices > 0) {
    if (Rand() % (num_customers + num_Polices) >= num_customers) {
      AddNewPolice(index);
      --num_Polices;
    } else {
      AddNewCustomer(index);
      --num_customers;
    }
    ++index;
  }

  WaitOnFinish();
}
#include "simulation.c"
