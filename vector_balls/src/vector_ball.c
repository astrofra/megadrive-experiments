#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"

/*
	Rotate the point list
	on its Z axis.
*/
// void rotatePointsOnAxisY(u16 angle, u16 point_list_size)
// {
// 	u16 loop;

// 	u16 list_idx = 0;
// 	for(loop = 0; loop < point_list_size << 2; loop += 4)
// 	{
// 		//	x' = x cos f - y sin f
// 		t_point_list[list_idx++] = (point_list[loop] * tcos[angle] - point_list[loop + 2] * tsin[angle]) >> 6;
// 		t_point_list[list_idx++] = point_list[loop + 1] << 3;
// 		//	y' = y cos f + x sin f
// 		t_point_list[list_idx++] = (point_list[loop] * tsin[angle] + point_list[loop + 2] * tcos[angle]) >> 6;
// 		t_point_list[list_idx++] = point_list[loop + 3];
// 	}
// }

// void drawPointListToViewport(u16 x_offset, u16 point_list_size)
// {
// 	u16 loop;
// 	int x, y;

// 	for(loop = 0; loop < point_list_size << 2; loop += 4)
// 	{
// 		x = t_point_list[loop] + (DEFAULT_WIDTH >> 1) + x_offset;
// 		y = t_point_list[loop + 1] + (t_point_list[loop + 2] >> 2) + (DISPL_HEIGHT1 >> 1);
// 	}
// }