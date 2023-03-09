//Initialize background image X
//Upload background image (.jpeg)
//Add mouse event 
//if x= and y= within start square
    //if mousepress
        //start the game

#include "start_screen.h"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game.h"
#include "game_element.h"
#include <windows.h>

using graphics::Image;

/*Constructors*/

//Default Constructor
StartScreen::StartScreen(){
    this->startScreen_.Initialize(800, 700);
}

//Constructor
StartScreen::StartScreen(int height, int width){
    this->file_ = "startScreen";
    this->startScreen_.Initialize(height,width);
}

/*End of Constructors*/

/*Beginning of Public Member Functions*/

//Load start screen
void StartScreen::DrawScreen(){
    Image startScreen;
    startScreen.Load(imageFile_);
}

//Music for game
void StartScreen::Music(){
 PlaySound("My_Song.wav",NULL,SND_FILENAME);
}

//Initialize start screen
void StartScreen:Init(){
    Image& image = GetStartScreen();
    image.AddMouseEventListener(*this);
    Music(); //placeholder for now until I possibly find a better place to put it
}

//If mouse pressed then start game
void StartScreen::OnMouseEvent(const graphics::MouseEvent& event){
    int x = event.GetX();
    int y = event.GetY();
/*These numbers are not accurate yet, need to correct them*/
if (x < 800 and y < 800) {
    if (event.GetMouseAction() == graphics::MouseAction::kPressed){
        Game::Start(); 
    }

}

}

