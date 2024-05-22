#ifndef VOICEVOX_CLIENT_CPP_GET_HPP_
#define VOICEVOX_CLIENT_CPP_GET_HPP_
#include <optional>

#include <cpprest/http_msg.h>

#include "voicevox_client_cpp/request.hpp"

namespace voicevox_client_cpp::request::get
{

struct Base : public voicevox_client_cpp::request::Base
{
  Base()
    : voicevox_client_cpp::request::Base()
  {
  }

  Base(const std::string& url)
    : voicevox_client_cpp::request::Base(url)
  {
  }

  virtual std::string GetMethod() const
  {
    return web::http::methods::GET;
  }
};

namespace speakers
{

struct Request final : public voicevox_client_cpp::request::get::Base
{
  Request()
    : Base(),
      core_version(std::nullopt)
  {
  }

  Request(
      const std::string& url,
      const std::optional<int> core_version = std::nullopt)
    : Base(url),
      core_version(core_version)
  {
  }

  std::string GetUrl() const override
  {
    std::stringstream param;
    if (this->core_version != std::nullopt)
    {
      param
        << "?core_version=" << this->core_version.value();
    }

    return this->url + "/speakers" + param.str();
  }

  std::optional<int> core_version;
};

class Builder final
{
public:
  Builder() : req_()
  {
  }

  Builder url(const std::string& url)
  {
    req_.url = url;
    return *this;
  }

  Builder core_version(const std::optional<int>& core_version)
  {
    req_.core_version = core_version;
    return *this;
  }

  Request Get() const
  {
    return req_;
  }

private:
  Request req_;
};

}  // namespace speakers

}  // namespace voicevox_client_cpp::request::get
#endif  // VOICEVOX_CLIENT_CPP_GET_HPP_
