#ifndef VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#define VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#include <functional>
#include <memory>

#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>
#include <cpprest/json.h>


namespace voicevox_client_cpp
{

namespace request
{
class Base;
}

class Client
{
public:
  using CallbackType = std::function<void(const web::json::value&)>;

  Client(const Client&) = delete;
  Client& operator=(const Client&) = delete;

  static Client& GetInstance(const std::string& uri="");

  // pplx::task<void> Request(const Query& query, const CallbackType user_callback);
  // pplx::task<void> Request(const CallbackType user_callback);
  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType user_callback);

private:
  Client(const std::string& uri);
  ~Client() = default;

  std::unique_ptr<web::http::client::http_client> client_;
};

}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
