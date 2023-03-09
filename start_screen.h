/*Start Screen of Game*/

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "start_screen.h"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game.h"
#include "game_element.h"
#include <windows.h>

class StartScreen :
    public graphics::AnimationEventListener,
    public graphics::MouseEventListener {

    private: 
     graphics::Image startScreen_;
     string imageFile_ = "";
     string SongFile_ = "";


    public: 
    //Constructors
    StartScreen();
    StartScreen(int height, int width);

    //Getters
    graphics::Image& GetStartScreen(){return startScreen_;}

    //Public Member Functions
    void DrawScreen();
    void Init();
    void Music();
    void OnMouseEvent();

};

#endif