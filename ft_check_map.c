/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 07:06:02 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 06:57:44 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**ft_read_map(char *path, int n_lines)
{
	char	**map;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(1, 0, NULL, "ft_read_map");
	map = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (!map)
		ft_exit(1, 0, NULL, "ft_read_map");
	i = 0;
	while (i < n_lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
		{
			free_map(map);
			ft_exit(1, 0, NULL, "get_next_line in ft_read_map failed.\n");
		}
		i++;
	}
	close(fd);
	map[i] = NULL;
	return (map);
}

static void	is_rectangle(char **map, int n_lines)
{
	int	i;

	i = 0;
	while (i < n_lines - 1)
	{
		if (ft_strlen(map[i]) != ft_strlen(map[i + 1]))
		{
			free_map(map);
			ft_exit(1, 0, NULL, "Map is not rectangle.\n");
		}
		i++;
	}
}

static void	is_closed(char **map, int n_lines)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_lines)
	{
		j = 0;
		while (map[i][j])
		{
			if (((i == 0 || i == n_lines - 1) && map[i][j] != '1')
				|| map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			{
				free_map(map);
				ft_exit(1, 0, NULL, "Map is not closed.\n");
			}
			j++;
		}
		i++;
	}
}

static void	check_symbols(char **map, t_all *vars)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				vars->player_pos.x = j;
				vars->player_pos.y = i;
			}
			j++;
		}
		i++;
	}
	if (count_symbols(map, 'C') < 1 || count_symbols(map, 'P') != 1
		|| count_symbols(map, 'E') < 1)
	{
		free_map(map);
		ft_exit(1, 0, NULL, "Invalid map configuration.\n");
	}
	vars->needed_collect = count_symbols(map, 'C');
}

char	**ft_check_map(char *path, t_all *vars)
{
	int		n_lines;
	char	**map;

	if (ft_strlen(path) < 5
		|| ft_strncmp(path + (ft_strlen(path) - 4), ".ber", 4) != 0)
		ft_exit(1, 0, NULL, "Not \".ber\" extension.\n");
	n_lines = count_lines(path);
	map = ft_read_map(path, n_lines);
	is_rectangle(map, n_lines);
	is_closed(map, n_lines);
	check_symbols(map, vars);
	return (map);
}
