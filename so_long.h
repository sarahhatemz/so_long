#ifndef SO_LONG_H
#define SO_LONG_H


#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <string.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

typedef struct s_image
{
    void *wall;
    void *floor;
    void *player;
    void *collectable;
    void *exit;
}   t_image;

typedef struct s_game
{
    void    *mlx;
    void    *win;

    char    **map;
    int     width;
    int     height;

    int     e_count;
    int     c_count;
    int     p_count;

    int     px;
    int     py;

    int     moves;

    t_image img;
}   t_game;

int key_hook(int keycode, t_game *g);
int close_hook(t_game *g);
void draw_map(t_game *g);
void free_pmap(char **map, int fill);
void init_img(t_image *img);
void init_game(t_game *g);
void check_newline(char *line);
int map_height(int fd);
int open_map(char *mapname);
int check_rec(t_game *game);
void init_img(t_image *img);
void init_game(t_game *game);
int	storing_map(t_game *game, char *mapname);
int	check_chars(t_game *game);
int checkwalls(t_game *game);
int check_rec(t_game *game);
void init_img(t_image *img);
void init_game(t_game *game);


#endif