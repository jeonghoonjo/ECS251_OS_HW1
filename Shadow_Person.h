
#ifndef _SHADOW_PERSON_H_
#define _SHADOW_PERSON_H_

#include "Transaction.h"
#include "Person.h"

class Shadow_Person: public Person
{
 private:
 public:
  Shadow_Person(std::string, std::string, std::string, std::string);
  Shadow_Person(std::string, std::string, std::string, std::string, std::string, std::string);
  virtual std :: string getVsID();
  virtual bool operator==(Shadow_Person& aPerson);
};

#endif // _SHADOW_FLIGHT_H_
