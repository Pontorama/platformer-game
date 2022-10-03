#include "SettingsManager.h"

SettingsManager::SettingsManager(){
    init(DEFAULT_SETTINGS_PATH);
}

SettingsManager::SettingsManager(string settingsPath){
    init(settingsPath);
}

SettingsManager::~SettingsManager(){
    // Nothing to do
}

void SettingsManager::init(string settingsFilePath){
    // Load file into json
    ifstream inputfile(settingsFilePath);
    json loaded = json::parse(inputfile);
    // Take value "Settings" to exclude comments and such
    _currentSettings = loaded["Settings"];
    inputfile.close();
    _currentSettingsFilePath = settingsFilePath;
}

/*!
 * Reset all settings to default values
 * */
void SettingsManager::resetSettings(){
    init(DEFAULT_SETTINGS_PATH);
}

/*!
 * Check if a setting exists
 * @param[in] settingName Name of setting to check for
 * @return true if the setting exists
 * */
bool SettingsManager::checkIfSettingExists(string settingName){
    return _currentSettings.contains(settingName);
}

void SettingsManager::saveSettings(){
    if(_currentSettingsFilePath != DEFAULT_SETTINGS_PATH){
        ofstream fileOut(_currentSettingsFilePath);
        json out;
        out["Settings"] = _currentSettings;
        fileOut << out;
        fileOut.close();
    }else{
        // Do nothing, don't overwrite default settings
    }
}

void SettingsManager::loadSettings(string settingsToLoadPath){
    init(settingsToLoadPath);
}

/*!
 * Get a setting value
 * @param[in] settingName The name of the setting to get
 * @param[in] T The expected type of the returned setting value. If this does not match an exception is thrown.
 * retrun The setting value
 * */
/*
template<typename T> T SettingsManager::getSettingValue(string settingName){
    if(checkIfSettingExists(settingName)){
        // Check type of setting
        string type = _currentSettings[settingName]["type"].get<string>();
        if(type == TYPE_INT){
            // is_same checks if same type at runtime
            if(is_same<T, int>::value){
                return _currentSettings[settingName]["value"].get<int>();
            }
        }else if(type == TYPE_FLOAT){
            if(is_same<T, float>::value){
                return _currentSettings[settingName]["value"].get<float>();
            }
        }else if(type == TYPE_STRING){
            if(is_same<T, string>::value){
                return _currentSettings[settingName]["value"].get<string>();
            }
        }else if(type == TYPE_BOOL){
            if(is_same<T, bool>::value){
                return _currentSettings[settingName]["value"].get<bool>();
            }
        }
        throw ValueTypeMismatchException(settingName, type);
    }else{
        throw SettingNotFoundException(settingName);
    }
}
*/
/*!
 * Set a new value for a setting.
 * @param[in] settingName The name of the setting to change. Throws SettingNotFoundException if not found.
 * @param[in] newValue The new value to set. Throws ValueTypeMismatchException if wrong type.
 * */
template<typename T> void SettingsManager::setSettingValue(string settingName, T newValue){
    if(checkIfSettingExists(settingName)){
        string type = _currentSettings[settingName]["type"].get<string>();
        if(type == TYPE_INT){
            if(is_same<T, int>::value){
                _currentSettings[settingName]["value"] = newValue;
            }
        }else if(type == TYPE_FLOAT){
            if(is_same<T, float>::value){
                _currentSettings[settingName]["value"] = newValue;
            }            
        }else if(type == TYPE_BOOL){
            if(is_same<T, bool>::value){
                _currentSettings[settingName]["value"]= newValue;
            }
        }else if(type == TYPE_STRING){
            if(is_same<T, string>::value){
                _currentSettings[settingName]["value"] = newValue;
            }
        }
        throw ValueTypeMismatchException(settingName, type);
    }else{
        throw SettingNotFoundException(settingName);
    }
}


