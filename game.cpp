#include "game.hpp"

void Model::change_name(char* buff)
{
	strncpy(game_name, buff, MAX_LENGTH);
	view.draw();
}
