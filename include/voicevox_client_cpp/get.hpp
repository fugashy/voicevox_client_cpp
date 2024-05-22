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

  Base(const std::string& ipaddr, const int port)
    : voicevox_client_cpp::request::Base(ipaddr, port)
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
      const std::string& ipaddr,
      const int port,
      const std::optional<int> _core_version = std::nullopt)
    : Base(ipaddr, port),
      core_version(_core_version)
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

    return Base::GetUrl() + "/speakers" + param.str();
  }

  std::optional<int> core_version;
};

class Builder final
{
public:
  Builder() : req_()
  {
  }

  Builder ipaddr(const std::string& ipaddr)
  {
    req_.ipaddr = ipaddr;
    return *this;
  }

  Builder port(const int port)
  {
    req_.port = port;
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

namespace version
{

struct Request final : public voicevox_client_cpp::request::get::Base
{
  Request()
    : Base()
  {
  }

  Request(
      const std::string& ipaddr,
      const int port)
    : Base(ipaddr, port)
  {
  }

  std::string GetUrl() const override
  {
    return Base::GetUrl() + "/version";
  }
};

class Builder final
{
public:
  Builder() : req_()
  {
  }

  Builder ipaddr(const std::string& ipaddr)
  {
    req_.ipaddr = ipaddr;
    return *this;
  }

  Builder port(const int port)
  {
    req_.port = port;
    return *this;
  }

  Request Get() const
  {
    return req_;
  }

private:
  Request req_;
};

}  // namespace version

namespace core_versions
{

struct Request final : public voicevox_client_cpp::request::get::Base
{
  Request()
    : Base()
  {
  }

  Request(
      const std::string& ipaddr,
      const int port)
    : Base(ipaddr, port)
  {
  }

  std::string GetUrl() const override
  {
    return Base::GetUrl() + "/core_versions";
  }

  std::optional<int> core_version;

};

class Builder final
{
public:
  Builder() : req_()
  {
  }

  Builder ipaddr(const std::string& ipaddr)
  {
    req_.ipaddr = ipaddr;
    return *this;
  }

  Builder port(const int port)
  {
    req_.port = port;
    return *this;
  }

  Request Get() const
  {
    return req_;
  }

private:
  Request req_;
};
}  // namespace core_versions

}  // namespace voicevox_client_cpp::request::get
#endif  // VOICEVOX_CLIENT_CPP_GET_HPP_
