#ifndef VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#define VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#include <string>
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace voicevox_client_cpp::request
{

/**
 * @brief A base class for a group of builder classes.
 */
class Builder
{
public:
  /**
   * @brief An alias of a pointer of this class
   */
  using SharedPtr = std::shared_ptr<Builder>;

  /**
   * @brief Initialize URI
   *
   * @param path The URI
   *
   * @throws std::invalid_argument is thrown if the given URI is empty.
   */
  Builder(const std::string& path) noexcept(false)
    : uri_builder_(path)
  {
    if (path.empty())
      throw std::invalid_argument("Builder requires a value represents resource name");
  }

  /**
   * @brief Create and provide a request based on the settings provided so far.
   *
   * @return The request
   */
  web::http::http_request get() noexcept
  {
    req_.set_request_uri(uri_builder_.to_uri());
    return req_;
  }

  /**
   * @brief Set HTTP method to request.
   *
   * @param method HTTP method like:
   *     web::http::method::GET,
   *     web::http::methods::POST, ...
   *
   * @return The reference of this builder
   */
  Builder& method(const web::http::method& method)
  {
    req_.set_method(method);
    return *this;
  }

  /**
   * @brief Set a header consists of a key and a value
   *
   * @param key The key of the header
   * @param value The value of the header
   *
   * @return The reference of this builder
   */
  Builder& header(const utility::string_t& key, const utility::string_t& value)
  {
    req_.headers().add(key, value);
    return *this;
  }

  /**
   * @brief Set the body of the request. (String type)
   *
   * @param body The request
   *
   * @return The reference of this builder
   */
  Builder& body(const utility::string_t& body)
  {
    req_.set_body(body);
    return *this;
  }

  /**
   * @brief Set the body of the request. (JSON type)
   *
   * @param body The request
   *
   * @return The reference of this builder
   */
  Builder& body(const web::json::value& body)
  {
    req_.set_body(body);
    return *this;
  }

protected:
  /**
   * @brief URI builder
   */
  web::http::uri_builder uri_builder_;

  /**
   * @brief The request object to be built
   */
  web::http::http_request req_;
};

}  // namespace voicevox_client_cpp::request
#endif  // VOICEVOX_CLIENT_CPP_REQUEST_HPP_
