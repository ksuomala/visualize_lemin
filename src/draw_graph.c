#include "lemin_visual.h"

void	room_name(SDL_Renderer *renderer, int scale, t_room room, TTF_Font *f)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Rect	rect;
	char		*nbr;

	nbr = ft_itoa(room.index);
	ft_bzero(&rect, sizeof(SDL_Rect));
	surface = TTF_RenderText_Solid(f, room.name,
			(SDL_Color){255, 255, 255, 255});
	if (!surface || !nbr)
		ft_error("failed to crate surface from font\n");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
		ft_error("Failed to create Texture from text surface\n");
	rect = get_rect(f, room, scale, rect);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(f, nbr, (SDL_Color){150, 150, 150, 255});
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(f, nbr, &rect.w, &rect.h);
	rect.y = rect.y - scale;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void	visit_room(t_map *map, char *line)
{
	char		**visited;
	int			index[2];

	visited = ft_strsplit(line, ' ');
	index[0] = ft_atoi(visited[1]);
	if (line[0] == 'R')
		map->rooms[index[0]].visited = 1;
	else
	{
		index[1] = ft_atoi(visited[2]);
		set_edge_color(map->edges, index[0], index[1], RGBA_VISITED);
	}
	ft_free2d((void **)visited);
}

void	draw_room(SDL_Renderer *renderer, int size, t_room room, \
const char *clr)
{
	SDL_Rect	rect;
	t_rgb		rgba;

	rgba = convert_color(clr);
	rect.h = size;
	rect.w = size;
	rect.x = room.x;
	rect.y = room.y;
	SDL_SetRenderDrawColor(renderer, rgba.r, rgba.g, rgba.b, rgba.a);
	SDL_RenderFillRect(renderer, &rect);
}

void	empty_rooms(t_edge *edges, t_room *rooms, int room_count)
{
	int	i;

	i = 0;
	while (i < room_count)
	{
		rooms[i].visited = -1;
		rooms[i].q = -1;
		rooms[i].path = 0;
		i++;
	}
	edge_colors(edges);
}

void	draw_graph(t_pointers *p, t_data *scl, t_map *map)
{
	int	i;

	SDL_SetRenderDrawColor(p->renderer, 0, 0, 0, 255);
	SDL_RenderClear(p->renderer);
	draw_links(p->renderer, scl->room_size, map);
	i = scl->room_count;
	while (i--)
	{
		if (!i)
			draw_room(p->renderer, scl->room_size, map->rooms[i],
				"255255255255");
		else if (i == scl->room_count - 1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_END);
		else if (map->rooms[i].path)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_PATH);
		else if (map->rooms[i].q == -1 && map->rooms[i].visited == -1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_VOID);
		else if (map->rooms[i].visited > -1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_VISITED);
		if (!scl->pos)
			room_name(p->renderer, scl->room_size, map->rooms[i], p->font);
	}
}
