#include "parser.h"

int	arrlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}
