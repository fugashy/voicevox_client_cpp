#ifndef VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#define VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#include <string>
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace voicevox_client_cpp::request
{

class Builder
{
public:
  using SharedPtr = std::shared_ptr<Builder>;

  Builder(const std::string& path) noexcept(false)
    : uri_builder_(path)
  {
    if (path.empty())
      throw std::invalid_argument("Builder requires a value represents resource name");
  }

  web::http::http_request get() noexcept
  {
    req_.set_request_uri(uri_builder_.to_uri());
    return req_;
  }

  Builder& method(const web::http::method& method)
  {
    req_.set_method(method);
    return *this;
  }

  Builder& header(const utility::string_t& key, const utility::string_t& value)
  {
    req_.headers().add(key, value);
    return *this;
  }

  Builder& body(const utility::string_t& body)
  {
    req_.set_body(body);
    return *this;
  }

  Builder& body(const web::json::value& body)
  {
    req_.set_body(body);
    return *this;
  }

protected:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

}  // namespace voicevox_client_cpp::request
#endif  // VOICEVOX_CLIENT_CPP_REQUEST_HPP_
