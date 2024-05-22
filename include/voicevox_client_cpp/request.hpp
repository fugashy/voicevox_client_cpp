#ifndef VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#define VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#include <string>
#include <memory>

namespace voicevox_client_cpp::request
{

struct Base
{
  using SharedPtr = std::shared_ptr<Base>;

  Base() : url("")
  {
  }

  Base(const std::string& url)
    : url(url)
  {
  }

  virtual std::string GetUrl() const
  {
    return url;
  }

  virtual std::string GetMethod() const = 0;

  std::string url;
};


}  // namespace voicevox_client_cpp::request
#endif  // VOICEVOX_CLIENT_CPP_REQUEST_HPP_
