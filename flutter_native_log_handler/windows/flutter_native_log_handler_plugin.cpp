#include "flutter_native_log_handler_plugin.h"

#include <VersionHelpers.h>
#include <flutter/standard_method_codec.h>

#include <sstream>

namespace flutter_native_log_handler {

// static
void FlutterNativeLogHandlerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_native_log_handler",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterNativeLogHandlerPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterNativeLogHandlerPlugin::FlutterNativeLogHandlerPlugin() {}

FlutterNativeLogHandlerPlugin::~FlutterNativeLogHandlerPlugin() {}

void FlutterNativeLogHandlerPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else {
    result->NotImplemented();
  }
}

// static
void FlutterNativeLogHandlerPlugin::RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar) {
  auto methodChannel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(registrar->messenger(), "flutter_native_log_handler", &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterNativeLogHandlerPlugin>();

  methodChannel->SetMethodCallHandler([plugin_pointer = plugin.get()](const auto &call, auto result) {
    plugin_pointer->HandleMethodCall(call, std::move(result));
  });


  auto eventChannel = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(registrar->messenger(), "flutter_native_log_handler/logs", &flutter::StandardMethodCodec::GetInstance());

  auto eventHandler = std::make_unique<flutter::StreamHandlerFunctions<flutter::EncodableValue>>(
  [plugin_pointer = plugin.get()](const flutter::EncodableValue *arguments, std::unique_ptr<FlutterEventSink> &&events) -> std::unique_ptr<FlutterStreamHandlerError>
  {
    return plugin_pointer->OnListen(arguments, std::move(events));
  },
  [plugin_pointer = plugin.get()](const flutter::EncodableValue *arguments) -> std::unique_ptr<FlutterStreamHandlerError>
  {
    return plugin_pointer->OnCancel(arguments);
  });

  eventChannel->SetStreamHandler(std::move(eventHandler));

  registrar->AddPlugin(std::move(plugin));

}

std::unique_ptr<FlutterStreamHandlerError> FlutterNativeLogHandlerPlugin::OnListen(const flutter::EncodableValue *arguments, std::unique_ptr<FlutterEventSink> &&events) {
    std::cout << "OnListen" << std::endl;
    eventSink_ = std::move(events);

    isListening_ = true;
    // Start the timer thread to send data at the specified interval
    const int interval = 1000; // Set your desired interval in milliseconds
    timerThread_ = std::make_unique<std::thread>(&FlutterNativeLogHandlerPlugin::sendDataAtInterval, this, interval);

  return nullptr;
}

std::unique_ptr<FlutterStreamHandlerError> FlutterNativeLogHandlerPlugin::OnCancel(const flutter::EncodableValue *arguments) {
  isListening_ = false;
  // Wait for the timer thread to finish
  if (timerThread_ && timerThread_->joinable()) {
    timerThread_->join();
  }

  eventSink_ = nullptr;
  return nullptr;
}

void FlutterNativeLogHandlerPlugin::sendDataAtInterval(int interval) {
  while (isListening_) {
    // Generate random data and send it through the event channel
    std::string randomData = "CPP to DART\n";
    eventSink_->Success(flutter::EncodableValue(randomData));

    // Sleep for the specified interval
    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
  }
}

}  // namespace flutter_native_log_handler