#include "ServiceLocator.h"

ServiceLocator* Services::locator;

ServiceLocator::ServiceLocator(){
    _debugLogger = nullptr;
    _settingsManager = nullptr;
    _uimaster = nullptr;
    _windowManager = nullptr;
}

void ServiceLocator::provide(Logger* debugLogger){
    _debugLogger = debugLogger;
}

void ServiceLocator::provide(SettingsManager* settingsManager){
    _settingsManager = settingsManager;
}

void ServiceLocator::provide(UIMaster* uiMaster){
    _uimaster = uiMaster;
}

void ServiceLocator::provide(WindowManager* windowManager){
    _windowManager = windowManager;
}

Logger* ServiceLocator::getDebuglogger(){
    return _debugLogger;
}

SettingsManager* ServiceLocator::getSettingsManager(){
    return _settingsManager;
}

UIMaster* ServiceLocator::getUIMaster(){
    return _uimaster;
}

WindowManager* ServiceLocator::getWindowManager(){
    return _windowManager;
}
