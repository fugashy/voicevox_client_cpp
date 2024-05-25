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
 * @brief 
 *
 * @param builder
 * @param core_version
 */
void SetGetSpeakersReequestCoreVersion(
    voicevox_client_cpp::request::get::speakers::Builder* builder,
    int core_version);
}

}  // namespace speakers

namespace version
{

class Builder final : public BaseBuilder
{
public:
  Builder() : BaseBuilder("/version")
  {
    this->method(web::http::methods::GET);
  }
};

extern "C"
{
voicevox_client_cpp::request::get::version::Builder* CreateGetVersionRequestBuilder();
void DestroyGetVersionRequestBuilder(
    voicevox_client_cpp::request::get::version::Builder* builder);
}

}  // namespace version

namespace core_versions
{

class Builder final : public BaseBuilder
{
public:
  Builder() : BaseBuilder("/core_versions")
  {
    this->method(web::http::methods::GET);
  }
};

extern "C"
{
voicevox_client_cpp::request::get::core_versions::Builder* CreateGetCoreVersionsRequestBuilder();
void DestroyGetCoreVersionsRequestBuilder(
    voicevox_client_cpp::request::get::core_versions::Builder* builder);
}


}  // namespace core_versions

}  // namespace voicevox_client_cpp::request::get
#endif  // VOICEVOX_CLIENT_CPP_GET_HPP_
