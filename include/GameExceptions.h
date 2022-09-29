#include <exception>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

class InvalidJsonException : public exception {
    json _object;
    public:
        InvalidJsonException() : _object("") {};
        InvalidJsonException(json object) : _object(object) {};
    virtual const char* what() const throw () {
        return string("Invalid JSON descriptor. JSON: \n" + _object.dump()).c_str();
    }
};
