/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:48:47 by ayarmaya          #+#    #+#             */
/*   Updated: 2023/12/19 18:35:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(char *str, size_t len)
{
	char	*result;
	size_t	i;

	if (!str || !len)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(char *str, char *buffer)
{
	size_t	i;
	size_t	len;
	char	*result;

	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer);
	if (!str)
		return (ft_strndup(buffer, len));
	len = len + ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	len = 0;
	i = 0;
	while (str[i])
		result[len++] = str[i++];
	i = 0;
	while (buffer[i])
		result[len++] = buffer[i++];
	result[len] = '\0';
	free(str);
	str = NULL;
	return (result);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
