/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_drow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 04:28:17 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 07:01:07 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_steps(t_all *vars)
{
	char	*str_number;

	str_number = ft_itoa(vars->steps);
	if (!str_number)
		ft_exit(1, 4, vars, "ft_itoa in ft_move");
	write(1, "Steps: ", 7);
	write(1, str_number, ft_strlen(str_number));
	write(1, "\n", 1);
	free(str_number);
}

static void	drow_char(t_all *vars, char c, int row, int line)
{
	if (c == '0')
		alias(vars, vars->empty.img_ptr, row, line);
	if (c == '1')
		alias(vars, vars->wall.img_ptr, row, line);
	if (c == 'P' && vars->prev % 2 == 0)
		alias(vars, vars->player1.img_ptr, row, line);
	if (c == 'P' && vars->prev % 2 == 1)
		alias(vars, vars->player2.img_ptr, row, line);
	if (c == 'C' && vars->prev % 2 == 0)
		alias(vars, vars->collect1.img_ptr, row, line);
	if (c == 'C' && vars->prev % 2 == 1)
		alias(vars, vars->collect2.img_ptr, row, line);
	if (c == 'B' && vars->prev % 2 == 0)
		alias(vars, vars->enemy1.img_ptr, row, line);
	if (c == 'B' && vars->prev % 2 == 1)
		alias(vars, vars->enemy2.img_ptr, row, line);
	if (c == 'E' && vars->needed_collect > 0)
		alias(vars, vars->exit1.img_ptr, row, line);
	if (c == 'E' && vars->needed_collect == 0)
		alias(vars, vars->exit2.img_ptr, row, line);
}

void	drow_map(t_all *vars)
{
	char	*str_number;
	int		line;
	int		row;

	line = 0;
	while (vars->map[line])
	{
		row = 0;
		while (vars->map[line][row])
		{
			drow_char(vars, vars->map[line][row], row, line);
			row++;
		}
		line++;
	}
	str_number = ft_itoa(vars->steps);
	if (!str_number)
		ft_exit(1, 4, vars, "ft_itoa in drow_map");
	mlx_string_put(vars->mlx_ptr, vars->win_ptr, 10, 20, 0x0000FF00, "Steps: ");
	mlx_string_put(vars->mlx_ptr, vars->win_ptr, 50, 20, 65280, str_number);
	free(str_number);
}

static void	drow_map_move(t_all *vars)
{
	char	*str_number;
	int		line;
	int		row;

	str_number = ft_itoa(vars->steps);
	if (!str_number)
		ft_exit(1, 4, vars, "ft_itoa in drow_map_mini");
	line = 4;
	while (line-- >= 2)
		alias(vars, vars->wall.img_ptr, line - 1, 0);
	mlx_string_put(vars->mlx_ptr, vars->win_ptr, 10, 20, 0x0000FF00, "Steps: ");
	mlx_string_put(vars->mlx_ptr, vars->win_ptr, 50, 20, 65280, str_number);
	free(str_number);
	while (vars->map[line])
	{
		row = 0;
		while (vars->map[line][row])
		{
			if (vars->map[line][row] == 'E')
				drow_char(vars, 'E', row, line);
			row++;
		}
		line++;
	}
}

void	ft_move(t_all *vars, int y, int x)
{
	if (vars->map[vars->player_pos.y + y][vars->player_pos.x + x] == 'B')
		ft_exit(0, 4, vars, "Ooops! You lose.\n");
	if (vars->map[vars->player_pos.y + y][vars->player_pos.x + x] == '1'
		|| (vars->map[vars->player_pos.y + y][vars->player_pos.x + x] == 'E'
		&& vars->needed_collect > 0))
		return ;
	vars->steps++;
	print_steps(vars);
	if (vars->map[vars->player_pos.y + y][vars->player_pos.x + x] == 'C')
		vars->needed_collect--;
	if (vars->map[vars->player_pos.y + y][vars->player_pos.x + x] == 'E'
		&& vars->needed_collect == 0)
		ft_exit(0, 4, vars, "Win!\n");
	vars->map[vars->player_pos.y + y][vars->player_pos.x + x] = 'P';
	vars->map[vars->player_pos.y][vars->player_pos.x] = '0';
	alias(vars, vars->empty.img_ptr, vars->player_pos.x, vars->player_pos.y);
	vars->player_pos.y += y;
	vars->player_pos.x += x;
	alias(vars, vars->player1.img_ptr, vars->player_pos.x, vars->player_pos.y);
	drow_map_move(vars);
}
