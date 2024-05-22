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
          if (response.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "Unexpected status code" << std::endl;
            callback(web::json::value());
            return;
          }
          const web::json::value json = response.extract_json().get();
          callback(json);
        });
}


}  // namespace voicevox_client_cpp
