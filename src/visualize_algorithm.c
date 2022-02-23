#include "lemin_visual.h"

void	add_edge_weight(t_edge *links, int a, int b)
{
	t_edge	*tmp;

	tmp = NULL;
	if (!links)
		return ;
	while (links)
	{
		if ((links->src == a && links->dst == b)
			|| (links->src == b && links->dst == a))
		{
			tmp = links;
			break ;
		}
		links = links->next;
	}
	if ((!tmp->weight))
		tmp->weight = 1;
	else
		tmp->weight = 0;
}

void	draw_link(SDL_Renderer *renderer, int size, t_map *map, int i[2])
{
	t_line	line;

	line.start_x = map->rooms[i[0]].x + size / 2;
	line.start_y = map->rooms[i[0]].y + size / 2;
	line.end_x = map->rooms[i[1]].x + size / 2;
	line.end_y = map->rooms[i[1]].y + size / 2;
	SDL_RenderDrawLine(renderer, line.start_x - 1, line.start_y,
		line.end_x - 1, line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y,
		line.end_x, line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x + 1, line.start_y,
		line.end_x + 1, line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y - 1,
		line.end_x, line.end_y - 1);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y + 1,
		line.end_x, line.end_y + 1);
}

void	draw_path(t_pointers *p, t_data *scl, t_map *map, char *input)
{
	char		**split;
	int			*path;
	int			i;
	static int	path_no;

	path_no++;
	i = -1;
	split = ft_strsplit(input, '|');
	if (!split)
		ft_error("split fail\n");
	path = ft_memalloc(sizeof(int) * scl->room_count);
	if (!path)
		ft_error("malloc fail\n");
	while (split[++i])
		path[i] = ft_atoi(split[i]);
	set_edge_color(map->edges, path[--i], scl->room_count - 1, RGBA_PATH);
	while (i--)
	{
		draw_graph(p, scl, map);
		set_edge_color(map->edges, path[i], path[i + 1], RGBA_PATH);
		if (ft_strstr(input, "MOD"))
			add_edge_weight(map->edges, path[i], path[i + 1]);
	}
	set_edge_color(map->edges, 0, path[i], RGBA_PATH);
	ft_n(1);
}

void	draw_links(SDL_Renderer *renderer, int size, t_map *map)
{
	t_edge	*links;

	links = map->edges;
	while (links)
	{
		SDL_SetRenderDrawColor(renderer, links->rgba.r, links->rgba.g,
			links->rgba.b, links->rgba.a);
		draw_link(renderer, size, map, (int [2]){links->src, links->dst});
		links = links->next;
	}
}

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	visualize_search(t_pointers *p, t_data *scl, t_map *map, char **input)
{
	int				i;
	int				pause;

	i = move_index(input, "");
	draw_graph(p, scl, map);
	SDL_RenderPresent(p->renderer);
	while (ft_strcmp(input[i], "") && !ft_strstr(input[i], " L"))
	{
		pause = events();
		if (pause % 2 == 0)
		{
			if (!ft_strcmp(input[i], "SEARCH"))
				empty_rooms(map->edges, map->rooms, scl->room_count);
			else if (ft_strchr(input[i], '|'))
				draw_path(p, scl, map, input[i]);
			else if (ft_strchr(input[i], ' '))
				visit_room(map, input[i]);
			i++;
			draw_graph(p, scl, map);
			SDL_RenderPresent(p->renderer);
			SDL_Delay(SEARCH_DELAY);
		}
	}
	ft_n(1);
}
