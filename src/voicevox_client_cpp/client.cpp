#include "voicevox_client_cpp/client.hpp"

#include <string>

#include <cpprest/http_client.h>

#include "voicevox_client_cpp/request.hpp"


namespace voicevox_client_cpp
{

Client& Client::GetInstance(const std::string& uri)
{
  static Client instance(uri);
  return instance;
}

Client::Client(const std::string& uri)
  : client_(new web::http::client::http_client(uri))
{
}

pplx::task<void> Client::Request(const web::http::http_request& req, const CallbackType callback)
{
  return pplx::create_task(
      [this, req]
      {
        return this->client_->request(req);
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
