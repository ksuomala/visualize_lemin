#include "lemin_visual.h"

SDL_Rect	get_rect(TTF_Font *f, t_room room, int scale, SDL_Rect rect)
{
	TTF_SizeText(f, room.name, &rect.w, &rect.h);
	rect.x = room.x + scale / 5;
	rect.y = room.y + scale / 5;
	return (rect);
}
