/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:30:13 by mde-souz          #+#    #+#             */
/*   Updated: 2024/05/15 20:47:50 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;

	p = s;
	while (n--)
	{
		*p++ = (char)c;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)

{
	void	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_memset(p, '\0', nmemb * size);
	return (p);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && little[j] == big[i + j])
		{
			if (i + j >= len)
				return (0);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (i + j + 1 < size && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j])
		j++;
	if (size <= i)
		return (j + size);
	return (i + j);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (size > 0)
	{
		size--;
		i = 0;
		while (size-- && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
