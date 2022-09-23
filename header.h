/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 06:05:13 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 05:54:27 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <mlx.h>
# include <time.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*path;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_all
{
	char	**map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	collect1;
	t_img	collect2;
	t_img	empty;
	t_img	enemy1;
	t_img	enemy2;
	t_img	exit1;
	t_img	exit2;
	t_img	player1;
	t_img	player2;
	t_img	wall;
	t_point	player_pos;
	t_point	enemy_pos;
	int		steps;
	int		needed_collect;
	time_t	prev;
}	t_all;

void	free_map(char **map);
char	**ft_check_map(char *path, t_all *vars);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	ft_exit(int err, int lvl, t_all *vars, char *message);
char	*ft_itoa(int n);
int		count_lines(char *path);
int		count_symbols(char **map, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_images(t_all *vars);
void	free_images(t_all *vars);
void	ft_move(t_all *vars, int y, int x);
void	drow_map(t_all *vars);
void	alias(t_all *vars, void *img, int row, int line);

#endif