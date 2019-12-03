#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int main(void)
{
    data_t        data;

    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "coucou")))
        return (EXIT_FAILURE);
    mlx_pixel_put(data.mlx_ptr, data.mlx_win, 220, 220, 255);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}