/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 04:31:39 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 06:39:22 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_exit(int err, int lvl, t_all *vars, char *message)
{
	if (lvl >= 4)
		free_images(vars);
	if (lvl >= 3)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	if (lvl >= 2)
		mlx_destroy_display(vars->mlx_ptr);
	if (lvl >= 1)
		free_map(vars->map);
	if (err)
	{
		if (errno != 0)
			perror(message);
		else
		{
			write(2, "Error\n", 6);
			write(2, message, ft_strlen(message));
		}
		exit(1);
	}
	else
	{
		if (message)
			write(1, message, ft_strlen(message));
		exit(0);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	count_lines(char *path)
{
	int		fd;
	int		i;
	char	*ptr;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(1, 0, NULL, "count_lines");
	i = 0;
	ptr = get_next_line(fd);
	while (ptr)
	{
		i++;
		free(ptr);
		ptr = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	count_symbols(char **map, char c)
{
	int	i;
	int	j;
	int	ans;

	ans = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'P' &&
				map[i][j] != 'C' && map[i][j] != 'E')
			{
				free_map(map);
				ft_exit(1, 0, NULL, "Invalid symbol in map.\n");
			}
			if (map[i][j] == c)
				ans++;
			j++;
		}
		i++;
	}
	return (ans);
}
