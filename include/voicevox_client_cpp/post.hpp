#ifndef VOICEVOX_CLIENT_CPP_POST_HPP_
#define VOICEVOX_CLIENT_CPP_POST_HPP_
#include <optional>

#include "voicevox_client_cpp/request.hpp"

/**
 * @brief An alias for the base builder.
 */
using BaseBuilder = voicevox_client_cpp::request::Builder;

namespace voicevox_client_cpp::request::post
{

namespace audio_query
{

/**
 * @brief A builder for creating requests to obtain audio_query.
 */
class Builder final : public BaseBuilder
{
public:
  /**
   * @brief Initialize base URI
   */
  Builder() : BaseBuilder("/audio_query")
  {
    this->method(web::http::methods::POST);
  }

  /**
   * @brief Set the text to be used for the query to synthesize Japanese speech.
   *
   * @param text A string to be used for synthesization
   *
   * @return The reference for this builder
   */
  Builder& text(const utility::string_t& text)
  {
    this->uri_builder_.append_query("text", text);
    return *this;
  }

  /**
   * @brief Set the speaker ID to be used for the query to synthesize Japanese speech.
   *
   * @param speaker A speaker ID value
   *
   * @return The reference for this builder
   */
  Builder& speaker(const int speaker)
  {
    this->uri_builder_.append_query("speaker", speaker);
    return *this;
  }

  /**
   * @brief Set core_version to the request
   *
   * @param core_version core_version of the engine.
   *
   * @return This builder
   */
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
/**
 * @brief Get a pointer to the builder for creating a request to obtain audio query.
 *
 * @return A pointer to the builder
 */
voicevox_client_cpp::request::post::audio_query::Builder* CreatePostAudioQueryRequestBuilder();

/**
 * @brief Delete the builder for getting audio auery.
 *
 * @param builder A pointer to the builder
 */
void DestroyPostAudioQueryRequestBuilder(
    voicevox_client_cpp::request::post::audio_query::Builder* builder);

/**
 * @brief Set the text to be used for the query to synthesize Japanese speech.
 *
 * @param builder A builder of the request
 * @param text A string to be used for synthesization
 */
void SetPostAudioQueryRequestText(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const char* text);

/**
 * @brief Set the speaker ID to be used for the query to synthesize Japanese speech.
 *
 * @param builder A pointer to the builder
 * @param speaker A speaker ID value
 */
void SetPostAudioQueryRequestSpeaker(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int speaker);

/**
 * @brief Set cove_version value to request
 *
 * @param builder A builder of the request
 * @param core_version A value of core_version
 */
void SetPostAudioQueryRequestCoreVersion(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int core_version);
}

}  // namespace audio_query

namespace synthesis
{

/**
 * @brief A builder for creating requests to obtain audio_query.
 */
class Builder final : public BaseBuilder
{
public:
  /**
   * @brief Initialize base URI and headers
   */
  Builder() : BaseBuilder("/synthesis")
  {
    this
      ->method(web::http::methods::POST)
      .header("accept", "audio/wav")
      .header("Content-Type", "application/json");
  }

  /**
   * @brief Set the speaker ID to be used for the query to synthesize Japanese speech.
   *
   * @param speaker A speaker ID value
   *
   * @return The reference for this builder
   */
  Builder& speaker(const int speaker)
  {
    this->uri_builder_.append_query("speaker", speaker);
    return *this;
  }

  /**
   * @brief Set a flag to control whether to raise the intonation at the end when it's a question.
   *
   * @param enable_interrogative_upspeak The flag
   *
   * @return The reference for this builder
   */
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

  /**
   * @brief Set the query for speech synthesis included in the response body of the audio_query request.
   *
   * @param accent_phrases The audio query (JSON type)
   *
   * @return The reference for this builder
   */
  Builder& accent_phrases(const web::json::value& accent_phrases)
  {
    this->body(accent_phrases);
    return *this;
  }

  /**
   * @brief Set the query for speech synthesis included in the response body of the audio_query request.
   *
   * @param accent_phrases The audio query (String type)
   *
   * @return The reference for this builder
   */
  Builder& accent_phrases(const char* accent_phrases)
  {
    this->body(accent_phrases);
    return *this;
  }

  /**
   * @brief Set core_version to the request
   *
   * @param core_version core_version of the engine.
   *
   * @return This builder
   */
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
/**
 * @brief Get a pointer to the builder for creating a request to obtain synthesized data.
 *
 * @return A pointer to the builder
 */
voicevox_client_cpp::request::post::synthesis::Builder* CreatePostSynthesisRequestBuilder();

/**
 * @brief Delete the builder for getting synthesized data.
 *
 * @param builder A pointer to the builder
 */
void DestroyPostSynthesisRequestBuilder(
    voicevox_client_cpp::request::post::synthesis::Builder* builder);

/**
 * @brief Set the speaker ID to be used for the query to synthesize Japanese speech.
 *
 * @param builder A builder of the request
 * @param speaker A speaker ID value
 */
void SetPostSynthesisRequestSpeaker(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int speaker);

/**
 * @brief Set a flag to control whether to raise the intonation at the end when it's a question.
 *
 * @param builder A builder of the request
 * @param enable_interrogative_upspeak The flag
 */
void SetPostSynthesisRequestEnableInterrogativeUpspeak(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const bool enable_interrogative_upspeak);

/**
 * @brief Set the query for speech synthesis included in the response body of the audio_query request.
 *
 * @param builder A builder of the request
 * @param accent_phrases The audio query(string)
 */
void SetPostSynthesisRequestAccentPhrases(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const char* accent_phrases);

/**
 * @brief Set cove_version value to request
 *
 * @param builder A builder of the request
 * @param core_version A value of core_version
 */
void SetPostSynthesisRequestCoreVersion(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int core_version);
}  // extern "C"

}  // namespace synthesis
}  // namespace voicevox_client_cpp::request::post
#endif  // VOICEVOX_CLIENT_CPP_POST_HPP_
