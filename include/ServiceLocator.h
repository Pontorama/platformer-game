#ifndef ServiceLocator_h
#define ServiceLocator_h

#include "DebugLogger.h"
#include "SettingsManager.h"
#include "UIMaster.h"
#include "WindowManager.h"

/*!
 * Class to access systems that need global or semi-global access
 * Things like loggers, audio system, settings manager go here
 * */
class ServiceLocator {
    private:
        Logger* _debugLogger;
        SettingsManager* _settingsManager;
        UIMaster* _uimaster;
        WindowManager* _windowManager;
        
    public:
        ServiceLocator();
        // Providers
        void provide(Logger* debugLogger);
        void provide(SettingsManager* settingsManager);
        void provide(UIMaster* uiMaster);
        void provide(WindowManager* windowManager);

        // Getters
        Logger* getDebuglogger();
        SettingsManager* getSettingsManager();
        UIMaster* getUIMaster();
        WindowManager* getWindowManager();
        

};

namespace Services {
    extern ServiceLocator* locator;
}
#endif
