#include "lemin_visual.h"

int	valid_line(char *line)
{
	if (line[0] != 'L')
		ft_error("invalid input\n");
	if (!ft_atoi(line + 1))
		ft_error("invalid input\n");
	if (!ft_strchr(line, '-'))
		ft_error("invalid input\n");
	return (1);
}

t_ant	*ant_movement(char *line, t_ant *list, t_map *map, int *wave)
{
	if (!ft_strchr(line, 'L') && !ft_strchr(line, '-'))
		return (list);
	list = ant_destinations(line, list, map->rooms, *wave);
	*wave += 1;
	return (list);
}

void	visualize_ants(t_pointers *sdl, t_data *scale, t_map *map,
		char **input)
{
	t_ant	*list;
	int		i;
	int		wave;
	int		pause;

	list = NULL;
	i = move_index(input, "");
	wave = 0;
	while (input[i])
	{
		pause = events();
		if (pause % 2 == 0)
		{
			if (!ft_strcmp("0 0", input[i]) || !valid_line(input[i]))
				break ;
			list = ant_movement(input[i], list, map, &wave);
			SDL_Delay(ANT_DELAY);
			while (move_ants(sdl, list, scale, map))
				SDL_Delay(1);
			i++;
		}
	}
	if (list)
		list = free_ants(list);
	SDL_Delay(3000);
}
