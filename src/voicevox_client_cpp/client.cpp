#include "voicevox_client_cpp/client.hpp"

#include <string>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "voicevox_client_cpp/request.hpp"


namespace voicevox_client_cpp
{

Client& Client::GetInstance(const std::string& uri)
{
  static Client instance(uri);
  return instance;
}

Client::Client(const std::string& uri)
  : client_(new web::http::client::http_client(uri))
{
}

void Client::Request(const web::http::http_request& req, const CallbackType callback)
{
  this->client_->request(req)
    .then(
        [callback](const web::http::http_response& res)
        {
          if (res.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "Unexpected status code" << std::endl;
            callback(web::json::value());
            return;
          }

          const auto content_type = res.headers().content_type();
          if (content_type == "application/json")
          {
            const web::json::value json = res.extract_json().get();
            callback(json);
          }
          else if (content_type == "audio/wav")
          {
            auto file_buffer = Concurrency::streams::file_stream<uint8_t>::open_ostream(
                U("/tmp/output.wav")).get();
            res.body().read_to_end(file_buffer.streambuf())
              .then(
                  [file_buffer](size_t)
                  {
                    file_buffer.close()
                      .then(
                          []
                          {
                            std::cout << U("Audio file saved successfully.") << std::endl;
                          }).wait();
            }).wait();
            callback(web::json::value());
          }
          else
          {
            std::cerr << "Unknown content type: " << content_type << std::endl;
            callback(web::json::value());
          }
        }).wait();
}


}  // namespace voicevox_client_cpp
