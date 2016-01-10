#include "genesis.h"

#define CUBE_MIN FIX16(-5.0)
#define CUBE_MAX FIX16(5.0)

/* cube.obj */
/* List of vertices */
const Vect3D_f16 vb_cube_vertex_pos[8] =
{
	{CUBE_MIN,	CUBE_MAX,	CUBE_MIN}, /* #0 */
	{CUBE_MAX,	CUBE_MAX,	CUBE_MIN}, /* #1 */
	{CUBE_MAX,	CUBE_MAX,	CUBE_MAX}, /* #2 */
	{CUBE_MIN,	CUBE_MAX,	CUBE_MAX}, /* #3 */
	{CUBE_MIN,	CUBE_MIN,	CUBE_MIN}, /* #4 */
	{CUBE_MAX,	CUBE_MIN,	CUBE_MIN}, /* #5 */
	{CUBE_MAX,	CUBE_MIN,	CUBE_MAX}, /* #6 */
	{CUBE_MIN,	CUBE_MIN,	CUBE_MAX}  /* #7 */
};

/*
      Y
      |

      0------1 --X
     /|     /|
    3------2 |
    | |    | |
    | 4----|-5
    |/     |/ 
    7------6
   /
  Z

*/