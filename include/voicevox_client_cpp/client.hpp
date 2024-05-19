#ifndef VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#define VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#include <functional>

#include <pplx/pplxtasks.h>


namespace voicevox_client_cpp
{

class Query;
class Response;

class Client
{
public:
  using CallbackType = std::function<void(const Response&)>;

  Client(const Client&) = delete;
  Client& operator=(const Client&) = delete;

  static Client& GetInstance();

  pplx::task<void> Request(const Query& query, const CallbackType user_callback);

private:
  Client() = default;
  ~Client() = default;
};

}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
