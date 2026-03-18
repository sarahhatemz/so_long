/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:27:11 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 17:54:48 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_image
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectable;
	void	*exit;
}			t_image;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		e_count;
	int		c_count;
	int		p_count;
	int		px;
	int		py;
	int		ex;
	int		ey;
	int		moves;
	int		on_exit;
	t_image	img;
}			t_game;

/* map reading */
int			open_map(char *mapname);
void		check_newline(char *line);
int			map_height(int fd);
int			alloc_map(t_game *game);
int			store_line(t_game *game, int fd, int i);
int			storing_map(t_game *game, char *mapname);
void		free_pmap(char **map, int fill);

/* validation */
int			check_rec(t_game *game);
int			checkwalls(t_game *game);
int			check_chars(t_game *game);
char		**copy_map(t_game *game);
void		flood_fill(char **map, int x, int y);
int			check_path(char **map, t_game *game);
int			validation(t_game *game);

/* window / graphics */
int			init_window(t_game *game);
int			load_images(t_game *game);
void		*load_xpm(void *mlx, char *path);
void		put_image(t_game *g, int x, int y);
void		draw_map(t_game *g);

/* game */
void		init_img(t_image *img);
void		init_game(t_game *game);
int			key_hook(int keycode, t_game *g);
int			close_hook(t_game *g);

#endif