
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
#include "Shadow_Flight.h"
#include "Shadow_Person.h"
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

Flight *f2;
Shadow_Flight *f3;

Person *pp1;
Person *pp2;

Shadow_Person *spp3;

// member function
Json::Value
Myhw1Server::GetDistance
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  cout << "Server Get Distance" << endl;
  cout << "action    :: " << action << endl;
  cout << "arguments :: " << arguments << endl;
  cout << "class_id  :: " << class_id << endl;
  cout << "host_url  :: " << host_url << endl;
  cout << "object_id :: " << object_id << endl;
  cout << "owner_vsID:: " << owner_vsID << endl; 
  cout << endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") || ((object_id != "00000002") && (object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000002")
	d = f2->getDistance();
      else
	d = f3->getDistance();
        cout << "Here" << endl;

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
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;
  bool d;
  cout << "Server COI" << endl;
  cout << " [PRINT] " << endl;
  cout << class_id << " " << object_id << endl;
  if ((class_id != "Flight") || ((object_id != "00000002") && (object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000002")
	d = f2->Conflict_of_Interest();
      else {
          cout << "Need to call this line!!!!" << endl;
	d = f3->Conflict_of_Interest();
      }

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"result\": " + to_string(d) + "}");
    }
  cout << "#" << d << endl;
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
  std::cout << "vsID " << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;
  std :: string d;

  if ((class_id != "Person") || ((object_id != "00000005") && (object_id != "00000006") && (object_id != "00005555")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000005")
	    d = pp1->getVsID();
      else if (object_id == "00005555") {
        d = spp3->getVsID();
      }
      else
	    d = pp2->getVsID();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"result\": " + d + "}");
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
    cout << "[server_PRINT]" << endl;
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
    // Requires an object from flight class
    bool d;
    if(class_id != "Person" || aPerson_class_id != "Person") {
        strJson +=
            "{\"status\" : \"failed\", \n\"reason\" : \"incorrect class_id\"}";
    }
    else {
        // Use an object from Flight class.
        // The method from Flight class will call the method from Person class.
        //
        // These are objects in hw1server
        cout << "This is called!" << endl;
        if ((aPerson_object_id == "00000006" && object_id == "00000005") ||
                (aPerson_object_id == "00000005" && object_id == "00000006")) {
            d = (*pp1 == *pp2);
        }
        else if ((aPerson_object_id == object_id) && object_id != "00005555") {
            if (object_id == "00000006")
                d = (*pp2 == *pp2);
            else
                d = (*pp1 == *pp1);
        }
        else  if (aPerson_object_id == "00005555" || object_id == "00005555") {
            if (aPerson_object_id == "00005555") {
                if (object_id == "00000005") {
                    d = (*pp1 == *spp3);
                }
                else if (object_id == "00000006") {
                    d = (*pp2 == *spp3);
                }
                else {
                    // This should go to another
                    d = (*spp3 == *spp3);
                }
            }
            else if (object_id == "00005555") {
                if (aPerson_object_id == "00000005") {
                    d = (*pp1 == *spp3);
                }
                else if (aPerson_object_id == "00000006") {
                    d = (*pp2 == *spp3);
                }
                else {
                        cout << "=========$$$$  " << endl;
                        d = (*spp3 == *spp3);
                }
            }
        }
        strJson += "{\"status\" : \"successful\", ";
        strJson += ("\"result\": " + to_string(d) + "}");
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

  Person p1 {"Lion King", "123456789123456789","http://169.237.6.102", "123456789", "Person", "00000005"};
  Person p2 {"Lion Queen", "223456789123456789" ,"http://169.237.6.102", "123456789", "Person", "00000006"};

  pp1 = (&p1);
  pp2 = (&p2);

  Transaction flight_one {"http://169.237.6.102", "1234567890", "Transaction", "00000001",
      TR_TYPE_FLIGHT, "desc", p1, gps_Davis, IP_Davis, time(NULL)};

  Flight flight_two {"http://169.237.6.102", "1234567890", "Flight", "00000002",
      TR_TYPE_FLIGHT, "desc", p1, gps_Davis, IP_Davis, time(NULL),
      p2, United, "1234567890", gps_Davis, gps_NYC};

  Shadow_Flight flight_three { "http://localhost:8385", "1234567890", "Flight", "00000003" };
  Shadow_Person sp3 { "http://localhost:8385", "123456789", "Person", "00005555"};
  
  // Setting the gloabal pointer as the shadow person object
  spp3 = (&sp3);

  // Testing shadow calls from the server.

  // cout  << "-----------> " << ((Person &)spx3).getVsID() << endl;
  f2 = (&flight_two);
  f3 = (&flight_three);

  //  if (sp3 == sp3)
  //	cout << "These are equal" << endl;
  
  // End of testing

  cout << "==========================================================" << endl;
  HttpServer httpserver(8384);
  Myhw1Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
