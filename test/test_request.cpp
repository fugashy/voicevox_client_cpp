#include <string>

#include <gtest/gtest.h>

#include "voicevox_client_cpp/request.hpp"

using voicevox_client_cpp::request::Builder;


TEST(BuilderTest, Constructor)
{
  // setup
  const std::string uri = "http://localhost:50021";
  Builder::SharedPtr target;


  // exercise end verify
  ASSERT_NO_THROW(target.reset(new Builder(uri)));

  // teardown
  // nothing to do
}
