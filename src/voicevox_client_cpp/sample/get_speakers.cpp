#include "voicevox_client_cpp/client.hpp"

#include <iostream>

void Callback()
{
  std::cout << "callback!" << std::endl;
}

int main(int argc, char** argv)
{
  voicevox_client_cpp::Client::GetInstance().Request(
      std::bind(&Callback)).wait();


  return EXIT_SUCCESS;
}
