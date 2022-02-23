#include "lemin_visual.h"

t_rgb	convert_color(const char *str)
{
	t_rgb	color;
	char	tmp[4];

	tmp[3] = '\0';
	ft_strncpy(tmp, str, 3);
	color.r = ft_atoi(tmp);
	ft_strncpy(tmp, str + 3, 3);
	color.g = ft_atoi(tmp);
	ft_strncpy(tmp, str + 6, 3);
	color.b = ft_atoi(tmp);
	ft_strncpy(tmp, str + 9, 3);
	color.a = ft_atoi(tmp);
	return (color);
}

/*
** If the color values of a and b are the same, return 0. Else return 1.
*/

int	rgba_cmp(t_rgb a, t_rgb b)
{
	if (a.a == b.a
		&& a.r == b.r
		&& a.g == b.g
		&& a.b == b.b)
		return (0);
	else
		return (1);
}

void	set_edge_color(t_edge *links, int a, int b, const char *color)
{
	t_rgb	rgba;

	rgba = convert_color(color);
	while (links)
	{
		if ((links->src == a && links->dst == b)
			|| (links->src == b && links->dst == a))
		{
			links->rgba = rgba;
			return ;
		}
		links = links->next;
	}
}

void	edge_colors(t_edge *edges)
{
	while (edges)
	{
		if (edges->weight)
		{
			if (edges->weight == 1)
				edges->rgba = convert_color(RGBA_REVERSED);
			else if (edges->weight == 2)
				edges->rgba = convert_color(RGBA_REVERSED);
			else if (edges->weight == 3)
				edges->rgba = convert_color(RGBA_PATH);
		}
		else
			edges->rgba = convert_color(RGBA_VOID);
		edges = edges->next;
	}
}
