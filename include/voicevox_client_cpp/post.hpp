#ifndef VOICEVOX_CLIENT_CPP_POST_HPP_
#define VOICEVOX_CLIENT_CPP_POST_HPP_
#include <optional>

#include "voicevox_client_cpp/request.hpp"

using BaseBuilder = voicevox_client_cpp::request::Builder;

namespace voicevox_client_cpp::request::post
{

namespace audio_query
{

class Builder final : public BaseBuilder
{
public:
  Builder() : BaseBuilder("/audio_query")
  {
    this->method(web::http::methods::POST);
  }

  Builder& text(const utility::string_t& text)
  {
    this->uri_builder_.append_query("text", text);
    return *this;
  }

  Builder& speaker(const int speaker)
  {
    this->uri_builder_.append_query("speaker", speaker);
    return *this;
  }

  Builder& core_version(const std::optional<int>& core_version)
  {
    if (core_version != std::nullopt)
    {
      this->uri_builder_.append_query("core_version", core_version.value());
    }
    return *this;
  }

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

}  // namespace audio_query

namespace synthesis
{

class Builder final : public BaseBuilder
{
public:
  Builder() : BaseBuilder("/synthesis")
  {
    this
      ->method(web::http::methods::POST)
      .header("accept", "audio/wav")
      .header("Content-Type", "application/json");
  }

  Builder& speaker(const int speaker)
  {
    this->uri_builder_.append_query("speaker", speaker);
    return *this;
  }

  Builder& enable_interrogative_upspeak(const bool enable_interrogative_upspeak)
  {
    if (enable_interrogative_upspeak)
    {
      this->uri_builder_.append_query("enable_interrogative_upspeak", "true");
    }
    else
    {
      this->uri_builder_.append_query("enable_interrogative_upspeak", "false");
    }
    return *this;
  }

  Builder& accent_phrases(const web::json::value& json)
  {
    this->body(json);
    return *this;
  }

  Builder& core_version(const std::optional<int>& core_version)
  {
    if (core_version != std::nullopt)
    {
      const utility::string_t& uri = req_.request_uri().path();
      std::stringstream ss;
      ss << uri << "?core_version=" << core_version.value();
      this->uri(ss.str());
    }
    return *this;
  }
};

}  // namespace synthesis


}  // namespace voicevox_client_cpp::request::post
#endif  // VOICEVOX_CLIENT_CPP_POST_HPP_
