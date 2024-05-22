#ifndef VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#define VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#include <string>
#include <memory>

namespace voicevox_client_cpp::request
{

struct Base
{
  using SharedPtr = std::shared_ptr<Base>;

  Base() : ipaddr(""), port()
  {
  }

  Base(const std::string& _ipaddr, const int _port)
    : ipaddr(_ipaddr), port(_port)
  {
  }

  virtual std::string GetUrl() const
  {
    std::stringstream ss;
    ss << "http://" << this->ipaddr << ":" << this->port;
    return ss.str();
  }

  virtual std::string GetMethod() const = 0;

  std::string ipaddr;
  int port;
};


}  // namespace voicevox_client_cpp::request
#endif  // VOICEVOX_CLIENT_CPP_REQUEST_HPP_
