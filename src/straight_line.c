#include "fdf.h"

void	straight_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
	int dx=x2-x1;
	int dy=y2-y1;
	int x=x1;
	int y=y1;

	int e=(2*dy)-dx;
	for (int i=0;i<=dx;i++)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
		while(e>=0)
		{
			y=y+1;
			e=e-(2*dx);
		}
		x=x+1;
		e=e+(2*dy);
	}
}
