#ifndef VOICEVOX_CLIENT_CPP_POST_HPP_
#define VOICEVOX_CLIENT_CPP_POST_HPP_
#include <optional>

#include <cpprest/http_msg.h>

#include "voicevox_client_cpp/request.hpp"

namespace voicevox_client_cpp::request::post
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

  virtual std::string GetMethod() const final
  {
    return web::http::methods::POST;
  }
};

namespace audio_query
{

struct Request final : public voicevox_client_cpp::request::post::Base
{
  Request()
    : Base(),
      text(""),
      speaker(),
      core_version(std::nullopt)
  {
  }

  Request(
      const std::string& ipaddr,
      const int port,
      const std::string& _text,
      const int _speaker,
      const std::optional<int> _core_version = std::nullopt)
    : Base(ipaddr, port),
      text(_text),
      speaker(_speaker),
      core_version(_core_version)
  {
  }

  std::string GetUrl() const override
  {
    std::stringstream param;
    param << "?text=" << this->Encode(this->text);
    param << "&speaker=" << this->speaker;
    if (this->core_version != std::nullopt)
    {
      param
        << "?core_version=" << this->core_version.value();
    }

    return Base::GetUrl() + "/audio_query" + param.str();
  }

  web::json::value GetBody() const override final
  {
    // no body to be required
    return web::json::value();
  }

  std::string text;
  int speaker;
  std::optional<int> core_version;

private:
  std::string Encode(const std::string& str) const
  {
    std::ostringstream encoded;
    encoded << std::hex << std::uppercase;
    for (char c : str)
    {
      if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~')
      {
        encoded << c;
      }
      else
      {
        encoded
          << '%'
          << std::setw(2)
          << std::setfill('0')
          << static_cast<int>(static_cast<unsigned char>(c));
      }
    }
    return encoded.str();
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

  Builder text(const std::string& text)
  {
    req_.text = text;
    return *this;
  }

  Builder speaker(const int speaker)
  {
    req_.speaker = speaker;
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

}  // namespace audio_query

namespace synthesis
{

struct Request final : public voicevox_client_cpp::request::post::Base
{
  Request()
    : Base(),
      speaker(0),
      enable_interrogative_upspeak(false),
      accent_phrases(web::json::value())
  {
  }

  Request(
      const std::string& ipaddr,
      const int port,
      const int _speaker,
      const bool _enable_interrogative_upspeak,
      const web::json::value& _accent_phrases)
    : Base(ipaddr, port),
      speaker(_speaker),
      enable_interrogative_upspeak(_enable_interrogative_upspeak),
      accent_phrases(_accent_phrases)
  {
  }

  std::string GetUrl() const override
  {
    std::stringstream param;
    param << "?speaker=" << this->speaker;
    if (this->enable_interrogative_upspeak)
    {
      param << "&enable_interrogative_upspeak=true";
    }
    else
    {
      param << "&enable_interrogative_upspeak=false";
    }
    if (this->core_version != std::nullopt)
    {
      param
        << "?core_version=" << this->core_version.value();
    }

    return Base::GetUrl() + "/synthesis" + param.str();
  }

  web::json::value GetBody() const override final
  {
    return this->accent_phrases;
  }

  int speaker;
  bool enable_interrogative_upspeak;
  std::optional<int> core_version;
  web::json::value accent_phrases;
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

  Builder speaker(const int speaker)
  {
    req_.speaker = speaker;
    return *this;
  }

  Builder enable_interrogative_upspeak(const bool enable_interrogative_upspeak)
  {
    req_.enable_interrogative_upspeak = enable_interrogative_upspeak;
    return *this;
  }

  Builder core_version(const std::optional<int>& core_version)
  {
    req_.core_version = core_version;
    return *this;
  }

  Builder accent_phrases(const web::json::value& accent_phrases)
  {
    req_.accent_phrases = accent_phrases;
    return *this;
  }

  Request Get() const
  {
    return req_;
  }

private:
  Request req_;
};

}  // namespace synthesis


}  // namespace voicevox_client_cpp::request::post
#endif  // VOICEVOX_CLIENT_CPP_POST_HPP_
