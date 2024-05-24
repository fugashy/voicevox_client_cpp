#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/post.hpp"

#include <iostream>

using ReqAudioQueryBuilder = voicevox_client_cpp::request::post::audio_query::Builder;
using ReqSynthesisBuilder = voicevox_client_cpp::request::post::synthesis::Builder;

void GetSynthesised(const web::json::value& json)
{
  std::cout
    << "got synthesised json" << std::endl
    << json << std::endl;
}


void RequestSynthesis(const web::json::value& json)
{
   const web::http::http_request req = ReqSynthesisBuilder()
       .speaker(3)
       .enable_interrogative_upspeak(false)
       .accent_phrases(json)
       .get();

  voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
  .Request(req, std::bind(&GetSynthesised, std::placeholders::_1));
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

  voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request(req, std::bind(&RequestSynthesis, std::placeholders::_1));

  return EXIT_SUCCESS;
}
