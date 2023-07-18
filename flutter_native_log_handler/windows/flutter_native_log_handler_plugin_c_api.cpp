#include "include/flutter_native_log_handler/flutter_native_log_handler_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_native_log_handler_plugin.h"

void FlutterNativeLogHandlerPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_native_log_handler::FlutterNativeLogHandlerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
