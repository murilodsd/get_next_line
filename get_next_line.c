/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:37:07 by mde-souz          #+#    #+#             */
/*   Updated: 2024/05/17 11:00:15 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_insert_into_line(char **line, char *buffer)
{
	size_t	s_cat;
	size_t	s_buffer_cat;
	char	*tmp;
	int		i;

	s_buffer_cat = ft_strlen(buffer);
	if (ft_strchr(buffer, '\n'))
		s_buffer_cat += 1 - ft_strlen(ft_strchr(buffer, '\n'));
	s_cat = ft_strlen(*line) + s_buffer_cat;
	tmp = *line;
	*line = (char *)ft_calloc(sizeof(char), s_cat + 1);
	if (!*line)
	{
		free(tmp);
		return (NULL);
	}
	ft_strcpy(*line, tmp);
	free(tmp);
	i = 0;
	while ((*line)[i])
		i++;
	while (*buffer && *buffer != '\n')
		(*line)[i++] = *buffer++;
	(*line)[i++] = *buffer++;
	return (*line);
}

void	ft_move_buffer(char *buffer)
{
	char	*endoftheline;
	int		i;

	endoftheline = ft_strchr(buffer, '\n');
	if (!endoftheline)
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
	else
	{
		i = 0;
		while (endoftheline[1 + i])
			*buffer++ = endoftheline[1 + i++];
		while (*buffer)
			*buffer++ = '\0';
	}
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = (char *)ft_calloc(sizeof(char), 1);
	if (!line)
		return (NULL);
	if (!ft_insert_into_line(&line, buffer))
		return (NULL);
	ft_move_buffer(buffer);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 && *line != '\0')
			return (line);
		else if (bytes_read == 0 || bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		if (!ft_insert_into_line(&line, buffer))
			return (NULL);
		ft_move_buffer(buffer);
	}
	return (line);
}
/* #include <fcntl.h>
#include <stdio.h>
#include <strings.h>

int main(void)
{
	int	fd0,fd1,fd2;
	char	*line;
	
 	fd0 = open("41_with_nl", O_RDWR);
 	fd1 = open("42_with_nl", O_RDWR);
 	fd2 = open("43_with_nl", O_RDWR);
	printf("%s",get_next_line(1000));
	printf("%s",get_next_line(fd0));
	printf("%s",get_next_line(1001));
	printf("%s",get_next_line(fd1));
	printf("%s",get_next_line(1002));
	printf("%s",get_next_line(fd2));
	printf("%s",get_next_line(1003));
	printf("%s",get_next_line(fd0));
	printf("%s",get_next_line(1004));
	//printf("%s",get_next_line(fd));
	//printf("%s",get_next_line(fd));
	//printf("%s",get_next_line(fd));
	//printf("%s",get_next_line(fd));
	//bzero(buffer,BUFFER_SIZE + 1);
 	//bytes_read = read(fd,buffer,BUFFER_SIZE);
	//ft_insert_into_line(&line,buffer);
	//ft_move_buffer(buffer);
	//printf("Linha:\n%s", line);
	//printf("buffer:\n%s\n", buffer);
	//printf("%s\n",buffertoline(buffer,line));
	//next_line = buffertoline(buffer,&line);
	//printf("%s",line);
	//bytes_read = read(fd,buffer,BUFFER_SIZE);
	//buffertoline(buffer,&next_line);
	//printf("%s",next_line);
	//printf("%li\n",bytes_read);
	//bytes_read = read(fd,buffer,32);
	//printf("%s\n",buffer);
	//printf("%li\n",bytes_read);
	close(fd0);
	close(fd1);
	close(fd2);
	return 0;
} */