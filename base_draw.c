//
// Created by Grass Emerald on 06/01/2020.
//

#include "fdf.h"

void draw_circle(t_point *half, t_pix start, int radius)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while(y >= 0)
	{
		pixel_to_image(half, start.x + x, start.y + y, start.color);
		pixel_to_image(half, start.x + x, start.y - y, start.color);
		pixel_to_image(half, start.x - x, start.y + y, start.color);
		pixel_to_image(half, start.x - x, start.y - y, start.color);
		error = 2 * (delta + y) - 1;
		if(delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if(delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}