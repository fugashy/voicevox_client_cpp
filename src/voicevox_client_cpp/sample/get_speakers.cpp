#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/get.hpp"

#include <iostream>

void Callback()
{
  std::cout << "callback!" << std::endl;
}

using ReqBasePtr = voicevox_client_cpp::request::Base::SharedPtr;
using ReqBuilder = voicevox_client_cpp::request::get::speakers::Builder;
using Req = voicevox_client_cpp::request::get::speakers::Request;

int main(int argc, char** argv)
{
  // Create a request via normal interface
   ReqBasePtr req_ptr(
      new Req(
        "http://localhost:50021"));

   // Create a request via builder interface
   ReqBasePtr req_ptr2 = std::make_shared<Req>(
       ReqBuilder()
        .url("http://localhost:50021")
        .core_version(std::nullopt)
        .Get());

  voicevox_client_cpp::Client::GetInstance()
    .Request(req_ptr.get(), std::bind(&Callback))
      .wait();
  voicevox_client_cpp::Client::GetInstance()
    .Request(req_ptr2.get(), std::bind(&Callback))
      .wait();

  return EXIT_SUCCESS;
}
