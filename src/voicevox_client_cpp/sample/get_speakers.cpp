#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/get.hpp"

#include <iostream>

void Callback(const web::json::value& json)
{
  std::cout
    << "callback!" << std::endl
    << json << std::endl;
}

using ReqBasePtr = voicevox_client_cpp::request::Base::SharedPtr;
using ReqBuilder = voicevox_client_cpp::request::get::speakers::Builder;
using Req = voicevox_client_cpp::request::get::speakers::Request;

int main(int argc, char** argv)
{
  // Create a request via normal interface
   ReqBasePtr req_ptr(
      new Req(
        "localhost",
        50021));

   // Create a request via builder interface
   ReqBasePtr req_ptr2 = std::make_shared<Req>(
       ReqBuilder()
        .ipaddr("localhost")
        .port(50021)
        .Get());

  // Get the same output by using both of two requests
  voicevox_client_cpp::Client::GetInstance()
    .Request(req_ptr.get(), std::bind(&Callback, std::placeholders::_1))
      .wait();
  voicevox_client_cpp::Client::GetInstance()
    .Request(req_ptr2.get(), std::bind(&Callback, std::placeholders::_1))
      .wait();

  return EXIT_SUCCESS;
}
