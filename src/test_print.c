#include "lemin_visual.h"

void	print_rooms(t_room *room, int room_count)
{
	int	i;

	i = 0;
	while (i < room_count)
	{
		ft_printf("room %s x = %d y = %d\n", room[i].name, room[i].x, room[i].y);
		i++;
	}
}

void	print_room_coord(t_room *room)
{
	int	i;

	i = 0;
	ft_printf("ROOM COORD:\n");
	while (i < 14)
	{
		ft_printf("%d x|%d| y|%d|\n", i, room[i].x, room[i].y);
		i++;
	}
}
