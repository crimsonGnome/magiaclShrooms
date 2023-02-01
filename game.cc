/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

#include "game.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "opponent.h"
#include "player.h"

using graphics::Image, std::cout, std::string, std::vector, std::unique_ptr;

// ---------------- Start of game Class ----------------------------
// ---------------- Start of Game Constructors ---------------------

Game::Game() {
  this->gameScreen_.Initialize(800, 600);
  Player crimsonGnome(375, 550);
  this->player_ = crimsonGnome;
}

Game::Game(int height, int width) {
  this->gameScreen_.Initialize(height, width);
  Player crimsonGnome(375, 550);
  this->player_ = crimsonGnome;
}
// ---------------- End of Game Constructors -----------------------
// ---------------- Start of Game Memeber Functions ----------------
// ---------------- Start of Game (Private) Memeber Functions ------

void Game::FirePlayerProjectile(Player& crimsonGnome) {
  // Vector for player projectiles
  vector<unique_ptr<PlayerProjectile>>& playerProjectileVect =
      GetPlayerProjectiles();
  // Create a unique pointer to player projectile
  unique_ptr<PlayerProjectile> beam(
      new PlayerProjectile(crimsonGnome.GetX(), crimsonGnome.GetY()));
  // Push player projectile to vector
  playerProjectileVect.push_back(move(beam));
}

// ---------------- Start of Game (Public) Memeber Functions ------

void Game::CreateOpponents() {
  // Init hoot hoots

  vector<unique_ptr<Opponent>>& opponentVector = opponent_;
  unique_ptr<Opponent> owl0(new Opponent(200, 1));
  unique_ptr<Opponent> owl1(new Opponent(300, 1));
  unique_ptr<Opponent> owl2(new Opponent(400, 1));
  unique_ptr<Opponent> owl3(new Opponent(500, 1));
  unique_ptr<Opponent> owl4(new Opponent(600, 1));

  // Add hoot hoots to array
  opponentVector.push_back(move(owl0));
  opponentVector.push_back(move(owl1));
  opponentVector.push_back(move(owl2));
  opponentVector.push_back(move(owl3));
  opponentVector.push_back(move(owl4));

  UpdateScreen();
}

void Game::Init() {
  // Setting New player position
  Image& image = GetGameScreen();
  // player.SetX(x);
  // player.SetY(y);
  image.AddMouseEventListener(*this);
  image.AddAnimationEventListener(*this);
}

void Game::MoveGameElements() {
  // Get Vectors
  Image& image = GetGameScreen();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  Player& player = GetPlayer();
  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  // Block owl movements move right or left
  if (opponent[opponent.size() - 1]->GetX() > 740) {
    for (int i = 0; i < opponent.size(); i++) {
      opponent[i]->SetMoveDirection(false);
    }
  } else if (opponent[0]->GetX() < 10) {
    for (int i = 0; i < opponent.size(); i++) {
      opponent[i]->SetMoveDirection(true);
    }
  }
  // Move all the images
  for (int i = 0; i < opponent.size(); i++) {
    opponent[i]->Move(image);
  }
  for (int i = 0; i < opponent_projectile.size(); i++) {
    opponent_projectile[i]->Move(image);
  }
  for (int i = 0; i < player_projectile.size(); i++) {
    player_projectile[i]->Move(image);
  }
}

void Game::FilterIntersections() {
  Player& player = GetPlayer();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  // for opponent and player
  for (int i = 0; i < opponent.size(); i++) {
    if (player.IntersectsWith(opponent[i].get())) {
      opponent[i]->SetIsActive(false);
      player.SetIsActive(false);
      this->status_ = false;
    }
  }

  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  // for opponent projectiles and player
  for (int i = 0; i < opponent_projectile.size(); i++) {
    if (player.IntersectsWith(opponent_projectile[i].get())) {
      opponent_projectile[i]->SetIcrimsonGnomesActive(false);
      player.SetIsActive(false);
      this->status_ = false;
    }
  }

  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  for (int j = 0; j < player_projectile.size(); j++) {
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->IntersectsWith(player_projectile[j].get())) {
        player_projectile[j]->SetIsActive(false);
        opponent[i]->SetIsActive(false);
        if (player.GetIsActive()) {
          this->score_++;
        }
      }
    }
  }
}

void Game::RemoveInactive() {
  // Get vector for opponent
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  // Loop over opponent vector and remove any elements that are inactive
  for (int i = 0; i < opponent.size(); i++) {
    // if inactive remove
    if (!opponent[i]->GetIsActive()) {
      opponent.erase(opponent.begin() + i);
      i--;
    }
  }

  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  // Loop over opponent_projectile vector and remove any elements that are
  // inactive
  for (int i = 0; i < opponent_projectile.size(); i++) {
    // if inactive remove
    if (!opponent_projectile[i]->GetIsActive()) {
      opponent_projectile.erase(opponent_projectile.begin() + i);
      i--;
    }
  }

  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  // Loop over player_projectile vector and remove any elements that are
  // inactive
  for (int i = 0; i < player_projectile.size(); i++) {
    // if inactive remove
    if (!player_projectile[i]->GetIsActive()) {
      player_projectile.erase(player_projectile.begin() + i);
      i--;
    }
  }
}

void Game::LaunchProjectiles() {
  // Launching Projectiles
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  for (int i = 0; i < opponent.size(); i++) {
    unique_ptr<OpponentProjectile> new_opponent =
        opponent[i]->LaunchProjectile();
    if (new_opponent != nullptr) {
      opponent_projectile.push_back(move(new_opponent));
    }
  }
}

void Game::UpdateScreen() {
  Image& image = GetGameScreen();
  // Draw Screen white
  image.DrawRectangle(0, 0, image.GetWidth(), image.GetHeight(), 255, 255, 255);

  // Intialize vectors objects to loop over
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  Player& player = GetPlayer();
  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();

  // Intialize the color of the text and turn the int score into string
  string scoreToString = std::to_string(score_);
  Color textColor(0, 0, 0);

  // Including the current score of the game
  image.DrawText(5, 5, scoreToString, 14, textColor);
  if (status_) {
    // Loop over opponent vector
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->GetIsActive() == true) {
        opponent[i]->Draw(image);
      }
    }
    // Loop over opponent projectile vector
    for (int i = 0; i < opponent_projectile.size(); i++) {
      if (opponent_projectile[i]->GetIsActive() == true) {
        opponent_projectile[i]->Draw(image);
      }
    }
    // Loop over player projectile vector
    for (int i = 0; i < player_projectile.size(); i++) {
      if (player_projectile[i]->GetIsActive() == true) {
        player_projectile[i]->Draw(image);
      }
    }

    if (player.GetIsActive()) {
      player.Draw(image);
    }
  } else {
    // if the player lost. Display game Screen
    // Get the middle of the screen for height and width.
    int middleOfWidthScreen = (image.GetWidth() / 2) - 100;
    int MiddleHeightOfScreen = (image.GetHeight() / 2) - 25;
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->GetIsActive() == true) {
        opponent[i]->Draw(image);
      }
    }
    image.DrawText(middleOfWidthScreen, MiddleHeightOfScreen, "Game Over", 50,
                   textColor);
  }
}

void Game::OnAnimationStep() {
  Image& image = GetGameScreen();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  if (opponent.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  image.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  int x = event.GetX();
  int y = event.GetY();
  Player& player = GetPlayer();

  if (event.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (x < 800 && x >= 0 && y >= 0 && y < 600) {
      player.SetX(x - 10);
      player.SetY(y - 25);
      FirePlayerProjectile(player);
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kMoved) {
    if (x < 800 && x >= 0 && y >= 0 && y < 600) {
      player.SetX(x - 10);
      player.SetY(y - 25);
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    FirePlayerProjectile(player);
  }
}

void Game::Start() {
  Image& image = GetGameScreen();
  image.ShowUntilClosed();
}
// ---------------- End of Game Memeber Functions ------------------
// ---------------- End of game Class ------------------------------
