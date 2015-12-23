#include <genesis.h>
#include "RSE_version_number.h"

#define RSE_VN_TILE_Y 18

void RSE_displayVersionAndFrequency(void)
{
	u16 vn_tile_x = 5;

	if (SYS_isNTSC())
		BMP_drawText("60Hz", 0, RSE_VN_TILE_Y);
	else
	{
		if (SYS_isPAL())
			BMP_drawText("50Hz", 0, RSE_VN_TILE_Y);
		else
		{
			BMP_drawText("!NO FREQ.", 0, RSE_VN_TILE_Y);
			vn_tile_x = 10;
		}
	}

	BMP_drawText(RSE_VERSION_NUMBER, vn_tile_x, RSE_VN_TILE_Y);
}