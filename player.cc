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
  makePlayer();
}

// Constructor
Player::Player(int startingX, int startingY)
    : GameElement(startingX, startingY, 20, 50) {
  this->isEvil_ = false;
  this->coordsUpdated_ = true;
  this->file_ = "playerCharacter";
  // Draw Character
  makePlayer();
}

// ---------------- * Public Methods  * -------------------------
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

// ---------------- ** Start of Private Methods * --------------------
// ------------ Start of Gnome Draw (Private) --------------------

void Player::rectangleMirror(Image& image, int midpoint, int startHeight,
                             int bottomHeight, int width, Color& colorRight,
                             Color& colorLeft) {
  // this Function makes a reactangle on both sides of the midpoint
  // right
  int tempHeight = bottomHeight - startHeight;
  image.DrawRectangle(midpoint, startHeight, width, tempHeight, colorRight);

  // left
  int leftSideStart = midpoint - width;
  image.DrawRectangle(leftSideStart, startHeight, width, tempHeight, colorLeft);
}

void Player::triangleMirror(Image& image, vector<int>& right, vector<int>& left,
                            Color& colorRight, Color& colorLeft) {
  image.DrawPolygon(left, colorLeft);
  image.DrawPolygon(right, colorRight);
}

void Player::makePlayer() {
  // ------------ Start of Variable Declaration --------------------
  // Vertical breakPoints
  // This wouldnt work for non divisble ints of base 50
  // Designed to scale to whatever hieght that is given;

  // VB of where different shapes will fit
  const int height = 50;
  const int width = 20;
  const string fileName = file_;
  const bool isEvil = isEvil_;

  const int bottomOfHatPointHeight = height * 22 / 50;
  const int topFace = height * 19 / 50;
  const int topOfBody = height * 3 / 5;
  const int cheakbone = topOfBody - height * 1 / 50;
  const int cheakboneHigher = cheakbone - height * 1 / 50;
  const int topBeard = bottomOfHatPointHeight + height * 3 / 50;
  const int midChunckBeard = topBeard + height * 4 / 25;
  const int beardPoint = height * 39 / 50;
  const int bottomCoat = beardPoint + height * 4 / 50;
  const int shoeBuffer = bottomCoat + height * 1 / 50;
  const int shoeHeel = shoeBuffer + height * 3 / 50;
  const int tipOfShoe = height * 46 / 50;
  const int leftHandHeight = height * 38 / 50;
  const int maxheight = height - 1;

  // Horizontal Break Points
  // Since the image will be mirrored. the 0 will be treated as the mid point.

  const int midpoint = width / 2;
  const int hatOuterWidth = 6;
  const int faceWidth = 5;
  const int faceBackroundWidth = 6;
  const int beardWidth = 7;
  const int bodyBackgroundWidth = 8;
  const int pantTaperWidth = 4;
  const int shoeTopWidth = width * 5 / 50;
  const int maxImageWidthRight = midpoint + 10;
  const int maxImageWidthLeft = midpoint - 10;

  // Postitions are meant for single lines vs widths are for boxes
  const int eyePosition = 1;
  const int armlength = 6;
  const int handlength = 4;

  // constants based on scaling width or height
  const int onePixelHeight = height * 1 / 50;
  const int onePixelWidth = 1;
  const int twoPixelHeight = height * 2 / 50;
  const int twoPixelWidth = 2;
  const int threePixelWidth = 3;
  const int rgbAverage = 3;
  // Variables that are placeHolders

  int leftSideStart;
  int tempHeight;
  int tempWidth;
  int secondPointForLine;
  int shoeTemp;
  int additionalShoePoint;

  // Vectors for Triangle Parts
  // Entire vector section is jsut setting up vector Section.
  // Vectors for the hat

  // right Hat Vector
  // All temp values there tempWidth,leftSideStart,shoeTemp used to shape hat
  // Width based off midpoint + hatouterWidth - one pixel (top curve)
  tempWidth = midpoint + hatOuterWidth - onePixelWidth;
  leftSideStart = midpoint + onePixelWidth;
  shoeTemp = midpoint + twoPixelWidth;
  // Multiple temp variables thrown into Widths. Widths have to be
  // mirrored which is why temp is used
  vector<int> rightHatVector{midpoint,      0,
                             midpoint,      bottomOfHatPointHeight,
                             tempWidth,     bottomOfHatPointHeight,
                             shoeTemp,      twoPixelHeight,
                             leftSideStart, onePixelHeight};
  // left Hat
  tempWidth = midpoint - hatOuterWidth;
  leftSideStart = midpoint - onePixelWidth;
  vector<int> leftHatVector{leftSideStart, 0,
                            midpoint,      bottomOfHatPointHeight,
                            tempWidth,     bottomOfHatPointHeight};

  // Vectors for beard
  // All temp values there tempWidth,leftSideStart,shoeTemp used to shape hat
  // Width based off midpoint
  tempWidth = midpoint + beardWidth - onePixelWidth;
  vector<int> rightBeardVector{midpoint,   midChunckBeard, midpoint,
                               beardPoint, tempWidth,      midChunckBeard};
  tempWidth = midpoint - beardWidth;
  vector<int> leftBeardVector{midpoint,   midChunckBeard, midpoint,
                              beardPoint, tempWidth,      midChunckBeard};

  // Vectors for face
  // Rigth face
  tempWidth = midpoint + pantTaperWidth;
  leftSideStart = tempWidth - onePixelWidth;
  secondPointForLine = midpoint + onePixelWidth;
  vector<int> rightFaceVector{midpoint,           topFace,
                              midpoint,           topOfBody,
                              secondPointForLine, topOfBody,
                              leftSideStart,      cheakbone,
                              tempWidth,          cheakboneHigher,
                              leftSideStart,      bottomOfHatPointHeight,
                              secondPointForLine, topFace};

  // left Face
  tempWidth = midpoint - pantTaperWidth - onePixelWidth;
  leftSideStart = tempWidth + onePixelWidth;
  secondPointForLine = midpoint - twoPixelWidth;
  vector<int> leftFaceVector{midpoint,           topFace,
                             midpoint,           topOfBody,
                             secondPointForLine, topOfBody,
                             leftSideStart,      cheakbone,
                             tempWidth,          cheakboneHigher,
                             leftSideStart,      bottomOfHatPointHeight,
                             secondPointForLine, topFace};

  // Vector for Shoes
  // right Shoe
  // line for heel to bottom
  tempWidth = midpoint + hatOuterWidth;
  // Adds one more stop in vector
  additionalShoePoint = tempWidth - onePixelWidth;
  // width tip of shoe
  secondPointForLine = midpoint + bodyBackgroundWidth;

  tempHeight = maxheight - onePixelHeight;
  shoeTemp = shoeTopWidth + midpoint;
  vector<int> rightBootVector{
      midpoint,   shoeBuffer,          midpoint,
      shoeHeel,   additionalShoePoint, maxheight,
      tempWidth,  maxheight,           secondPointForLine,
      tempHeight, secondPointForLine,  tipOfShoe,
      shoeTemp,   shoeBuffer};
  // left Shoe
  // line for heel to bottom
  tempWidth = midpoint - hatOuterWidth;
  // adds one more poin to shoe
  additionalShoePoint = tempWidth + onePixelWidth;
  // width tip of shoe
  secondPointForLine = midpoint - bodyBackgroundWidth;
  shoeTemp = midpoint - shoeTopWidth;
  vector<int> leftBootVector{
      midpoint,   shoeBuffer,          midpoint,
      shoeHeel,   additionalShoePoint, maxheight,
      tempWidth,  maxheight,           secondPointForLine,
      tempHeight, secondPointForLine,  tipOfShoe,
      shoeTemp,   shoeBuffer};
  // End of vetor sction

  // Color Section
  // Second thing I did was make the Image
  Color rightHat(190, 73, 74);
  Color rightBeard(198, 99, 98);
  Color rightSkin(254, 254, 254);
  Color rightBoot(133, 64, 64);
  Color rightHatTrim(182, 47, 45);
  Color rightBody(161, 66, 68);
  // Character left
  Color leftHat(139, 22, 23);
  Color leftBeard(148, 47, 44);
  Color leftSkin(200, 200, 200);
  Color leftBoot(85, 15, 17);
  Color lefthatTrim(139, 22, 23);
  Color leftBody(107, 11, 14);
  // Universal
  Color eyeColor(176, 133, 133);
  Color evilCorruption(41, 217, 33);
  // If Evil Change EyeColor
  if (isEvil) {
    eyeColor.SetRed(255);
    eyeColor.SetGreen(0);
    eyeColor.SetBlue(0);
  }
  // -------------- end of Variable Declaration- -------------------
  // Create Image
  Image image(width, height);

  // 1st Draw is the Body
  // -------- Start Body Background Section --------------------
  rectangleMirror(image, midpoint, topOfBody, bottomCoat, bodyBackgroundWidth,
                  rightBody, leftBody);
  // Draw line next to arms
  // Right arm
  // arm start
  tempHeight = topOfBody + twoPixelHeight;
  // arm end
  secondPointForLine = tempHeight + armlength;
  leftSideStart = midpoint + bodyBackgroundWidth;

  image.DrawLine(leftSideStart, tempHeight, leftSideStart, secondPointForLine,
                 rightBody);
  // Left Arm
  leftSideStart = midpoint - bodyBackgroundWidth - onePixelWidth;
  image.DrawLine(leftSideStart, tempHeight, leftSideStart, secondPointForLine,
                 leftBody);

  // Draw tapered bottom body
  tempWidth = bodyBackgroundWidth - onePixelWidth;
  leftSideStart = bottomCoat;
  tempHeight = leftSideStart + onePixelHeight;
  rectangleMirror(image, midpoint, leftSideStart, tempHeight, tempWidth,
                  rightBody, leftBody);
  // Tapper one more down again
  leftSideStart = leftSideStart + onePixelHeight;
  rectangleMirror(image, midpoint, leftSideStart, tempHeight, shoeTopWidth,
                  rightBody, leftBody);
  // ------------------- End Body Section --------------------
  // ------------------- Start Beard Section ------------------
  // Drawing Face Frame/ hairbackgroound
  rectangleMirror(image, midpoint, bottomOfHatPointHeight, topBeard,
                  faceBackroundWidth, rightBeard, leftBeard);
  // drawing Top of Breard or the main chunck of the beard
  rectangleMirror(image, midpoint, topBeard, midChunckBeard, beardWidth,
                  rightBeard, leftBeard);
  // Beard point
  triangleMirror(image, rightBeardVector, leftBeardVector, rightBeard,
                 leftBeard);
  // ------------------- End Beard Section ------------------
  // ------------------ Start Hat Section ------------------
  // hat
  triangleMirror(image, rightHatVector, leftHatVector, rightBody, leftBody);
  // tiny hat ball
  tempHeight = 0;
  tempWidth = midpoint - threePixelWidth;
  image.DrawRectangle(tempWidth, tempHeight, twoPixelHeight, twoPixelWidth,
                      leftBody);
  // ------------------- End Hat Section ------------------

  // ------------------ Start Hand Section ------------------
  // Draw Right Hand
  // setting the hands at diffeent heights
  tempWidth = midpoint + faceWidth - onePixelWidth;
  tempHeight = leftHandHeight - onePixelHeight;
  image.DrawRectangle(tempWidth, tempHeight, threePixelWidth, handlength,
                      rightSkin);

  // Left Hand
  // setting temp width for location of hand
  tempWidth = midpoint - beardWidth;
  image.DrawRectangle(tempWidth, leftHandHeight, threePixelWidth, handlength,
                      leftSkin);
  // ------------------ End Hand Section ------------------
  // ------------------ Start Face Section ------------------
  // Face
  triangleMirror(image, rightFaceVector, leftFaceVector, rightSkin, leftSkin);
  // ------------------ End Face Section ------------------
  // ------------------ Start shoes Section ------------------
  // Shoes
  triangleMirror(image, rightBootVector, leftBootVector, rightBoot, leftBoot);
  // ------------------ End shoes Section ------------------

  // Pixelization to make it look cooler
  for (int x = 0; x < width; x++) {
    // There is no pixels to edit outside of this Range
    if (maxImageWidthLeft < x && x < maxImageWidthRight) {
      for (int y = 0; y < width; y++) {
        int red = image.GetRed(x, y);
        // If image red is == 255 then the picture is background then skip
        if (red == 255) {
          continue;
        } else if (isEvil) {
          // If its Evil run code
          int random = rand() % 5 + 1;
          // 1 out 5 change add evil Corruption Color
          if (random % 4 == 0) {
            image.SetColor(x, y, evilCorruption);
          } else {
            // 4/5 change to greyScale Evil Image
            // Get Colors
            Color color = image.GetColor(x, y);
            // Then I average the colors to get the grey Scale
            int greyScale =
                (color.Red() + color.Blue() + color.Green()) / rgbAverage;
            // New GreyScale Color
            Color tempColor(greyScale, greyScale, greyScale);
            image.SetColor(x, y, tempColor);
          }
          // Finally don't do anythine else skip loop
          continue;
        } else if (red == 254 || red == 200) {
          // if Color is near white or grey second side. randomize color
          red = red - rand() % 10 + 1;
          Color tempColor(red, red, red);
          image.SetColor(x, y, tempColor);
        } else {
          // random number
          int random = rand() % 4 + 1;
          // 1/4 chance of changing color
          if (random % 4 == 0) {
            // get Colors, then randomize off base
            int green = image.GetGreen(x, y);
            int blue = image.GetBlue(x, y);
            red = red + rand() % 20 + 1;
            blue = blue + rand() % 10 + 1;
            green = green + rand() % 10 + 1;
            Color tempColor(red, green, blue);
            image.SetColor(x, y, tempColor);
          } else {
            continue;
          }
        }
      }
    } else {
      continue;
    }
  }
  // After gnome has been altered add eyes
  // ------------------ Start eye Section ------------------
  // Eyes
  // right Eye

  leftSideStart = midpoint + eyePosition;
  tempHeight = bottomOfHatPointHeight + twoPixelHeight;
  image.DrawLine(leftSideStart, bottomOfHatPointHeight, leftSideStart,
                 tempHeight, eyeColor);
  // Left eye
  leftSideStart = midpoint - eyePosition - onePixelWidth;
  image.DrawLine(leftSideStart, bottomOfHatPointHeight, leftSideStart,
                 tempHeight, eyeColor);
  // ------------------ End eye Section ------------------
  // Save File
  image.SaveImageBmp(fileName);
}
// ------------ * End of Gnome Draw * --------------------
//
// ---------- *** Player Class End *** ---------------------
//
//
//
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
  this->y_ = y_ - velocity_;
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
