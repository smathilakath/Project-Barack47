/* 
 *    Author : Sumod Madhavan
 *  
 */
#ifndef PASSPORT_OFFICE_Police_H
#define PASSPORT_OFFICE_Police_H

#include <stdint.h>
#include <vector>

#include "../threads/synch.h"
#include "utilities.h"

class PassportOffice;
class Clerk;
class CashierClerk;

class Police : public Customer {
 public:
  Police(PassportOffice* passport_office);
  virtual ~Police() {}

  virtual std::string IdentifierString() const;
  virtual void Run();
};

#endif
