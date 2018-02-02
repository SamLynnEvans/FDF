#ifndef FDF_H
#define FDF_H

# define X 0
# define Y 1
# define Z 2
# define C 3


# include "mlx.h"
# include "ft_printf.h"
# include <math.h>
# include <pthread.h>

typedef  struct	s_input
{
	int		dim[2];
	int		**coords;
	int		bpp;
	int		sl;
	int		endian;
	float	alt;
	float	zoom;
	int		y_adj;
	int		**p;
	int		x_adj;
	int		isize;
	int		colour;
	int		peaks;
	float	rot;
	int		width;
	int		height;
	int		x;
	int		y;
	char	*data;
	void	*mlx;
	void	*win;
	void	*img;
}				t_input;

void	fdf(char *coords, t_input *input);
void	print_toscreen(t_input *input);

#endif
