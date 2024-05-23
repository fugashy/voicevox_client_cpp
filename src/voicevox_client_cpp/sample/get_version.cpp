#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/get.hpp"

#include <iostream>

void Callback(const web::json::value& json)
{
  std::cout
    << "callback!" << std::endl
    << json << std::endl;
}

using ReqBuilder = voicevox_client_cpp::request::get::version::Builder;

int main(int argc, char** argv)
{
  const web::http::http_request req = ReqBuilder().get();

  voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request(req, std::bind(&Callback, std::placeholders::_1))
      .wait();

  return EXIT_SUCCESS;
}
