#include "voicevox_client_cpp/client.hpp"

#include <string>

#include <cpprest/http_client.h>


namespace voicevox_client_cpp
{

class Query
{
  Query()
  {
    hoge_ = "hoge";
  }

private:
  std::string hoge_;
};

class Response
{
public:
  Response() = default;
};


Client& Client::GetInstance()
{
  static Client instance;
  return instance;
}

// pplx::task<void> Client::Request(const Query& query, const CallbackType callback)
pplx::task<void> Client::Request(const CallbackType callback)
{
  return pplx::create_task(
      []
      {
        web::http::client::http_client client("http://localhost:50021/speakers");
        return client.request(web::http::methods::GET);
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
