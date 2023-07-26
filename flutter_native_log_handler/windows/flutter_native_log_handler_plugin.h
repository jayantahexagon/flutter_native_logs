#ifndef FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_

#include <windows.h>

#include <flutter/plugin_registrar_windows.h>
#include <flutter/method_channel.h>
#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/encodable_value.h>

#include <thread>

namespace flutter_native_log_handler {

// typedef flutter::StreamHandler<flutter::EncodableValue> FlutterStreamHandler;
typedef flutter::StreamHandlerError<flutter::EncodableValue> FlutterStreamHandlerError;
typedef flutter::EventSink<flutter::EncodableValue> FlutterEventSink;

class FlutterNativeLogHandlerPlugin : public flutter::Plugin {
 public:
    static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

    FlutterNativeLogHandlerPlugin();

    virtual ~FlutterNativeLogHandlerPlugin();

    FlutterNativeLogHandlerPlugin(const FlutterNativeLogHandlerPlugin&) = delete;

    FlutterNativeLogHandlerPlugin& operator=(const FlutterNativeLogHandlerPlugin&) = delete;

 private:
    void HandleMethodCall(const flutter::MethodCall<flutter::EncodableValue> &method_call, std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

    std::unique_ptr<FlutterStreamHandlerError> OnListen(const flutter::EncodableValue *arguments, std::unique_ptr<FlutterEventSink> &&events);

    std::unique_ptr<FlutterStreamHandlerError> OnCancel(const flutter::EncodableValue *arguments);

    std::unique_ptr<FlutterEventSink> eventSink_;

    void sendDataAtInterval(int interval);
    std::unique_ptr<std::thread> timerThread_;
    bool isListening_ = false;
};

}  // namespace flutter_native_log_handler

#endif  // FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_
