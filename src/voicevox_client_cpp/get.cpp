#include "voicevox_client_cpp/get.hpp"


extern "C"
{

/* get speakers */
__attribute__((visibility("default")))
voicevox_client_cpp::request::get::speakers::Builder* CreateGetSpeakersRequestBuilder()
{
  return new voicevox_client_cpp::request::get::speakers::Builder();
}

__attribute__((visibility("default")))
void DestroyGetSpeakersRequestBuilder(
    voicevox_client_cpp::request::get::speakers::Builder* builder)
{
  delete builder;
}

__attribute__((visibility("default")))
void SetGetSpeakersReequestCoreVersion(
    voicevox_client_cpp::request::get::speakers::Builder* builder,
    int core_version)
{
  builder->core_version(core_version);
}

/* get version */
__attribute__((visibility("default")))
voicevox_client_cpp::request::get::version::Builder* CreateGetVersionRequestBuilder()
{
  return new voicevox_client_cpp::request::get::version::Builder();
}

__attribute__((visibility("default")))
void DestroyGetVersionRequestBuilder(
    voicevox_client_cpp::request::get::version::Builder* builder)
{
  delete builder;
}

/* get core versions */
__attribute__((visibility("default")))
voicevox_client_cpp::request::get::core_versions::Builder* CreateGetCoreVersionsRequestBuilder()
{
  return new voicevox_client_cpp::request::get::core_versions::Builder();
}

__attribute__((visibility("default")))
void DestroyGetCoreVersionsRequestBuilder(
    voicevox_client_cpp::request::get::core_versions::Builder* builder)
{
  delete builder;
}


}
