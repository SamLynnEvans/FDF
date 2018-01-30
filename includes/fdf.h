#ifndef FDF_H
#define FDF_H

# define X 0
# define Y 1
# define Z 2

# include "mlx.h"
# include "ft_printf.h"

typedef  struct	s_input
{
	int		dim[2];
	void	*mlx;
	void	*win;
	int		**coords;
	int		key;
	int		alt;
}				t_input;

void	fdf(char *coords, int dim[2]);

#endif
