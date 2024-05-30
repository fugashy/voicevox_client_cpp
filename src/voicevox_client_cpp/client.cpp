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
    const CallbackType<OptionalBinary> callback)
{
  return pplx::create_task(
      [this, req, callback]()
      {
        return this->client_->request(req);
      }).then([callback](const web::http::http_response& res)
        {
          if (res.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "Unexpected status code" << std::endl;
            return std::vector<unsigned char>();
          }
          const auto content_type = res.headers().content_type();
          if (content_type != "audio/wav")
          {
            std::cerr << "Unexpected content type: " << content_type << std::endl;
            return std::vector<unsigned char>();
          }
          auto vector_task = res.extract_vector();
          vector_task.wait();
          return vector_task.get();
        }).then([callback](const std::vector<unsigned char>& data)
          {
            if (data.empty())
            {
              callback(std::nullopt);
              return;
            }

            callback(data);
            std::ofstream outfile("/tmp/output.wav", std::ios::binary);
            outfile.write(
                reinterpret_cast<const char*>(data.data()), data.size());
            outfile.close();
            return;
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
  Client::OptionalBinary out = client->Request<Client::OptionalBinary>(req_builder->get());
  if (out == std::nullopt) return NULL;

  char* cstr = new char[out.value().size() + 1];
  std::copy(out.value().begin(), out.value().end(), cstr);
  return cstr;
}

void FreeString(const char* str)
{
  delete[] str;
}

}  // extern "C"

}  // namespace voicevox_client_cpp
