#include "hud.h"

HUD::HUD() {}

HUD::HUD(Graphics &graphics, Player &player)
{
	this->player = player;
	this->healthBarSprite = Sprite(graphics, "content/sprites/TextBox.png", 0, 40, 64, 8, 35, 70);
	this->healthNumber1 = Sprite(graphics, "content/sprites/TextBox.png", 0, 56, 8, 8, 66, 70);
	this->currentHealthBar = Sprite(graphics, "content/sprites/TextBox.png", 0, 25, 39, 5, 83, 72);
	this->lvWorld = Sprite(graphics, "content/sprites/TextBox.png", 81, 81, 11, 7, 38, 55);
	this->lvNumber = Sprite(graphics, "content/sprites/TextBox.png", 0, 56, 8, 8, 66, 52);
	this->expBar = Sprite(graphics, "content/sprites/TextBox.png", 0, 72, 40, 8, 83, 52);
	this->slash = Sprite(graphics, "content/sprites/TextBox.png", 72, 48, 8, 8, 100, 36);
	this->dashes = Sprite(graphics, "content/sprites/TextBox.png", 81, 51, 15, 11, 132, 26);
}

void HUD::update(int elapsedTime, Player &player)
{
	this->player = player;
	this->healthNumber1.setSourceRectX(8 * this->player.getCurrentHealth());

	//Calculation the width of the health bar
	// 100% = 39 px
	float num = (float)this->player.getCurrentHealth() / this->player.getMaxHealth();
	this->currentHealthBar.setSourceRectW(std::floor(num * 39));
}

void HUD::draw(Graphics &graphics)
{
	this->healthBarSprite.draw(graphics, this->healthBarSprite.getX(), this->healthBarSprite.getY());
	this->healthNumber1.draw(graphics, this->healthNumber1.getX(), this->healthNumber1.getY());
	this->currentHealthBar.draw(graphics, this->currentHealthBar.getX(), this->currentHealthBar.getY());
	this->lvWorld.draw(graphics, this->lvWorld.getX(), this->lvWorld.getY());
	this->lvNumber.draw(graphics, this->lvNumber.getX(), this->lvNumber.getY());
	this->expBar.draw(graphics, this->expBar.getX(), this->expBar.getY());
	this->slash.draw(graphics, this->slash.getX(), this->slash.getY());
	this->dashes.draw(graphics, this->dashes.getX(), this->dashes.getY());
}