/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edges.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:40:45 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 13:57:49 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

void	edge_to_adlist(t_room *lst, int src, int dst)
{
	int	i;

	i = 0;
	while (lst[src].adlist[i])
		i++;
	lst[src].adlist[i] = dst;
	i = 0;
	while (lst[dst].adlist[i])
		i++;
	lst[dst].adlist[i] = src;
}

int	edge_index(t_room *rooms, char *name)
{
	int	i;

	i = 0;
	while (ft_strcmp(name, rooms[i].name))
		i++;
	return (i);
}

t_edge	*new_edge(t_edge *head, t_room *rooms, char *src, char *dst)
{
	t_edge	*new;
	t_edge	*tmp;

	new = ft_memalloc(sizeof(t_edge));
	if (!new)
		ft_error("malloc fail");
	new->src = edge_index(rooms, src);
	new->dst = edge_index(rooms, dst);
	edge_to_adlist(rooms, new->src, new->dst);
	new->rgba = convert_color(RGBA_VOID);
	new->next = NULL;
	if (!head)
		return (new);
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		return (head);
	}
}

/*
** Sets all visited and q values to -1.
*/

t_edge	*add_edges(t_room *rooms, char **input, int room_count)
{
	char	**split;
	t_edge	*head;

	head = NULL;
	while (!ft_strchr(input[room_count], '-'))
		room_count++;
	while (input[room_count] && ft_strchr(input[room_count], '-'))
	{
		split = ft_strsplit(input[room_count], '-');
		if (!split)
			ft_error("split fail");
		head = new_edge(head, rooms, split[0], split[1]);
		free(split);
		room_count++;
	}
	return (head);
}
