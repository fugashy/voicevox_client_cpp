#include "voicevox_client_cpp/post.hpp"


extern "C"
{

/* post audio_query */
__attribute__((visibility("default")))
voicevox_client_cpp::request::post::audio_query::Builder* CreatePostAudioQueryRequestBuilder()
{
  return new voicevox_client_cpp::request::post::audio_query::Builder();
}

__attribute__((visibility("default")))
void DestroyPostAudioQueryRequestBuilder(
    voicevox_client_cpp::request::post::audio_query::Builder* builder)
{
  delete builder;
}

__attribute__((visibility("default")))
void SetPostAudioQueryRequestText(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const char* text)
{
  builder->text(text);
}

__attribute__((visibility("default")))
void SetPostAudioQueryRequestSpeaker(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int speaker)
{
  builder->speaker(speaker);
}

__attribute__((visibility("default")))
void SetPostAudioQueryRequestCoreVersion(
    voicevox_client_cpp::request::post::audio_query::Builder* builder,
    const int core_version)
{
  builder->core_version(core_version);
}

/* post synthesis */
__attribute__((visibility("default")))
voicevox_client_cpp::request::post::synthesis::Builder* CreatePostSynthesisRequestBuilder()
{
  return new voicevox_client_cpp::request::post::synthesis::Builder();
}

__attribute__((visibility("default")))
void DestroyPostSynthesisRequestBuilder(
    voicevox_client_cpp::request::post::synthesis::Builder* builder)
{
  delete builder;
}

__attribute__((visibility("default")))
void SetPostSynthesisRequestSpeaker(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int speaker)
{
  builder->speaker(speaker);
}

__attribute__((visibility("default")))
void SetPostSynthesisRequestEnableInterrogativeUpspeak(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const bool enable_interrogative_upspeak)
{
  builder->enable_interrogative_upspeak(enable_interrogative_upspeak);
}

__attribute__((visibility("default")))
void SetPostSynthesisRequestAccentPhrases(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const char* accent_phrases)
{
  builder->accent_phrases(accent_phrases);
}

__attribute__((visibility("default")))
void SetPostSynthesisRequestCoreVersion(
    voicevox_client_cpp::request::post::synthesis::Builder* builder,
    const int core_version)
{
  builder->core_version(core_version);
}


}
