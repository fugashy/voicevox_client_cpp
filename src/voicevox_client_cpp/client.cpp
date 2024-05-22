#include "voicevox_client_cpp/client.hpp"

#include <string>

#include <cpprest/http_client.h>

#include "voicevox_client_cpp/request.hpp"


namespace voicevox_client_cpp
{

Client& Client::GetInstance()
{
  static Client instance;
  return instance;
}

// pplx::task<void> Client::Request(const Query& query, const CallbackType callback)
pplx::task<void> Client::Request(const request::Base* req, const CallbackType callback)
{
  return pplx::create_task(
      [req]
      {
        web::http::client::http_client client(req->GetUrl());
        return client.request(req->GetMethod());
      })
    .then(
        [callback](web::http::http_response response)
        {
          std::cout
            << "the response:" << std::endl
            << response.extract_string().get().c_str() << std::endl;
          callback();
        });
}


}  // namespace voicevox_client_cpp
