#ifndef LEMIN_VISUAL_H
# define LEMIN_VISUAL_H

# define WIN_W 1400
# define WIN_H 700
# define SEARCH_DELAY 100
# define ANT_DELAY 0
# define MOVE_ANT_DELAY 0
# define PI  3.14159

# define RGBA_VOID "070070070255"
# define RGBA_REVERSED "000120000255"
# define RGBA_VISITED "000000170255"
# define RGBA_PATH "000120000255"
# define RGBA_END "050000050255"

# include "libft.h"
# include "SDL2/SDL.h"
# include <SDL_ttf.h>
# include <math.h>

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_rgb;

typedef struct s_flag
{
	int	algorithm;
	int	mod_position;
}				t_flag;

typedef struct s_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}				t_line;

/*
** visited_from is initialized to -1.
*/

typedef struct s_room
{
	struct s_room	*next;
	char			*name;
	int				index;
	int				prev_room_index;
	int				adlist[10000];
	int				level;
	int				visited;
	int				path;
	int				q;
	int				x;
	int				y;
}				t_room;

typedef struct s_queue
{
	t_room			*head;
	t_room			*tail;
}					t_queue;

typedef struct s_ant
{
	int				i;
	float			x;
	float			y;
	float			dest_x;
	float			dest_y;
	int				wave;
	struct s_ant	*next;
}				t_ant;

typedef struct s_edge
{
	int				src;
	int				dst;
	int				weight;
	t_rgb			rgba;
	struct s_edge	*next;
}				t_edge;

/*
** This is where most of our data is stored. *ants represents the head node
** of a linked list containing information of ants and their movements.
**
** *rooms is an array of t_room elements.
** *edges is the head element of a linked list containing all the edges between
** vertices in the maze.
*/

typedef struct s_map
{
	int		count;
	t_ant	*ants;
	t_room	*rooms;
	t_edge	*edges;
}				t_map;

typedef struct s_data
{
	int	room_count;
	int	room_size;
	int	pos;
	int	win_w;
	int	max_y;
	int	max_x;
	int	ants;
}	t_data;

typedef struct s_pointers
{
	SDL_Texture		*backround;
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	TTF_Font		*font;

}					t_pointers;

/*
** Functions in save_graph.c. These are used to read data from the stdin
** and save it to t_data and t_map data types.
*/

t_data			scale_map(char **input);
t_room			add_room(char *line, int index);
t_edge			*new_edge(t_edge *edges, t_room *rooms, char *src, char *dst);
t_edge			*add_edges(t_room *rooms, char **input, int room_count);
t_map			save_rooms(char **input, int room_count);
int				move_index(char **input, char *find);
SDL_Rect		get_rect(TTF_Font *f, t_room room, int scale, SDL_Rect rect);

/*
**
*/

void			ft_error(const char *str_err);
char			**lemin_realloc(char **input, int len);

/*
** colors.c
*/

void			set_edge_color(t_edge *links, int a, int b, const char *color);
int				rgba_cmp(t_rgb a, t_rgb b);
void			edge_colors(t_edge *edges);
t_rgb			convert_color(const char *str);

/*
** draw_graph.c
*/

void			room_name(SDL_Renderer *renderer, int scale, t_room room, \
					TTF_Font *f);
void			draw_link(SDL_Renderer *renderer, int size, t_map *map, \
					int i[2]);
void			visit_room(t_map *map, char *line);
void			draw_path(t_pointers *p, t_data *scl, t_map *map, char *input);
void			empty_rooms(t_edge *edges, t_room *rooms, int room_count);

/*
** visualize_algorithm.c
*/

void			draw_links(SDL_Renderer *renderer, int size, t_map *map);
t_pointers		*initialize(t_data *scale, t_pointers *sdl, t_room *rooms);
t_room			*find_room(char *name, t_room *list);
t_ant			*ant_destinations(char *line, t_ant *head, \
					t_room *room, int wave);

/*
** Drawing the path finding algorithms.
*/

void			visualize_search(t_pointers *p, t_data *scl, \
					t_map *map, char **input);
void			draw_room(SDL_Renderer *renderer, int size, \
					t_room room, const char *color);

/*
** These functions are used to draw ant movement on the screen
*/

int				move_ants(t_pointers *sdl, t_ant *head, t_data \
					*scale, t_map *map);
void			draw_graph(t_pointers *p, t_data *scl, t_map *map);
SDL_Renderer	*links(SDL_Renderer *renderer, int size, t_map *map);
int				events(void);
int				rgba_cmp(t_rgb a, t_rgb b);

/*
** free_all.c
*/

t_ant			*free_ants(t_ant *head);
void			kill_all(t_pointers *sdl, t_map map, char **input);

t_data			scale_map(char **input);

void			bfs_location(t_room *rooms, int total_rooms);

t_queue			*dequeue(t_queue *q);
t_queue			*enqueue(int index, t_queue *q, t_room *adlist, int prev);
void			free_queue(t_queue *q);
int				room_size(t_data *scale);
void			visualize_ants(t_pointers *sdl, t_data *scale, t_map *map, \
char **input);

#endif
