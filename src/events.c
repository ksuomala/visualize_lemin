#include "lemin_visual.h"

int	events(void)
{
	SDL_Event		event;
	static int		pause;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.key.keysym.sym == SDLK_SPACE
			&& event.key.type == SDL_KEYUP)
		{
			pause++;
		}
	}
	return (pause);
}
