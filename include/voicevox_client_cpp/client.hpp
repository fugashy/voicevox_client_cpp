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
  using OptionalJson = std::optional<web::json::value>;
  using OptionalString = std::optional<std::string>;

  template<class T>
  using CallbackType = std::function<void(const T&)>;

  Client(const Client&) = delete;
  Client& operator=(const Client&) = delete;

  static Client& GetInstance(const std::string& uri);

  void Request(
      const web::http::http_request& req,
      const CallbackType<OptionalJson> callback_json);
  void Request(
      const web::http::http_request& req,
      const CallbackType<OptionalString> callback_audio);

private:
  Client(const std::string& uri);
  ~Client() = default;

  std::unique_ptr<web::http::client::http_client> client_;
};

}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
