#ifndef Debugger_h
#define Debugger_h
#include "Vector2.h"

class Debugger{
    // TODO add list of logs
    public:
        void addLog();
        void removeLog();
    private:
        Vector2 logsPos;
        
};

#endif /* Debugger.h */