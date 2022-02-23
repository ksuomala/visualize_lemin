/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:27:26 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 14:23:40 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

t_ant	*free_ants(t_ant *head)
{
	t_ant	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_memdel((void **)&tmp);
	}
	return (NULL);
}

void	kill_all(t_pointers *sdl, t_map map, char **input)
{
	int		i;
	t_edge	*edge;

	ft_free2d((void **)input);
	SDL_DestroyTexture(sdl->backround);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	free(sdl);
	i = 0;
	while (map.rooms[i].name)
	{
		ft_strdel(&map.rooms[i].name);
		i++;
	}
	free(map.rooms);
	edge = map.edges;
	while (edge)
	{
		edge = map.edges->next;
		ft_memdel((void *)&map.edges);
		map.edges = edge;
	}
	SDL_Quit();
	exit(0);
}
