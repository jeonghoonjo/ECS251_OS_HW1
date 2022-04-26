
// ecs251 first program

#include <iostream>
#include "Shadow_Flight.h"
#include "Shadow_Person.h"

using namespace std;

int
main()
{
  
  // This person exists in the server.
  
  Shadow_Person sp1 { "http://127.0.0.1:8384", "1234567890", "Person", "00000005" };
  std::cout << "1  " << ((Person&) sp1).getVsID() << std::endl; //It will call Shadow Person's getVsID because it's virtual function
  std::cout << "2  " << sp1.getVsID() << std::endl;

  Shadow_Person sp2 { "http://localhost:8384", "1234567890", "Person", "00000006" };
  std::cout << "3  " << ((Person&) sp2).getVsID() << std::endl;
  std::cout << "4  " << sp2.getVsID() << std::endl;  

  // This person exists in the hw1another. The server should make a remote
  // call to find out this real person.

  Shadow_Person sp3 { "http://127.0.0.1:8384", "123456789", "Person", "00005555" };
  std::cout << "5  " << ((Person&) sp3).getVsID() << std::endl;
  std::cout << "6  " << sp3.getVsID() << std::endl;
   
  // End of person calls.
  
  std :: cout << "===========================================" << std :: endl;

  // Reference implementation for getDistance.
  
  Shadow_Flight sf3 { "http://localhost:8384", "1234567890", "Flight", "00000003" };
  std::cout << "7 " << std::to_string(((Flight&) sf3).getDistance()) << std::endl;

  Shadow_Flight sf2 { "http://localhost:8384", "1234567890", "Flight", "00000002" };
  std::cout << "8 " << std::to_string(sf2.getDistance()) << std::endl;

  Shadow_Flight sf1 { "http://localhost:8384", "1234567890", "Flight", "00000001" };
  std::cout << "9 " << std::to_string(sf1.getDistance()) << std::endl;

  // End of reference implementation.
  
  std :: cout << "===========================================" << std :: endl;
  
  
  if (sp1 == sp2) printf("sp1, sp2 :: They are equal\n");   // unequal
  if (sp1 == sp1) printf("sp1, sp1 :: They are equal\n");   // equal, but, within the server
  if (sp1 == sp3) printf("sp1, sp3 :: They are equal\n");   // unequal
  if (sp3 == sp3) printf("sp3, sp3 :: They are equal\n");   // equal, another
  std :: cout << "===========================================" << std :: endl;
  
  if (sf1.Conflict_of_Interest()) printf("sf1 coi\n");
  if (sf2.Conflict_of_Interest()) printf("sf2 coi\n");
  if (sf3.Conflict_of_Interest()) printf("sf3 coi\n");
  
  return 0;
}
