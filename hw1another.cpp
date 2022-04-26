

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw1server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs251
#include "Core.h"
#include "Person.h"
#include "Transaction.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

class Myhw1Server : public hw1Server
{
public:
  Myhw1Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value GetDistance(const std::string& action, const std::string& arguments,
				 const std::string& class_id, const std::string& host_url,
				 const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value Conflict_of_Interest(const std::string& action, const std::string& arguments,
				 const std::string& class_id, const std::string& host_url,
				 const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value GetVsID(const std::string& action, const std::string& arguments,
				 const std::string& class_id, const std::string& host_url,
				 const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value OperatorEqEq(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
};

Myhw1Server::Myhw1Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw1Server(connector, type)
{
  std::cout << "Myhw1Server Object created" << std::endl;
}

Flight *f3;
Person *pp3;

// member function
Json::Value
Myhw1Server::GetDistance
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  cout << "Another GetDistance" << endl;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") || ((object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000003")
	d = f3->getDistance();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"distance\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

// The second function for Shadow Flight
// member function
Json::Value
Myhw1Server::Conflict_of_Interest
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  cout << "Another COI" << endl;
  std::cout << "\t [!] COI " << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  bool d;
  if ((class_id != "Flight") || ((object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000003")
        d = f3->Conflict_of_Interest();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"result\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

// The third function for Shadow Person
// member function
Json::Value
Myhw1Server::GetVsID
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << "\tAnotherVsID " << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;
  std :: string d;
  if ((class_id != "Person"))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
    if (object_id == "00005555")
	  d = pp3->getVsID();
    }

  strJson += "{\"status\" : \"successful\", ";
  strJson += ("\"result\": " + d + "}");

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}
// another

Json::Value Myhw1Server::OperatorEqEq(
    const std::string& aPerson_class_id,
    const std::string& aPerson_host_url, 
    const std::string& aPerson_object_id, 
    const std::string& aPerson_owner_vsID, 
    const std::string& action,
    const std::string& arguments,
    const std::string& class_id,
    const std::string& host_url,
    const std::string& object_id,
    const std::string& owner_vsID
) {
    Json::Value result;
    std::string strJson;
    cout << "[another_PRINT]" << endl;
    cout << "aPerson_class_id  : " << aPerson_class_id << endl;
    cout << "aPerson_host_url  : " << aPerson_host_url << endl; 
    cout << "aPerson_object_id : " << aPerson_object_id << endl;
    cout << "aPerson_owner_vsID: " << aPerson_owner_vsID << endl; 
    cout << "action            : " << action << endl;
    cout << "arguments         : " << arguments << endl;
    cout << "class_id          : " << class_id << endl; 
    cout << "host_url          : " << host_url << endl;
    cout << "object_id         : " << object_id << endl;
    cout << "owner_vsID        : " << owner_vsID << "\n" << endl; 
   
    cout << "\tAnother operator==" << endl;
    // Requires an object from flight class
    bool d;
    // Comparing these numbers for some reason
    if(class_id != "Person" || aPerson_class_id != "Person")
        strJson +=
            "{\"status\" : \"failed\", \n\"reason\" : \"incorrect class_id\"}";
    else if(object_id == "00005555" && aPerson_object_id == "00005555") {
        d = (*pp3 == *pp3);
        strJson += "{\"status\" : \"successful\", ";
        strJson += ("\"result\": " + to_string(d) + "}");
    }
    else {
        strJson +=
            "{\"status\" : \"failed\", \n\"reason\" : \"incorrect object_id\"}";
    }

    // There is just an equal comparator for this function.
    // Using parts from the previous function to return the results
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;
    bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
    delete reader;

    if (!parsingSuccessful) {
        std::cout << "Failed to parse the JSON, errors:" << std::endl;
        std::cout << errors << std::endl;
    }

    return result;
}
int main() {

  Airline United;
  GPS_DD gps_Davis {38.5, -121.7};
  GPS_DD gps_NYC {40.7, -73.95};
  GPS_DD gps_Sydney {-33.87, 151.213};
  IP_Address IP_Davis {12345678};
  IP_Address IP_Sydney {12345678};
  IP_Address IP_NYC {12375678};

  Person p3 {"Lion Emperor", "323456789123456789", "http://169.237.6.102", "123456789", "Person", "00005555"};
  pp3 = (&p3);

  Flight flight_three {"http://169.237.6.102", "1234567890", "Flight", "00000003",
      TR_TYPE_FLIGHT, "desc", p3, gps_Davis, IP_Davis, time(NULL),
      p3, United, "9999999999", gps_NYC, gps_Sydney};

  f3 = (&flight_three);

  cout << "==========================================================" << endl;
  HttpServer httpserver(8385);
  Myhw1Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the another" << endl;
  getchar();

  s.StopListening();
  return 0;
}
