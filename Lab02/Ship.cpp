#include "Ship.h"
#include "Game.h"
#include "Laser.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include <iostream>
Ship::Ship(Game* game)
	:Actor(game){
	// Create a sprite component
	sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

    mc = new MoveComponent(this);
    interval = 0.0f;
    //SetAngularSpeed(30.0f);
    //mc->SetForwardSpeed(100.0f);
}

void Ship::OnProcessInput(const Uint8 *keyState){
    
    mc->SetForwardSpeed(0.0f);
    mc->SetAngularSpeed(0.0f);
    sc->SetTexture(this->GetGame()->GetTexture("Assets/Ship.png"));
    if (keyState[SDL_SCANCODE_UP]){
        // Create a laser and set its position/rotation to mine
        sc->SetTexture(this->GetGame()->GetTexture("Assets/ShipThrust.png"));
        mc->SetForwardSpeed(256.0f);
    } else if (keyState[SDL_SCANCODE_DOWN]){
        sc->SetTexture(this->GetGame()->GetTexture("Assets/ShipThrust.png"));
        mc->SetForwardSpeed(-256.0f);

    }
    if (keyState[SDL_SCANCODE_LEFT]){
        mc->SetAngularSpeed(2*M_PI);
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        mc->SetAngularSpeed(-(2*M_PI));
    }
    if (keyState[SDL_SCANCODE_SPACE] && interval <= 0.0f){
        Laser* laser = new Laser(GetGame());
        /*if(GetGame()==NULL)
            std::cout<<"Game Doesn'tExist";
        else
            std::cout<<"Game Exist";*/
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        interval = 1.0f;
    }
    //mc->SetAngularSpeed(0.0f);
    //mc->SetForwardSpeed(0.0f);
}

void Ship::OnUpdate(float deltaTime) {
    interval -= deltaTime;
    Vector2 position = this->GetPosition();
    if (position.x < 0.0f){
        position.x = 1022.0f;
    } else if (position.x > 1024.0f){
        position.x = 2.0f;
    }
    
    if (position.y < 0.0f){
        position.y = 766.0f;
    } else if (position.y > 768.0f){
        position.y = 2.0f;
    }
    this->SetPosition(position);
}
