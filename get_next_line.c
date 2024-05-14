/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:37:07 by mde-souz          #+#    #+#             */
/*   Updated: 2024/05/14 08:32:30 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	buffertoline(char *buffer, char **line)
{
	char	*tmp;
	char 	*endofline;
	endofline = ft_strnstr(buffer,"\n",BUFFER_SIZE);
	if (endofline)
	{
		if (!*line)
		{
			if (ft_strnstr(buffer,"\n",BUFFER_SIZE))
			{
				*line = (char *)malloc(sizeof(char) * (endofline - buffer + 1) + 1);
				if (!*line)
					return (NULL);
				ft_strlcpy(*line,buffer,(endofline - buffer + 1) + 1);
				ft_strlcpy(buffer,endofline + 1,BUFFER_SIZE - (endofline - buffer));
				ft_memset(buffer, '\0', endofline - buffer);
			}
		}
		else
		{
			tmp = *line;
			*line = (char *)malloc(sizeof(char) * ft_strlen(*line) + (endofline - buffer + 1) + 1);
			if (!*line)
			{
				free(tmp);
				return (NULL);
			}
			ft_strlcpy(*line,tmp,ft_strlen(tmp) + 1);
			ft_strlcat(*line,buffer,endofline - buffer + 1);
			ft_strlcpy(buffer,endofline + 1,BUFFER_SIZE - (endofline - buffer));
			ft_memset(buffer, '\0', endofline - buffer);
		}
	}
	else
	{
		tmp = *line;
		*line = (char *)malloc(sizeof(char) * ft_strlen(*line) + BUFFER_SIZE + 1);
		if (!line)
		{
			free(tmp);
			return (NULL);
		}
		ft_strcpy(*line,tmp);
		free(tmp);
		ft_strlcat(*line,buffer,ft_strlen(*line) + BUFFER_SIZE + 1);
		return (NULL);
	}
}

void	*ft_insert_into_line(char **line, char *buffer)
{
	size_t	s_cat;
	size_t	s_buffer_cat;
	char * tmp;
	int	i;
	
	if (ft_strchr(buffer,'\n'))
		s_buffer_cat = ft_strlen(buffer) - ft_strlen(ft_strchr(buffer,'\n')) + 1;
	else
		s_buffer_cat = ft_strlen(buffer);
	s_cat = ft_strlen(*line) + s_buffer_cat;
	tmp = *line;
	*line = (char *)calloc(sizeof(char), s_cat + 1);
		if (!*line)
		{
			free(tmp);
			return (NULL);
		}
	ft_strcpy(*line,tmp);
	free(tmp);
	i = 0;
	while ((*line)[i])
		i++;
	while (*buffer && *buffer != '\n')
		(*line)[i++] = *buffer++;
	(*line)[i++] = *buffer++;
	return (line);
}

void	ft_move_buffer(char *buffer)
{
	char	*endoftheline;
	int		i;
	
	endoftheline = ft_strchr(buffer,'\n');
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

char *get_next_line(int fd)
{
	ssize_t bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	static int	is_first_time;
	char	*line;
	char 	*endofline;
	
	is_first_time = 1;
	if (is_first_time)
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
	line = (char *)calloc(sizeof(char),1);
	if(!line)
		return (NULL);
	if (!ft_insert_into_line(&line, buffer))
			return (NULL);
	ft_move_buffer(buffer);
	while (!ft_strchr(line,'\n'))
	{
		bytes_read = read(fd,buffer,BUFFER_SIZE);
		if (bytes_read == 0)
			return (NULL);
		if (!ft_insert_into_line(&line, buffer))
			return (NULL);
		ft_move_buffer(buffer);
	}
	is_first_time = 0;
	return(line);
}
/* #include <fcntl.h>
#include <stdio.h>
#include <strings.h> */
#include <strings.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p;

	p = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
int main(void)
{
	int	fd;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	line = ft_strdup("teste ja escrito");
	ssize_t bytes_read;
	char	*next_line;
	
 	fd = open("meu_texto.txt", O_RDONLY);
 	//fd = open("texto_uma_linha.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
/*	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd)); */
	//bzero(buffer,BUFFER_SIZE + 1);
 	//bytes_read = read(fd,buffer,BUFFER_SIZE);
	//ft_insert_into_line(&line,buffer);
	//ft_move_buffer(buffer);
	//printf("Linha:\n%s", line);
	//printf("buffer:\n%s\n", buffer);
	//printf("%s\n",buffertoline(buffer,line));
	/* next_line = buffertoline(buffer,&line);
	printf("%s",line);
	bytes_read = read(fd,buffer,BUFFER_SIZE);
	buffertoline(buffer,&next_line);
	printf("%s",next_line); */
	//printf("%li\n",bytes_read);
/*	bytes_read = read(fd,buffer,32);
	printf("%s\n",buffer);
	printf("%li\n",bytes_read); */
	close(fd);
	return 0;
}
