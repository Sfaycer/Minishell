/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:23:24 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 12:26:26 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	clear_data(char **data)
{
	free(*data);
	*data = 0;
}

static int	output_n_trim_line(char **data, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*data)[i] != '\n' && (*data)[i] != 0)
		i++;
	if ((*data)[i] == '\n')
	{
		*line = ft_substr(*data, 0, i);
		temp = ft_strdup(&((*data)[i + 1]));
		free(*data);
		*data = temp;
		if ((*data)[0] == 0)
			clear_data(data);
	}
	else
	{
		*line = ft_strdup(*data);
		clear_data(data);
		return (0);
	}
	return (1);
}

static int	gnl_fate(char **line, int rbytes, char **data)
{
	if (rbytes < 0)
		return (-1);
	else if (rbytes == 0 && *data == 0)
	{
		*line = (char *)malloc(sizeof(char));
		*line[0] = 0;
		return (0);
	}
	else
		return (output_n_trim_line(data, line));
}

int	get_next_line(int fd, char **line)
{
	static char	*data[256];
	char		buf[BUFFER_SIZE + 1];
	int			rbytes;
	char		*temp;

	if (fd < 0 || line == 0 || BUFFER_SIZE == 0)
		return (-1);
	rbytes = read(fd, buf, BUFFER_SIZE);
	while (rbytes > 0)
	{
		buf[rbytes] = 0;
		if (data[fd] == 0)
			data[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(data[fd], buf);
			free(data[fd]);
			data[fd] = temp;
		}
		if (ft_strchr(data[fd], '\n'))
			break ;
		rbytes = read(fd, buf, BUFFER_SIZE);
	}
	return (gnl_fate(line, rbytes, &data[fd]));
}
