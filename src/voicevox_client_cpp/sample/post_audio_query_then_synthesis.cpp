#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/post.hpp"

#include <iostream>

using ReqBasePtr = voicevox_client_cpp::request::Base::SharedPtr;
using ReqAudioQueryBuilder = voicevox_client_cpp::request::post::audio_query::Builder;
using ReqSynthesisBuilder = voicevox_client_cpp::request::post::synthesis::Builder;
using ReqAudioQuery = voicevox_client_cpp::request::post::audio_query::Request;
using ReqSynthesis = voicevox_client_cpp::request::post::synthesis::Request;


void GetSynthesised(const web::json::value& json)
{
  std::cout
    << "got synthesised json" << std::endl
    << json << std::endl;
}


void RequestSynthesis(const web::json::value& json)
{
  ReqBasePtr req_ptr = std::make_shared<ReqSynthesis>(
      ReqSynthesisBuilder()
       .ipaddr("localhost")
       .port(50021)
       .speaker(3)
       .enable_interrogative_upspeak(false)
       .accent_phrases(json)
       .Get());

  voicevox_client_cpp::Client::GetInstance()
  .Request(req_ptr.get(), std::bind(&GetSynthesised, std::placeholders::_1))
    .wait();
}

int main(int argc, char** argv)
{
   ReqBasePtr req_ptr = std::make_shared<ReqAudioQuery>(
       ReqAudioQueryBuilder()
        .ipaddr("localhost")
        .port(50021)
        .text("こんにちは")
        .speaker(3)
        .Get());

  // Get the same output by using both of two requests
  voicevox_client_cpp::Client::GetInstance()
    .Request(req_ptr.get(), std::bind(&RequestSynthesis, std::placeholders::_1))
      .wait();

  return EXIT_SUCCESS;
}
