/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:22:05 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 13:34:00 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

t_rgb	ant_color(int wave)
{
	t_rgb	color[20];

	if (wave > 19)
		wave = wave % 19;
	color[0] = (t_rgb){0, 0, 255, 255};
	color[1] = (t_rgb){255, 0, 255, 255};
	color[2] = (t_rgb){0, 255, 0, 255};
	color[3] = (t_rgb){255, 255, 0, 255};
	color[4] = (t_rgb){0, 255, 255, 255};
	color[5] = (t_rgb){0, 123, 123, 255};
	color[6] = (t_rgb){0, 255, 0, 255};
	color[7] = (t_rgb){0, 255, 0, 255};
	color[8] = (t_rgb){0, 255, 0, 255};
	color[9] = (t_rgb){0, 255, 0, 255};
	color[10] = (t_rgb){0, 255, 0, 255};
	color[11] = (t_rgb){0, 255, 0, 255};
	color[12] = (t_rgb){0, 255, 0, 255};
	color[13] = (t_rgb){0, 255, 0, 255};
	color[14] = (t_rgb){0, 255, 0, 255};
	color[15] = (t_rgb){0, 255, 0, 255};
	color[16] = (t_rgb){0, 255, 0, 255};
	color[17] = (t_rgb){0, 255, 0, 255};
	color[18] = (t_rgb){0, 255, 0, 255};
	color[19] = (t_rgb){0, 255, 0, 255};
	return (color[wave]);
}

void	draw_ants(t_pointers *sdl, t_ant *ants, t_data *scale, t_map *map)
{
	SDL_Rect	pos;
	t_ant		*tmp;
	t_rgb		cl;

	pos.h = 10;
	pos.w = 10;
	tmp = ants;
	draw_graph(sdl, scale, map);
	while (tmp)
	{
		cl = ant_color(tmp->wave);
		pos.x = tmp->x + scale->room_size / 2 - 5;
		pos.y = tmp->y + scale->room_size / 2 - 5;
		SDL_SetRenderDrawColor(sdl->renderer, cl.r, cl.g, cl.b, 255);
		SDL_RenderFillRect(sdl->renderer, &pos);
		tmp = tmp->next;
	}
	events();
	SDL_RenderPresent(sdl->renderer);
	SDL_Delay(MOVE_ANT_DELAY);
}

/*
** Updating the position of the current ant to the next closest pixel towards
** the destination.
*/

void	walk_ant(t_ant *ant)
{
	float	dx;
	float	dy;
	float	step;

	dx = (ant->dest_x - ant->x);
	dy = (ant->dest_y - ant->y);
	if (fabsf(dx) >= fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	ant->x += dx / step;
	ant->y += dy / step;
}

/*
** Going through the list of ants. If the ant is not at the destination, move
** it one step closer to it. If all the ants are at their destinations, return 0.
*/

int	move_ants(t_pointers *sdl, t_ant *head, t_data *scale, t_map *map)
{
	t_ant	*tmp;
	int		ret;

	tmp = head;
	ret = 0;
	while (tmp)
	{
		if (tmp->x != tmp->dest_x || tmp->y != tmp->dest_y)
		{
			walk_ant(tmp);
			ret = 1;
		}
		tmp = tmp->next;
	}
	if (ret)
		draw_ants(sdl, head, scale, map);
	return (ret);
}
