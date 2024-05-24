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
class Builder;
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

  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType<OptionalJson> callback_json);
  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType<OptionalString> callback_audio);

  template<class T>
  T Request(const web::http::http_request& req)
  {
    T out;
    auto callback = [&out](const T& in) { out = in; };
    auto task = Request(req, callback);
    task.wait();
    return out;
  }

private:
  Client(const std::string& uri);
  ~Client() = default;

  std::unique_ptr<web::http::client::http_client> client_;
};

extern "C"
{
Client* GetClientInstance(const char* uri);
const char* RequestJsonString(
    Client* client,
    request::Builder* req_builder);
const char* RequestString(
    Client* client,
    request::Builder* req_builder);
void FreeString(const char* str);
}  // extern "C"

}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
