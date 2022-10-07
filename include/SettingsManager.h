#ifndef SettingsManager_h
#define SettingsManager_h

#include "json.hpp"
#include "Constants.h"
#include <exception>
#include <fstream>

using namespace std;
using json = nlohmann::json;
/*!
 * Class to keep track of settings. 
 * Loads settings from json and has getters for different fields.
 * Default settings should be defined here.
 * */
// Default settings path
const string DEFAULT_SETTINGS_PATH = ASSETS_PATH + "Default_settings.json";
// -----------------------
// Types
const string TYPE_INT = "int";
const string TYPE_FLOAT = "float";
const string TYPE_STRING = "string";
const string TYPE_BOOL = "bool";
// -----
// Exceptions
class SettingNotFoundException : public exception {
    public:
        SettingNotFoundException(string settingName) : _settingName(settingName) {}
        const char* what() {
            _errorMessage = "Setting '" + _settingName + "' not found.";
            return _errorMessage.c_str();
        }
    private:
        string _settingName;
        string _errorMessage;
};

class ValueTypeMismatchException : public exception {
    public:
        ValueTypeMismatchException(string settingName, string settingType) : _settingName(settingName), _settingType(settingType){}
        const char* what(){
            string out = "Setting '" + _settingName + "' is type '" + _settingType + "'.";
            return out.c_str();
        }
    private:
        string _settingName;
        string _settingType;
};
class SettingsManager {
    public:
        SettingsManager();
        SettingsManager(string settingsPath);
        ~SettingsManager();

        void resetSettings();
        template<typename T> T getSettingValue(string settingName){
            if(checkIfSettingExists(settingName)){
                // Check type of setting
                string type = _currentSettings[settingName]["type"].get<string>();
                if(type == TYPE_INT){
                // is_same checks if same type at runtime
                if(is_same<T, int>::value){
                    return _currentSettings[settingName]["value"].get<T>();
                }
            }else if(type == TYPE_FLOAT){
                if(is_same<T, float>::value){
                    return _currentSettings[settingName]["value"].get<T>();
                }
            }else if(type == TYPE_STRING){
                if(is_same<T, string>::value){
                    return _currentSettings[settingName]["value"].get<T>();
                }
            }else if(type == TYPE_BOOL){
                if(is_same<T, bool>::value){
                    return _currentSettings[settingName]["value"].get<T>();
                }
            }
            throw ValueTypeMismatchException(settingName, type);
            }else{
                throw SettingNotFoundException(settingName);
            }
        };
        template<typename T> void setSettingValue(string settingName, T newValue);
        void saveSettings();
        void loadSettings(string settingsToLoadPath);
    private:
        json _currentSettings;
        string _currentSettingsFilePath;

        bool checkIfSettingExists(string settingName);
        void init(string settingsFilePath);
};




#endif
