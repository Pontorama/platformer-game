#ifndef Logger_h
#define Logger_h

#include <string>

using namespace std;

/*
 * Interface for loggers
 * */

class Logger {
    public:
        virtual ~Logger();
        virtual void log(string message);       
};

#endif /* Logger.h */
