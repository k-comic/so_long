/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leroy <leroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:36:11 by leroy             #+#    #+#             */
/*   Updated: 2022/05/10 06:58:35 by leroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	alias(t_all *vars, void *img, int row, int line)
{
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		img, row * 64, line * 64);
}

static void	norme_style(t_all *vars)
{
	vars->collect1.path = "images/collect1.xpm";
	vars->collect2.path = "images/collect2.xpm";
	vars->empty.path = "images/empty.xpm";
	vars->enemy1.path = "images/enemy1.xpm";
	vars->enemy2.path = "images/enemy2.xpm";
	vars->exit1.path = "images/exit1.xpm";
	vars->exit2.path = "images/exit2.xpm";
	vars->player1.path = "images/player1.xpm";
	vars->player2.path = "images/player2.xpm";
	vars->wall.path = "images/wall.xpm";
}

static void	norme_style2(t_all *vars)
{
	if (!vars->collect1.img_ptr || !vars->collect2.img_ptr
		|| !vars->empty.img_ptr || !vars->enemy1.img_ptr
		|| !vars->enemy2.img_ptr || !vars->exit1.img_ptr
		|| !vars->exit2.img_ptr || !vars->player1.img_ptr
		|| !vars->player2.img_ptr || !vars->wall.img_ptr)
		ft_exit(1, 4, vars, "init images");
}

void	free_images(t_all *vars)
{
	if (vars->collect1.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->collect1.img_ptr);
	if (vars->collect2.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->collect2.img_ptr);
	if (vars->empty.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->empty.img_ptr);
	if (vars->enemy1.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->enemy1.img_ptr);
	if (vars->enemy2.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->enemy2.img_ptr);
	if (vars->exit1.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->exit1.img_ptr);
	if (vars->exit2.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->exit2.img_ptr);
	if (vars->player1.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->player1.img_ptr);
	if (vars->player2.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->player2.img_ptr);
	if (vars->wall.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->wall.img_ptr);
}

void	init_images(t_all *vars)
{
	norme_style(vars);
	vars->collect1.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->collect1.path, &vars->collect1.width, &vars->collect1.height);
	vars->collect2.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->collect2.path, &vars->collect2.width, &vars->collect2.height);
	vars->empty.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->empty.path, &vars->empty.width, &vars->empty.height);
	vars->enemy1.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->enemy1.path, &vars->enemy1.width, &vars->enemy1.height);
	vars->enemy2.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->enemy2.path, &vars->enemy2.width, &vars->enemy2.height);
	vars->exit1.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->exit1.path, &vars->exit1.width, &vars->exit1.height);
	vars->exit2.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->exit2.path, &vars->exit2.width, &vars->exit2.height);
	vars->player1.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->player1.path, &vars->player1.width, &vars->player1.height);
	vars->player2.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->player2.path, &vars->player2.width, &vars->player2.height);
	vars->wall.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			vars->wall.path, &vars->wall.width, &vars->wall.height);
	norme_style2(vars);
}
