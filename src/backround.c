/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backround.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:59:26 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 14:45:34 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

t_room	*room_coordinates(t_room *rooms, int size, int room_count)
{
	int	i;

	i = 0;
	while (i < room_count)
	{
		rooms[i].x = rooms[i].x * size + 50;
		rooms[i].y = rooms[i].y * size + 50;
		i++;
	}
	return (rooms);
}

/*
** Initializing SDL2. Creating the window and renderer.
*/

t_pointers	*initialize(t_data *scale, t_pointers *sdl, t_room *rooms)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		ft_error(SDL_GetError());
	sdl->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!sdl->window)
		ft_error(SDL_GetError());
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
			SDL_RENDERER_TARGETTEXTURE);
	if (!sdl->renderer)
		ft_error(SDL_GetError());
	if (TTF_Init() == -1)
		ft_error("TTF_INIT ERROR\n");
	sdl->font = TTF_OpenFont("visualizer_dir/Ubuntu-M.ttf", 24);
	if (!sdl->font)
		ft_error(SDL_GetError());
	rooms = room_coordinates(rooms, scale->room_size, scale->room_count);
	return (sdl);
}
