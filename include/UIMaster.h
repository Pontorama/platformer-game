#ifndef UIMaster_h
#define UIMaster_h

#include <vector>
#include <string>

#include "UIElement.h"
// FIXME: these includes might not be needed
#include "Constants.h"
#include "TextBox.h"
#include "DebugLogger.h"

using namespace std;

/*!
    Class to init and control UI elements. UI elements get rendered last (on top of everything else).
*/

class UIMaster{
    // Master for all UI elements in a scene, renders everything
    public:
        UIMaster(SDL_Renderer* renderer);
        virtual ~UIMaster();

        void renderAllElements();
        void updateElement(int elementID, string action);
        void addElement(UIElement* elementToAdd);
        void removeElement(int elementID);
        UIElement* getElement(int index);

    private:
        SDL_Renderer* _ren;
        vector<UIElement*> _elements;

};

#endif
