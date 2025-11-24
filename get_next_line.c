/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-jes <lude-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:34:57 by lude-jes          #+#    #+#             */
/*   Updated: 2025/11/24 17:28:39 by lude-jes         ###   ########.fr       */
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
	char	*line;
	size_t	i;
	size_t	len;
	
	i = 0;
	len = 0;
	if (!stock[len])
		return (NULL);
	while (stock[len] != '\n' && stock[len] != '\0')
		len++;
	if (stock[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stock(char *stock)
{
	char	*updated_stock;
	size_t	i;
	size_t	j;

	if (!stock)
		return (NULL);
	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\n')
		i++;
	if (!stock[i])
		return (free(stock), NULL);
	updated_stock = malloc(ft_strlen(stock) - i + 1);
	if (!updated_stock)
		return (free(stock), NULL);
	while (stock[i])
		updated_stock[j++] = stock[i++];
	updated_stock[j] = '\0';
	free(stock);
	return (updated_stock);
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
	if (!line)
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	stock = update_stock(stock);
	return (line);
}
