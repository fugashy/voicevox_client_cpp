#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/post.hpp"

#include <iostream>

using ReqAudioQueryBuilder = voicevox_client_cpp::request::post::audio_query::Builder;
using ReqSynthesisBuilder = voicevox_client_cpp::request::post::synthesis::Builder;

void GetSynthesised(const voicevox_client_cpp::Client::OptionalString& string)
{
  if (string == std::nullopt)
  {
    std::cerr << "Null results causes by invalid query may be" << std::endl;
    return;
  }
  std::cout << "saved audio file path: " << string.value() << std::endl;
}


void RequestSynthesis(const voicevox_client_cpp::Client::OptionalJson& json)
{
  if (json == std::nullopt)
  {
    std::cerr << "Null results causes by invalid query may be" << std::endl;
    return;
  }

  const web::http::http_request req = ReqSynthesisBuilder()
      .speaker(3)
      .enable_interrogative_upspeak(false)
      .accent_phrases(json.value())
      .get();

  auto task = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
  .Request(req, std::bind(&GetSynthesised, std::placeholders::_1));

  task.wait();
}

int main(int argc, char** argv)
{
  std::string text = "こんにちは";
  if (argc > 1)
  {
    text = argv[1];
  }
  std::cout << "input: " << text << std::endl;
  const web::http::http_request req = ReqAudioQueryBuilder()
       .text(text)
       .speaker(3)
       .get();

  auto task = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request(req, std::bind(&RequestSynthesis, std::placeholders::_1));

  task.wait();

  return EXIT_SUCCESS;
}
