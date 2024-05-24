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
};

extern "C"
{
voicevox_client_cpp::request::post::audio_query::Builder* CreatePostAudioQueryRequestBuilder();
void DestroyPostAudioQueryRequestBuilder(
    voicevox_client_cpp::request::post::audio_query::Builder* builder);
void SetPostAudioQueryRequestText(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const char* text);
void SetPostAudioQueryRequestSpeaker(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int speaker);
void SetPostAudioQueryRequestCoreVersion(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int core_version);
}

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

  Builder& accent_phrases(const web::json::value& accent_phrases)
  {
    this->body(accent_phrases);
    return *this;
  }

  Builder& accent_phrases(const char* accent_phrases)
  {
    this->body(accent_phrases);
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
};

extern "C"
{
voicevox_client_cpp::request::post::synthesis::Builder* CreatePostSynthesisRequestBuilder();
void DestroyPostSynthesisRequestBuilder(
    voicevox_client_cpp::request::post::synthesis::Builder* builder);
void SetPostSynthesisRequestSpeaker(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int speaker);
void SetPostSynthesisRequestEnableInterrogativeUpspeak(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const bool enable_interrogative_upspeak);
void SetPostSynthesisRequestAccentPhrases(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const char* accent_phrases);
void SetPostSynthesisRequestCoreVersion(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int core_version);
}  // extern "C"

}  // namespace synthesis
}  // namespace voicevox_client_cpp::request::post
#endif  // VOICEVOX_CLIENT_CPP_POST_HPP_
