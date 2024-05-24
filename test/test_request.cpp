#include <string>
#include <gtest/gtest.h>
#include "voicevox_client_cpp/request.hpp"

using voicevox_client_cpp::request::Builder;


TEST(BuilderTest, Constructor)
{
  // setup
  const std::string uri = "some_resource";
  Builder::SharedPtr target;

  // exercise end verify
  ASSERT_NO_THROW(target.reset(new Builder(uri)));

  // teardown
  // nothing to do
}

TEST(BuilderTest, EmptyParamConstructor)
{
  // setup
  const std::string uri = "";
  Builder::SharedPtr target;

  // exercise end verify
  ASSERT_THROW(target.reset(new Builder(uri)), std::invalid_argument);

  // teardown
  // nothing to do
}

TEST(BuilderTest, GetInitialProperties)
{
  // setup
  const std::string uri = "some_resource";
  Builder::SharedPtr target(new Builder(uri));

  // exercise
  const auto out = target->get();

  // verify
  EXPECT_STREQ(web::http::methods::GET.c_str(), out.method().c_str());
  EXPECT_STREQ(uri.c_str(), out.request_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.relative_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.absolute_uri().to_string().c_str());
  const web::http::http_headers& headers = out.headers();
  EXPECT_EQ(0, headers.size());
  EXPECT_TRUE(headers.empty());
  const web::http::http_version& http_version = out.http_version();
  EXPECT_EQ(0, http_version.major);
  EXPECT_EQ(0, http_version.minor);
  EXPECT_TRUE(out.remote_address().empty());

  // teardown
  // nothing to do
}

TEST(BuilderTest, SetMethodThenGet)
{
  // setup
  const std::string uri = "some_resource";
  const web::http::method method = web::http::methods::POST;
  Builder::SharedPtr target(new Builder(uri));

  // exercise
  const auto out = target->method(method).get();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), out.method().c_str());
  EXPECT_STREQ(uri.c_str(), out.request_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.relative_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.absolute_uri().to_string().c_str());
  const web::http::http_headers& headers = out.headers();
  EXPECT_EQ(0, headers.size());
  EXPECT_TRUE(headers.empty());
  const web::http::http_version& http_version = out.http_version();
  EXPECT_EQ(0, http_version.major);
  EXPECT_EQ(0, http_version.minor);
  EXPECT_TRUE(out.remote_address().empty());

  // teardown
  // nothing to do
}

TEST(BuilderTest, SetHeaderThenGet)
{
  // setup
  const std::string uri = "some_resource";
  const web::http::method method = web::http::methods::POST;
  const std::pair<utility::string_t, utility::string_t> header = {
    "Content-Type", "audio/wav"};
  Builder::SharedPtr target(new Builder(uri));

  // exercise
  const auto out = target
    ->method(method)
    .header(header.first, header.second)
    .get();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), out.method().c_str());
  EXPECT_STREQ(uri.c_str(), out.request_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.relative_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.absolute_uri().to_string().c_str());
  web::http::http_headers headers = out.headers();
  EXPECT_EQ(1, headers.size());
  EXPECT_TRUE(headers.has(header.first));
  EXPECT_STREQ(header.second.c_str(), headers[header.first.c_str()].c_str());
  const web::http::http_version& http_version = out.http_version();
  EXPECT_EQ(0, http_version.major);
  EXPECT_EQ(0, http_version.minor);
  EXPECT_TRUE(out.remote_address().empty());

  // teardown
  // nothing to do
}


TEST(BuilderTest, SetBodyAsStringThenGet)
{
  // setup
  const std::string uri = "some_resource";
  const web::http::method method = web::http::methods::POST;
  const std::pair<utility::string_t, utility::string_t> header = {
    "Content-Type", "audio/wav"};
  const std::string body = "{\"test\":\"hoge\"}";
  Builder::SharedPtr target(new Builder(uri));

  // exercise
  const auto out = target
    ->method(method)
    .header(header.first, header.second)
    .body(body)
    .get();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), out.method().c_str());
  EXPECT_STREQ(uri.c_str(), out.request_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.relative_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.absolute_uri().to_string().c_str());
  web::http::http_headers headers = out.headers();
  /*
  for (auto it = headers.begin(); it != headers.end(); ++it)
  {
    std::cout << it->first << ":" << it->second << std::endl;
  }
  */
  EXPECT_EQ(2, headers.size());  // automatically append a header about the content length
  EXPECT_TRUE(headers.has(header.first));
  EXPECT_STREQ(header.second.c_str(), headers[header.first.c_str()].c_str());
  const web::http::http_version& http_version = out.http_version();
  EXPECT_EQ(0, http_version.major);
  EXPECT_EQ(0, http_version.minor);
  EXPECT_TRUE(out.remote_address().empty());

  // teardown
  // nothing to do
}


TEST(BuilderTest, SetBodyAsJsonThenGet)
{
  // setup
  const std::string uri = "some_resource";
  const web::http::method method = web::http::methods::POST;
  const std::pair<utility::string_t, utility::string_t> header = {
    "Content-Type", "audio/wav"};
  web::json::value json;
  json["name"] = web::json::value::string("fugashy");
  Builder::SharedPtr target(new Builder(uri));

  // exercise
  const auto out = target
    ->method(method)
    .header(header.first, header.second)
    .body(json)
    .get();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), out.method().c_str());
  EXPECT_STREQ(uri.c_str(), out.request_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.relative_uri().to_string().c_str());
  EXPECT_STREQ(uri.c_str(), out.absolute_uri().to_string().c_str());
  web::http::http_headers headers = out.headers();
  EXPECT_EQ(2, headers.size());  // automatically append a header about the content length
  EXPECT_TRUE(headers.has(header.first));
  EXPECT_STREQ(header.second.c_str(), headers[header.first.c_str()].c_str());
  const web::http::http_version& http_version = out.http_version();
  EXPECT_EQ(0, http_version.major);
  EXPECT_EQ(0, http_version.minor);
  EXPECT_TRUE(out.remote_address().empty());

  // teardown
  // nothing to do
}
