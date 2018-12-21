#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include "slope.h"
#include "animatedtile.h"
#include "door.h"

class Enemy;
class Player;
//Tileset structure
struct Tileset
{
	SDL_Texture* Texture;
	int FirstGid;

	Tileset()
	{
		this->FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstgid)
	{
		this->Texture = texture;
		this->FirstGid = firstgid;
	}
};

class Level
{
public:
	Level();
	Level(std::string mapNam, Graphics &graphics);
	~Level();

	void update(int elapsedTime, Player &player);
	void draw(Graphics &gaphics);

	std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
	std::vector<Slope> checkSlopeCollision(const Rectangle &other);
	std::vector<Door> checkDoorCollision(const Rectangle &other);
	std::vector<std::shared_ptr<Enemy>> checkEnemyCollision(const Rectangle &other);

	const Vector2 getPlayerSpawnPoint() const;
	
private:
	std::string mapName;
	Vector2 spawnPoint;
	
	Vector2 size;
	Vector2 tileSize;

	SDL_Texture* backgroundTexture;

	std::vector<Tile> tileList;
	std::vector<Tileset> tilesets;
	std::vector<Rectangle> collisionRects;
	std::vector<Slope> slopes;

	std::vector<AnimatedTile> animatedTileList;
	std::vector<AnimatedTileInfo> animatedTileInfos;

	std::vector<Door> doorList;

	std::vector<std::shared_ptr<Enemy>> enemies;

	/* void loadMap
	 * Loads a map
	*/
	void loadMap(std::string mapName, Graphics &graphics);
	void playBackgroungMusic(std::string mapName);

	Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);

};

#endif