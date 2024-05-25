#ifndef VOICEVOX_CLIENT_CPP_GET_HPP_
#define VOICEVOX_CLIENT_CPP_GET_HPP_
#include <optional>

#include <cpprest/http_msg.h>

#include "voicevox_client_cpp/request.hpp"

/**
 * @brief An alias for the base builder.
 */
using BaseBuilder = voicevox_client_cpp::request::Builder;

namespace voicevox_client_cpp::request::get
{

namespace speakers
{

/**
 * @brief A builder for creating requests to obtain speakers.
 */
class Builder final : public BaseBuilder
{
public:
  /**
   * @brief Initialize base URI
   */
  Builder() : BaseBuilder("/speakers")
  {
    this->method(web::http::methods::GET);
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
 * @brief Get a pointer to the builder for creating a request to obtain speakers.
 *
 * @return A pointer to the builder
 */
voicevox_client_cpp::request::get::speakers::Builder* CreateGetSpeakersRequestBuilder();

/**
 * @brief Delete the builder for getting speakers.
 *
 * @param builder A pointer to the builder
 */
void DestroyGetSpeakersRequestBuilder(
    voicevox_client_cpp::request::get::speakers::Builder* builder);

/**
 * @brief Set cove_version value to request
 *
 * @param builder A builder of the request
 * @param core_version A value of core_version
 */
void SetGetSpeakersReequestCoreVersion(
    voicevox_client_cpp::request::get::speakers::Builder* builder,
    int core_version);
}

}  // namespace speakers

namespace version
{

/**
 * @brief A builder for creating requests to obtain version.
 */
class Builder final : public BaseBuilder
{
public:
  /**
   * @brief Initialize base URI
   */
  Builder() : BaseBuilder("/version")
  {
    this->method(web::http::methods::GET);
  }
};

extern "C"
{
/**
 * @brief Get a pointer to the builder for creating a request to obtain version.
 *
 * @return A pointer to the builder
 */
voicevox_client_cpp::request::get::version::Builder* CreateGetVersionRequestBuilder();

/**
 * @brief Delete the builder for getting speakers.
 *
 * @param builder A pointer to the builder
 */
void DestroyGetVersionRequestBuilder(
    voicevox_client_cpp::request::get::version::Builder* builder);
}

}  // namespace version

namespace core_versions
{

/**
 * @brief A builder for creating requests to obtain core_version.
 */
class Builder final : public BaseBuilder
{
public:
  /**
   * @brief Initialize base URI
   */
  Builder() : BaseBuilder("/core_versions")
  {
    this->method(web::http::methods::GET);
  }
};

extern "C"
{
/**
 * @brief Get a pointer to the builder for creating a request to obtain core_version.
 *
 * @return A pointer to the builder
 */
voicevox_client_cpp::request::get::core_versions::Builder* CreateGetCoreVersionsRequestBuilder();

/**
 * @brief Delete the builder for getting core_versions.
 *
 * @param builder A pointer to the builder
 */
void DestroyGetCoreVersionsRequestBuilder(
    voicevox_client_cpp::request::get::core_versions::Builder* builder);
}


}  // namespace core_versions

}  // namespace voicevox_client_cpp::request::get
#endif  // VOICEVOX_CLIENT_CPP_GET_HPP_
