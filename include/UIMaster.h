#ifndef UIMaster_h
#define UIMaster_h

#include <vector>
#include <string>

#include "UIElement.h"
// FIXME: these includes might not be needed
#include "Constants.h"
#include "TextBox.h"

using namespace std;

class UIMaster{
    // Master for all UI elements in a scene, renders everything
    public:
        UIMaster(SDL_Renderer* renderer);
        virtual ~UIMaster();

        void renderAllElements();
        void updateElement(int elementID, string action);
        void addElement(UIElement* elementToAdd);
        void removeElement(int elementID);

    private:
        SDL_Renderer* _ren;
        vector<UIElement*> _elements;

};

#endif