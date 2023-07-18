#ifndef FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_native_log_handler {

class FlutterNativeLogHandlerPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterNativeLogHandlerPlugin();

  virtual ~FlutterNativeLogHandlerPlugin();

  // Disallow copy and assign.
  FlutterNativeLogHandlerPlugin(const FlutterNativeLogHandlerPlugin&) = delete;
  FlutterNativeLogHandlerPlugin& operator=(const FlutterNativeLogHandlerPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace flutter_native_log_handler

#endif  // FLUTTER_PLUGIN_FLUTTER_NATIVE_LOG_HANDLER_PLUGIN_H_
