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

pplx::task<void> Client::Request(
    const web::http::http_request& req,
    const CallbackType<OptionalJson> callback)
{
  return pplx::create_task(
      [this, req, callback]()
      {
        return this->client_->request(req);
      })
    .then(
        [callback](const web::http::http_response& res)
        {
          if (res.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "Unexpected status code" << std::endl;
            callback(std::nullopt);
            return;
          }

          const auto content_type = res.headers().content_type();
          if (content_type == "application/json")
          {
            const web::json::value json = res.extract_json().get();
            callback(json);
          }
          else
          {
            std::cerr << "Unknown content type: " << content_type << std::endl;
            callback(web::json::value());
          }
        });
}

pplx::task<void> Client::Request(
    const web::http::http_request& req,
    const CallbackType<OptionalString> callback)
{
  return pplx::create_task(
      [this, req, callback]()
      {
        return this->client_->request(req);
      })
    .then(
        [callback](const web::http::http_response& res)
        {
          if (res.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "Unexpected status code" << std::endl;
            callback(std::nullopt);
            return;
          }

          const auto content_type = res.headers().content_type();
          if (content_type == "audio/wav")
          {
            const std::string output_path = "/tmp/output.wav";
            auto file_buffer = Concurrency::streams::file_stream<uint8_t>::open_ostream(
                U(output_path)).get();
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
            callback(output_path);
          }
          else
          {
            std::cerr << "Unknown content type: " << content_type << std::endl;
            callback(std::nullopt);
          }
        });
}

extern "C"
{
/* get speakers */
__attribute__((visibility("default")))
Client* GetClientInstance(const char* uri)
{
  return &(Client::GetInstance(uri));
}

const char* RequestJsonString(
    Client* client,
    request::Builder* req_builder)
{
  Client::OptionalJson out = client->Request<Client::OptionalJson>(req_builder->get());
  if (out == std::nullopt) return NULL;

  const std::string str = out.value().as_string();
  char* cstr = new char[str.size() + 1];
  std::strcpy(cstr, str.c_str());
  return cstr;
}

const char* RequestString(
    Client* client,
    request::Builder* req_builder)
{
  Client::OptionalString out = client->Request<Client::OptionalString>(req_builder->get());
  if (out == std::nullopt) return NULL;

  char* cstr = new char[out.value().size() + 1];
  std::strcpy(cstr, out.value().c_str());
  return cstr;
}

void FreeString(const char* str)
{
  delete[] str;
}

}  // extern "C"

}  // namespace voicevox_client_cpp
