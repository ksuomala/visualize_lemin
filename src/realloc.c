#include "lemin_visual.h"

char	**lemin_realloc(char **input, int len)
{
	char	**tmp;

	tmp = ft_memalloc(sizeof(char *) * (len * 2 + 1));
	if (!tmp)
		ft_error("Malloc fail\n");
	tmp = ft_memcpy(tmp, input, sizeof(char *) * len);
	free(input);
	return (tmp);
}
