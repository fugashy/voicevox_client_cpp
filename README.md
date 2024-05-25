# voicevox_client_cpp

A client library for VOICEVOX implemented in C++.

It also provides an interface for calling from other languages. (Still under testing)

# Required

- C++ 17
- cpprestsdk

# How to build and install

```bash
mkdir build
cd build
cmake ..

# build
make

# install
sudo make install
```

# How to build the docker image

```bash
docker build -t vvccpp:latest .
```

# A sample code for speech synthesis

```cpp
#include "voicevox_client_cpp/client.hpp"
#include "voicevox_client_cpp/post.hpp"

#include <iostream>

using ReqAudioQueryBuilder = voicevox_client_cpp::request::post::audio_query::Builder;
using ReqSynthesisBuilder = voicevox_client_cpp::request::post::synthesis::Builder;

int main(int argc, char** argv)
{
  // default text to synthesis
  std::string text = "こんにちは";
  if (argc > 1)
  {
    text = argv[1];
  }
  std::cout << "input: " << text << std::endl;

  // Build a request to create a speech query.
  const web::http::http_request req_audio_query = ReqAudioQueryBuilder()
       .text(text)
       .speaker(3)
       .get();

  // Build a request for speech synthesis.
  const web::http::http_request req_synthesis = ReqSynthesisBuilder()
      .speaker(3)
      .enable_interrogative_upspeak(false)
      .accent_phrases(json.value())
      .get();

  // Here's an example using a synchronous interface to obtain responses.
  // It sends requests in the following order: speech query creation request,
  // followed by a speech synthesis request.
  const auto json = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalJson>(req_audio_query);
  const auto string = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalString>(req_synthesis);
  std::cout << "saved audio file path: " << string.value() << std::endl;

  // Please refer to the file below for information on the interface for obtaining responses asynchronously.
  // - src/voicevox_client_cpp/sample/post_audio_query_then_synthesis.cpp

  return EXIT_SUCCESS;
}
```
