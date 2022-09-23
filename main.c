/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:59:48 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 06:59:55 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	add_enemy(t_all *vars)
{
	int	line;
	int	row;

	line = 1;
	while (vars->map[line])
	{
		if (line % 3 == 0)
		{
			row = ft_strlen(vars->map[line]) - 1;
			while (row > 0)
			{
				if (vars->map[line][row] == '0'
					&& vars->map[line][row - 1] == '0')
				{
					vars->map[line][row] = 'B';
					vars->enemy_pos.x = row;
					vars->enemy_pos.y = line;
					break ;
				}
				row--;
			}
			break ;
		}
		line++;
	}
}

static int	close_x(t_all *vars)
{
	ft_exit(0, 4, vars, NULL);
	return (0);
}

static int	key_hook(int keycode, t_all *vars)
{
	if (keycode == 0xff1b)
		ft_exit(0, 4, vars, NULL);
	if (keycode == 119)
		ft_move(vars, -1, 0);
	else if (keycode == 97)
		ft_move(vars, 0, -1);
	else if (keycode == 115)
		ft_move(vars, 1, 0);
	else if (keycode == 100)
		ft_move(vars, 0, 1);
	return (0);
}

static int	loop_hook(t_all *vars)
{
	time_t		now;
	static int	where = 1;

	now = time(NULL);
	if (now > vars->prev)
	{
		if (vars->enemy_pos.y != 0)
		{
			if (vars->map[vars->enemy_pos.y][vars->enemy_pos.x + where] != '0'
				&& vars->map[vars->enemy_pos.y][vars->enemy_pos.x + where]
				!= 'P')
				where = -where;
			if (vars->map[vars->enemy_pos.y][vars->enemy_pos.x + where] == 'P')
				ft_exit(0, 4, vars, "Ooops! You lose.\n");
			vars->map[vars->enemy_pos.y][vars->enemy_pos.x] = '0';
			vars->map[vars->enemy_pos.y][vars->enemy_pos.x + where] = 'B';
			vars->enemy_pos.x += where;
		}
		drow_map(vars);
	}
	vars->prev = now;
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	vars;

	vars.steps = 0;
	vars.prev = time(NULL);
	if (argc != 2)
		ft_exit(1, 0, NULL, "Wrong number of arguments.\n");
	vars.map = ft_check_map(argv[1], &vars);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		ft_exit(1, 1, &vars, "mlx_init");
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1500, 800, "so_long");
	if (!vars.mlx_ptr)
		ft_exit(1, 2, &vars, "mlx_init");
	init_images(&vars);
	add_enemy(&vars);
	mlx_hook(vars.win_ptr, 17, 0L, close_x, &vars);
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_loop_hook(vars.mlx_ptr, loop_hook, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
