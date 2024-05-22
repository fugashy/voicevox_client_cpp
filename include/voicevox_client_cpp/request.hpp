#ifndef VOICEVOX_CLIENT_CPP_REQUEST_HPP_
#define VOICEVOX_CLIENT_CPP_REQUEST_HPP_
namespace voicevox_client_cpp
{

namespace request
{

class Base
{
public:
  using SharedPtr = std::shared_ptr<Base>;

  Base(const std::string& url)
    : url_(url)
  {
  }

  virtual std::string GetUrl() const
  {
    return url_;
  }

  virtual std::string GetMethod() const = 0;

protected:
  const std::string url_;
};

}  // namespace request
}  // namespace voicevox_client_cpp
#endif  // VOICEVOX_CLIENT_CPP_REQUEST_HPP_
