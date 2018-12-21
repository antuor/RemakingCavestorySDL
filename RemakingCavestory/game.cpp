#include "game.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}


Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Camera::Init();
	this->gameLoop();
}


Game::~Game()
{

}

void Game::gameLoop() 
{
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();

	Graphics graphics;
	Input input;
	SDL_Event event;

	this->level = Level("Map_1", graphics);
	this->player = Player(graphics, this->level.getPlayerSpawnPoint());
	this->hud = HUD(graphics, this->player);
	this->guns = Guns(graphics, this->player);
	
	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) 
		{
			if(event.type == SDL_KEYDOWN) 
			{
				if (event.key.repeat == 0) 
					input.KeyDownEvent(event);
			}
			else if (event.type == SDL_KEYUP) 
				input.KeyUpEvent(event);
			else if (event.type == SDL_QUIT) 
				return;
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
			return;
		else if (this->player.getCurrentHealth() <= 0)
			return;
		else if(input.isKeyHeld(SDL_SCANCODE_LEFT) && input.isKeyHeld(SDL_SCANCODE_RIGHT))
			this->player.stopMoving();
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT))
			this->player.moveLeft();
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT))
			this->player.moveRight();

		if (input.isKeyHeld(SDL_SCANCODE_UP) == true)
			this->player.lookUp();
		else 
		{
			if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true)
				this->player.lookDown();
		}

		if (input.wasKeyReleased(SDL_SCANCODE_UP) == true)
			this->player.stopLookingUp();
		if (input.wasKeyReleased(SDL_SCANCODE_DOWN) == true)
			this->player.stopLookingDown();

		if (input.wasKeyPressed(SDL_SCANCODE_Z) == true)
		{
			this->player.jump();
		}
		if (input.wasKeyPressed(SDL_SCANCODE_X) == true)
			this->shoot = Shoot(graphics, this->player);

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
			this->player.stopMoving();

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->graphics = graphics;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		SDL_Delay(1000 / FPS);
		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) 
{
	graphics.clear();

	this->level.draw(graphics);
	this->player.draw(graphics);
	this->hud.draw(graphics);
	this->shoot.draw(graphics);
	//this->guns.draw(graphics);
	SDL_Rect tmp = { -Camera::GetRect().x, -Camera::GetRect().y, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT };
	SDL_RenderSetViewport(graphics.getRenderer(), &tmp);
	graphics.flip();
}

void Game::update(float elapsedtime) 
{
	this->player.update(elapsedtime);
	//this->guns.update(elapsedtime, this->player);
	this->level.update(elapsedtime, this->player);
	this->hud.update(elapsedtime, this->player);
	this->shoot.update(elapsedtime);
	Camera::Update(elapsedtime, this->player);

	//Check collisions
	std::vector<Rectangle> others;
	if ((others = this->level.checkTileCollisions(this->player.getBoundingBox())).size() > 0)
	{
		//Player collided with at least one tile. Handle it
		this->player.handleTileCollisions(others);
	}
	//Check slopes
	std::vector<Slope> othersSlopes;
	if ((othersSlopes = this->level.checkSlopeCollision(this->player.getBoundingBox())).size() > 0)
	{
		this->player.handleSlopeCollisions(othersSlopes);
	}

	//Check doors
	std::vector<Door> otherDoors;
	if ((otherDoors = this->level.checkDoorCollision(this->player.getBoundingBox())).size() > 0) 
	{
		this->player.handleDoorCollision(otherDoors, this->level, this->graphics);
	}

	//Check enemies
	std::vector<std::shared_ptr<Enemy>> otherEnemy;
	if ((otherEnemy = this->level.checkEnemyCollision(this->player.getBoundingBox())).size() > 0)
	{
		this->player.handleEnemyCollisions(otherEnemy);
	}

	//Check bullets
	std::vector<std::shared_ptr<Enemy>> otherHitEnemy;
	if ((otherHitEnemy = this->level.checkEnemyCollision(this->shoot.getBoundingBox())).size() > 0)
	{
		this->shoot.handleEnemyCollisions(otherHitEnemy);
	}
}