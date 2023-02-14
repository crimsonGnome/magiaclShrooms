// Name: Destiny Bonillas
// CWID: 887190072
// Email: destinybonillas@csu.fullerton.edu

// Name: Joseph Eggers
// CWID: 885939488
// Email: joseph.eggers@csu.fullerton.edu

#include "player.h"

#include <iostream>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"

using graphics::Image, graphics::Color, std::cin, std::cout, std::endl,
    std::string, std::vector;

// ---------- *** Player Class Start *** ---------------------
// ---------------- ** Start of Public Methods * ---------------------

// ---------------- * Constructors * -------------------------

// Default Constructor
Player::Player() : GameElement(0, 0, 20, 50) {
  this->isEvil_ = false;
  this->coordsUpdated_ = false;
  this->file_ = "playerCharacter";
  // Draw Character
  
}

// Constructor
Player::Player(int startingX, int startingY)
    : GameElement(startingX, startingY, 20, 50) {
  this->isEvil_ = false;
  this->coordsUpdated_ = true;
  this->file_ = "playerCharacter";
  // Draw Character
}
// Draw Character onto image
void Player::Draw(Image& image) {
  // Initilize Images
  Image player;
  // Load Robot and Hide it so it Doesnt display
  player.Load(file_);
  // ---------- Start of Variable Decleartion -----------
  // Constant Hieghts
  const int imgHeight = image.GetHeight();
  const int imgWidth = image.GetWidth();
  const int height = player.GetHeight();
  const int width = player.GetWidth();

  // ---------- End of Variable Decleartion -----------
  // ------------ Copy Image -----------------------
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Get color of the Image
      Color playerColor = player.GetColor(i, j);
      // off setting by the middle to draw image
      int xOffSet = x_ + i;
      int yOffSet = y_ + j;

      // Getting the image to draw on the location
      // only Draw Image if its range
      if ((xOffSet < imgWidth && xOffSet >= 0) &&
          (yOffSet < imgHeight && yOffSet >= 0)) {
        image.SetColor(xOffSet, yOffSet, playerColor);
      } else {
        continue;
      }
    }
  }
  this->coordsUpdated_ = false;
}

// Defining Move Function
void Player::Move(const Image& image) {
  // implememt later
}
//
// ---------- *** PlayerProjectile Class Start *** ----------------
// ---------------- ** Start of Public Methods * ---------------------

// ---------------- * Constructors * -------------------------

// Default Constructor
PlayerProjectile::PlayerProjectile() : GameElement(0, 0, 5, 5) {
  this->coordsUpdated_ = false;
  this->file_ = "playerProjectile";
  // Draw Character
  makeProjectile();
}

// Constructor
PlayerProjectile::PlayerProjectile(int startingX, int startingY)
    : GameElement(startingX, startingY, 5, 5) {
  this->coordsUpdated_ = true;
  this->file_ = "playerProjectile";
  // Draw Character
  makeProjectile();
}

// ---------------- * Public Methods  * -------------------------
// Draw Character onto image
void PlayerProjectile::Draw(Image& image) {
  // Initilize Images
  Image player;
  // Load Robot and Hide it so it Doesnt display
  player.Load(file_);
  player.Hide();
  // ---------- Start of Variable Decleartion -----------
  // Constant Hieghts
  const int imgHeight = image.GetHeight();
  const int imgWidth = image.GetWidth();
  const int height = player.GetHeight();
  const int width = player.GetWidth();
  // ---------- End of Variable Decleartion -----------
  // ------------ Copy Image -----------------------
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Get color of the Image
      Color playerColor = player.GetColor(i, j);
      // off setting by the middle to draw image
      int xOffSet = x_ + i;
      int yOffSet = y_ + j;

      // Getting the image to draw on the location
      // only Draw Image if its range
      if ((xOffSet < imgWidth && xOffSet >= 0) &&
          (yOffSet < imgHeight && yOffSet >= 0)) {
        image.SetColor(xOffSet, yOffSet, playerColor);
      } else {
        continue;
      }
    }
  }
  this->coordsUpdated_ = false;
}

// Defining Move Function
void PlayerProjectile::Move(const Image& image) {
  if (IsOutOfBounds(image) == true) {
    is_active_ = false;
    return;
  }
  this->y_ = y_ + velocity_;
}
// ---------------- ** Start of Private Methods * --------------------
void PlayerProjectile::makeProjectile() {
  Color center(153, 217, 234);
  Color second(78, 171, 252);
  Image image(width_, height_);
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      int random = rand() % 3 + 1;
      if (random % 3 == 0) {
        image.SetColor(x, y, second);
      } else {
        image.SetColor(x, y, center);
      }
    }
  }
  image.SaveImageBmp(file_);
}
