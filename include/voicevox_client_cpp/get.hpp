#ifndef VOICEVOX_CLIENT_CPP_GET_HPP_
#define VOICEVOX_CLIENT_CPP_GET_HPP_
#include <optional>

#include <cpprest/http_msg.h>

#include "voicevox_client_cpp/request.hpp"

namespace voicevox_client_cpp
{
namespace request
{
namespace get
{

class Base : public voicevox_client_cpp::request::Base
{
public:
  Base(const std::string& url)
    : voicevox_client_cpp::request::Base(url)
  {
  }

  virtual std::string GetMethod() const
  {
    return web::http::methods::GET;
  }

protected:
};

namespace speakers
{

class Request final : public voicevox_client_cpp::request::get::Base
{
public:
  Request(
      const std::string& url,
      const std::optional<int> core_version = std::nullopt)
    : Base(url),
      core_version_(core_version)
  {
  }

  std::string GetUrl() const override
  {
    std::stringstream param;
    if (core_version_ != std::nullopt)
    {
      param
        << "?core_version=" << core_version_.value();
    }

    return this->url_ + "/speakers" + param.str();
  }

private:
  const std::optional<int> core_version_;

};

}  // namespace speakers

}  // namespace request
}  // namespace get
}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_GET_HPP_
