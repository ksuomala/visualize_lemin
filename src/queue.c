/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:48 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 14:24:52 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

void	free_queue(t_queue *q)
{
	while (q->head)
		dequeue(q);
	ft_memdel((void **)&q);
}

int	is_queued(int index, t_queue *q)
{
	t_room	*tmp;

	if (!q)
		return (0);
	tmp = q->head;
	while (tmp)
	{
		if (tmp->index == index)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** Add room to the queue
*/

t_queue	*enqueue(int index, t_queue *q, t_room *rooms, int prev)
{
	t_room	*new;

	if (!q)
		q = ft_memalloc(sizeof(t_queue));
	if (!q)
		exit(0);
	new = ft_memdup(&rooms[index], sizeof(t_room));
	if (!new)
		exit(0);
	new->prev_room_index = prev;
	new->index = index;
	new->next = NULL;
	if (!q->head)
		q->head = new;
	if (!q->tail)
		q->tail = new;
	else
	{
		q->tail->next = new;
		q->tail = new;
	}
	return (q);
}

/*
** Delete room from the queue
*/

t_queue	*dequeue(t_queue *q)
{
	t_room	*tmp;

	if (!q->head)
		return (NULL);
	tmp = q->head;
	q->head = q->head->next;
	ft_memdel((void **)&tmp);
	if (!q->head)
		q->tail = NULL;
	return (q);
}
