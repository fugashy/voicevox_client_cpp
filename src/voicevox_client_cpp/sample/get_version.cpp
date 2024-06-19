#include "voicevox_client_cpp/voicevox_client_cpp.hpp"

#include <iostream>

using ReqBuilder = voicevox_client_cpp::request::get::version::Builder;

void ShowJson(const voicevox_client_cpp::Client::OptionalJson& json)
{
  if (json == std::nullopt)
  {
    std::cerr << "Null results causes by invalid query may be" << std::endl;
  }
  std::cout << json.value() << std::endl;
}

int main(int argc, char** argv)
{
  const web::http::http_request req = ReqBuilder().get();

  auto json = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalJson>(req);
  ShowJson(json);

  auto task = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request(req, std::bind(&ShowJson, std::placeholders::_1));

  task.wait();

  return EXIT_SUCCESS;
}
