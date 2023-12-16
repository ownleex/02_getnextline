/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:48:01 by ayarmaya          #+#    #+#             */
/*   Updated: 2023/12/16 03:14:49 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_next(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i++])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_print_line(char **temp)
{
	int		cursor;
	char	*line;
	char	*temp_str;

	if (!*temp)
		return (NULL);
	temp_str = *temp;
	cursor = 0;
	while (temp_str[cursor] && temp_str[cursor] != '\n')
		cursor++;
	if (temp_str[cursor] == '\n')
		cursor++;
	line = ft_strndup(temp_str, cursor);
	*temp = ft_strndup(temp_str + cursor, ft_strlen(temp_str + cursor));
	if (temp_str)
		free(temp_str);
	temp_str = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	int			n_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n_read = 1;
	while (n_read > 0)
	{
		n_read = read(fd, buffer, BUFFER_SIZE);
		if (n_read < 0)
		{
			free(buffer);
			return (free(str), str = NULL, NULL);
		}
		buffer[n_read] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_next(str) || n_read == 0)
			break ;
	}
	free(buffer);
	return (ft_print_line(&str));
}

/*
int	main()
{
	int		fd;
	char	*line;

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


int     main(void)
{
        int fd = open("test.txt", O_RDONLY);
        char    *str;
        
        while (1)
        {
                str = get_next_line(fd);
                if (str == NULL)
                        break;
                printf("%s", str);
                free(str);
        }
        return (0);
}
*/
