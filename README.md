# voicevox_client_cpp

![build-document](https://github.com/fugashy/voicevox_client_cpp/actions/workflows/build_document.yml/badge.svg)
![run-tests](https://github.com/fugashy/voicevox_client_cpp/actions/workflows/run_test.yml/badge.svg)

An *Unofficial* client library for VOICEVOX implemented in C++.

It also provides an interface for calling from other languages. *Still under testing*

[Link to the Document](https://fugashy.github.io/voicevox_client_cpp/index.html)

# Required

- C++ 17
- cpprestsdk

# Supported OS

- Ubuntu 24.04
- masOS Sonoma 14.5

# How to build and install

```bash
# for Ubuntu
sudo apt install libcpprest-dev
# for macOS
brew install cpprestsdk

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

  // Here's an example using a synchronous interface to obtain responses.
  // It sends requests in the following order: speech query creation request,
  // followed by a speech synthesis request.

  // Build a request to create a speech query then send it.
  const web::http::http_request req_audio_query = ReqAudioQueryBuilder()
       .text(text)
       .speaker(3)
       .get();
  const auto json = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalJson>(req_audio_query);

  // Build a request for speech synthesis then send it.
  const web::http::http_request req_synthesis = ReqSynthesisBuilder()
      .speaker(3)
      .enable_interrogative_upspeak(false)
      .accent_phrases(json.value())
      .get();
  const auto string = voicevox_client_cpp::Client::GetInstance("http://localhost:50021")
    .Request<voicevox_client_cpp::Client::OptionalString>(req_synthesis);
  std::cout << "saved audio file path: " << string.value() << std::endl;

  // Please refer to the file below for information on the interface for obtaining responses asynchronously.
  // - src/voicevox_client_cpp/sample/post_audio_query_then_synthesis.cpp

  return EXIT_SUCCESS;
}
```

# How to use samples

```bash
# Please run the voicevox server before execution of following commands.

docker run \
  -it \
  --rm \
  --net host \
  --volume /tmp:/tmp:rw \
  vvccpp:24.04 voicevox_client_cpp_sample_post_audio_query_then_synthesis

> input: こんにちは
> received audio size: 50732
> audio file size: 50732

# Please see /tmp then you can find wav files named like yyyymmddhhMMss-koNnichiwa.wav
# 2 files are output because the sample requests 2 queries using sync method and async method.
```
