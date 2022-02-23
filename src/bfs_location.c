/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_location.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:20:13 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 15:06:05 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

int	get_side_len(int nb)
{
	int	i;

	i = 1;
	while (i * i < nb && i < 46341)
		i++;
	return (i);
}

/*
** Modifies generator map coordinates so they can be visualized.
*/

/*
void	modify_coordinates(t_map *map, t_data *scale)
{
	int	side_len;
	int	x;
	int	y;
	int	i;
	int	mod;

	mod = 0;
	i = 0;
	x = 0;
	y = 0;
	scale->max_x = x;
	scale->max_y = y;
	side_len = get_side_len(map->count);
	while (i < map->count)
	{
		map->rooms[i].x = x;
		map->rooms[i].y = y;
		if (x > scale->max_x)
			scale->max_x = x;
		if (y > scale->max_y)
			scale->max_y = y;
		i++;
		mod++;
		if (mod % 2)
			y++;
		else if (y)
			y--;
		if (x > side_len * 4)
		{
			x = 0;
			y += 3;
		}
		x += 3;
	}
} */

void	modify_coordinates_bfs(t_room *rooms, int total_rooms, int level_height)
{
	int	i;
	int	level;
	int	*rooms_per_level;

	if (!level_height)
		write(1, "height = 0\n", 11);
	rooms_per_level = ft_memalloc(sizeof(int) * 10000);
	i = 1;
	if (!rooms_per_level)
		exit(0);
	while (i < total_rooms)
	{
		level = rooms[i].level;
		rooms[i].x = level * 3;
		rooms_per_level[level]++;
		rooms[i].y = rooms_per_level[level] * 5 + (level % 2);
		i++;
	}
}

void	init_bfs(int *level, int *max_rooms_per_level, t_queue **q)
{
	*level = 0;
	*max_rooms_per_level = 0;
	*q = NULL;
}

int	save_levels(t_room *rooms)
{
	int		level;
	int		max_level_height;
	int		i;
	t_queue	*q;

	init_bfs(&level, &max_level_height, &q);
	q = enqueue(0, q, rooms, 0);
	while (q->head)
	{
		i = -1;
		level++;
		while (rooms[q->head->index].adlist[++i])
		{
			if (!rooms[rooms[q->head->index].adlist[i]].level)
			{
				q = enqueue(rooms[q->head->index].adlist[i], q, rooms,
						q->head->index);
				rooms[rooms[q->head->index].adlist[i]].level = level;
			}
		}
		if (i > max_level_height)
			max_level_height = i;
		dequeue(q);
	}
	return (max_level_height);
}

void	bfs_location(t_room *rooms, int total_rooms)
{
	int	level_height;

	level_height = save_levels(rooms);
	modify_coordinates_bfs(rooms, total_rooms, level_height);
}
