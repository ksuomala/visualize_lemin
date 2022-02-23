/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:05:41 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 14:39:28 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

/*
** Locates the t_room struct with the name matching char *name from the array
** *listand returns a pointer to it. If the room was not found, return NULL.
*/

t_room	*find_room(char *name, t_room *list)
{
	int	i;

	i = 0;
	while (&list[i])
	{
		if (!ft_strcmp(list[i].name, name))
			return (list + i);
		i++;
	}
	return (NULL);
}

t_ant	*new_ant(int nb, int wave, t_room *dst, t_room *start)
{
	t_ant	*new;

	new = ft_memalloc(sizeof(t_ant));
	if (!new)
		ft_error("malloc fail");
	new->i = nb;
	new->x = start->x;
	new->y = start->y;
	new->wave = wave;
	new->dest_x = dst->x;
	new->dest_y = dst->y;
	new->next = NULL;
	return (new);
}

t_ant	*save_move(t_ant *head, t_room *dest, int ant[2], t_room *start)
{
	t_ant	*tmp;

	tmp = head;
	if (!tmp)
		return (new_ant(ant[0], ant[1], dest, start));
	while (tmp->next && tmp->i != ant[0])
		tmp = tmp->next;
	if (tmp->i == ant[0])
	{
		tmp->dest_x = dest->x;
		tmp->dest_y = dest->y;
	}
	else
		tmp->next = new_ant(ant[0], ant[1], dest, start);
	return (head);
}

/*
** ant_destinationsinations recieves the next single line of ant movements as
** char *line and
** the current position of active ants in the maze as a list of t_ant structs.
*/

t_ant	*ant_destinations(char *line, t_ant *head, t_room *room, int wave)
{
	char	**moves;
	char	**dest;
	t_room	*temp;
	int		i;
	int		ant;

	i = -1;
	moves = ft_strsplit(line, ' ');
	if (!moves)
		ft_error("split fail");
	while (moves[++i])
	{
		dest = ft_strsplit(moves[i], '-');
		if (!dest)
			ft_error("split faiil");
		ant = ft_atoi(&dest[0][1]);
		if (dest[1])
			temp = find_room(dest[1], room);
		if (!temp)
			return (NULL);
		head = save_move(head, temp, (int [2]){ant, wave}, room);
		ft_free2d((void **)dest);
	}
	ft_free2d((void **)moves);
	return (head);
}
