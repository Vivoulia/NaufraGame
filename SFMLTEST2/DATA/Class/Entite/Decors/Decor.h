#pragma once
#include "../Entite.h"

class Decor: public Entite
{
public:
	Decor(int textRect_width, int textRect_height, int textRect_top, int textRect_left,int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture);
};