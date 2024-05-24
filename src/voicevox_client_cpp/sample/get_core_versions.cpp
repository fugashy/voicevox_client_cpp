#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/get.hpp"

#include <iostream>

using ReqBuilder = voicevox_client_cpp::request::get::core_versions::Builder;

void ShowJson(const voicevox_client_cpp::Client::OptionalJson json)
{
  if (json == std::nullopt)
  {
    std::cerr << "Null results causes by invalid query may be" << std::endl;
    return;
  }
  std::cout << json.value() << std::endl;
}


int main(int argc, char** argv)
{
  // build request then get it.
  const web::http::http_request req = ReqBuilder().get();

  // sync interface
  auto json = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalJson>(req);
  ShowJson(json);

  // async interface
  // request the get the handler.
  auto task = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request(req, std::bind(&ShowJson, std::placeholders::_1));

  // do some thing while a request is processed

  // wait for the task completed
  task.wait();

  return EXIT_SUCCESS;
}
