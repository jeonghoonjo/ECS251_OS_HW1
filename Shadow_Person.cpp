
#include "Shadow_Person.h"

// JSON RPC part
#include <stdlib.h>
#include "hw1client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

Shadow_Person::Shadow_Person
(std::string arg_host_url, std::string arg_vsID, std::string arg_class_id, std::string arg_object_id)
  : Person { arg_host_url, arg_vsID, arg_class_id, arg_object_id }
{
  std::cout << "Shadow Person created" << std::endl;
}

Shadow_Person::Shadow_Person
(std :: string arg_name, std :: string arg_id, std :: string arg_host_url, std::string arg_vsID, std::string arg_class_id, std::string arg_object_id)
  : Person { arg_name, arg_id, arg_host_url, arg_vsID, arg_class_id, arg_object_id }
{
  std::cout << "[!] New Shadow Person created" << std::endl;
}
std :: string
Shadow_Person::getVsID()
{
  cout << "Shadow Get VsID: " << endl;
  HttpClient httpclient((this->host_url).c_str());
  hw1Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    myv = myClient.GetVsID("getVsID", "This is a person JSON string!",
			      (this->class_id).c_str(), (this->host_url).c_str(),
			      (this->object_id).c_str(), (this->owner_vsID).c_str());
    cout << myv.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  // std::cout << myv["distance"] << std::endl;
  return (myv["result"]).asString();
}

bool Shadow_Person :: operator==(Shadow_Person& aPerson) {
    // mandatory part
    //
    HttpClient httpclient((host_url).c_str());
    hw1Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;

    try{
        std :: cout << "Calling OperatorEqEq from a shadow function"
            << endl;
        // Here goes nothing...
        myv = myClient.OperatorEqEq(
            (aPerson.class_id).c_str(),
            (aPerson.host_url).c_str(),
  	        (aPerson.object_id).c_str(),
            (aPerson.owner_vsID).c_str(),
            "operator==",
            "This is an OperatorEqEq string!", 
            (this->class_id).c_str(),
            (this->host_url).c_str(),
  	        (this->object_id).c_str(),
            (this->owner_vsID).c_str());
        cout << myv.toStyledString() << endl;
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    return (myv["result"]).asBool(); 
}
