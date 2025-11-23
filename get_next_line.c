/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-jes <lude-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:34:57 by lude-jes          #+#    #+#             */
/*   Updated: 2025/11/23 23:25:26 by lude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stock(int fd, char *stock)
{
	char	*buff;
	char	*temp;
	size_t	bytes_read;
	
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free (stock), NULL);
		buff[bytes_read] = '\0';
		temp = ft_strjoin(stock, buff);
		if (!temp)
			return (free(buff), free (stock), NULL);
		free(stock);
		stock = temp;
		if (ft_strchr(stock, '\n'))
			break;
	}
	free (buff);
	return (stock);
}

char	*take_line(char *stock)
{
	
}

char	*update_stock(char *stock)
{
	
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = read_to_stock(fd, stock);
	if (!stock)
		return (NULL);
	line = take_line(stock);
	stock = update_stock(stock);
	return (line);
}
