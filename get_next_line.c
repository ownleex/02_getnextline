/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:48:01 by ayarmaya          #+#    #+#             */
/*   Updated: 2023/12/12 17:04:39 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_next(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_print_line(char **temp)
{
	int		cursor;
	char	*line;
	char	*str;

	if (!*temp)
		return (NULL);
	str = *temp;
	cursor = 0;
	while (str[cursor] && str[cursor] != '\n')
		cursor++;
	if (str[cursor] == '\n')
		cursor++;
	line = ft_strdup(str, cursor);
	*temp = ft_strdup(str + cursor, ft_strlen(str + cursor));
	if (str)
		free(str);
	str = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*buffer;
	int				n_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(str), str = NULL, NULL);
	if (ft_next(str))
		return (ft_print_line(&str));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	n_read = 1;
	while (n_read > 0)
	{
		n_read = read(fd, buffer, BUFFER_SIZE);
		buffer[n_read] = 0;
		str = ft_strjoin(str, buffer);
		if (ft_next(str))
			break ;
	}
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (ft_print_line(&str));
}

int main()
{
    int fd;
    char *line;

    // Ouverture du fichier en lecture seule
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Lecture et affichage de chaque ligne du fichier
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    // Fermeture du fichier
    close(fd);
    return 0;
}
