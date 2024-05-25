#ifndef VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#define VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
#include <functional>
#include <memory>
#include <optional>

#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>
#include <cpprest/json.h>


namespace voicevox_client_cpp
{

namespace request
{
class Builder;
}

/**
 * @brief A client class for handlingk requests and responses to/from VOICEVOX.
 */
class Client
{
public:
  /**
   * @brief Responses from the client (in JSON format).
   */
  using OptionalJson = std::optional<web::json::value>;

  /**
   * @brief Responses from the client (in String format)
   */
  using OptionalString = std::optional<std::string>;

  /**
   * @brief User callback type
   *
   * @tparam T Response type
   */
  template<class T>
  using CallbackType = std::function<void(const T&)>;

  /**
   * @brief Copy constructor (deleted)
   *
   * @param Client
   */
  Client(const Client&) = delete;

  /**
   * @brief Copy constructor (deleted)
   *
   * @param Client
   *
   * @return 
   */
  Client& operator=(const Client&) = delete;

  /**
   * @brief The only interface for obtaining the client.
   *
   * @param uri URI of VOICEVOX
   *
   * @return An instance of the client.
   */
  static Client& GetInstance(const std::string& uri);

  /**
   * @brief An interface for sending supplies to the server and receiving responses asynchronously.
   *
   * @param req A request for the server
   * @param callback_json A function to call when processing is complete (in JSON format)
   *
   * @return A task handler
   */
  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType<OptionalJson> callback_json);

  /**
   * @brief An interface for sending a request to the server and receiving responses asynchronously.
   *
   * @param req A request for the server
   * @param callback_json A function to call when processing is complete (in String format)
   *
   * @return A task handler
   */
  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType<OptionalString> callback_audio);

  /**
   * @brief An interface for sending requests to the server and receiving responses synchronously.
   *
   * @tparam T The response type
   * @param req The request for the server
   *
   * @return The response
   */
  template<class T>
  T Request(const web::http::http_request& req)
  {
    T out;
    auto callback = [&out](const T& in) { out = in; };
    auto task = Request(req, callback);
    task.wait();
    return out;
  }

private:
  /**
   * @brief Constructor
   *
   * @param uri A URI of the server
   */
  Client(const std::string& uri);

  /**
   * @brief Destructor
   */
  ~Client() = default;

  /**
   * @brief A client object
   */
  std::unique_ptr<web::http::client::http_client> client_;
};

extern "C"
{
Client* GetClientInstance(const char* uri);
const char* RequestJsonString(
    Client* client,
    request::Builder* req_builder);
const char* RequestString(
    Client* client,
    request::Builder* req_builder);
void FreeString(const char* str);
}  // extern "C"

}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_CLIEHT_HPP_
