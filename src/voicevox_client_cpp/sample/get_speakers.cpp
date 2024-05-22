#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/get.hpp"

#include <iostream>

void Callback()
{
  std::cout << "callback!" << std::endl;
}

int main(int argc, char** argv)
{
  voicevox_client_cpp::request::Base::SharedPtr req(
      new voicevox_client_cpp::request::get::speakers::Request(
        "http://localhost:50021"));

  voicevox_client_cpp::Client::GetInstance()
    .Request(req.get(), std::bind(&Callback))
      .wait();

  return EXIT_SUCCESS;
}
