#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include <kdebug.h>

#define SPR_CUSTOM_ON	// use standard SPR SGDK functions or customs

/*
 
	comment the SPR_CUSTOM_ON for use the native SPR engine
 
 
	Average subtick for								-----------------------
		the native SGDK SPR_update function -------> 0x0000348 / 0x000034B
													-----------------------
 
 
 
 */


#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos

static void workOnSprUpdate();

int main(){
	workOnSprUpdate();
	return 0;
}


/* FROM STANDARD SPR ENGINE */
#define VISIBILITY_ALWAYS_FLAG  0x40000000
#define VISIBILITY_ALWAYS_ON    (VISIBILITY_ALWAYS_FLAG | 0x3FFFFFFF)
#define VISIBILITY_ALWAYS_OFF   (VISIBILITY_ALWAYS_FLAG | 0x00000000)
VDPSprite *VDPSpriteCache = NULL;
static TileCache tcSprite;
static u16 toUpload;
extern vu32 VIntProcess;


/* FROM STANDARD SPR ENGINE */
void RSE_SPR_init(u16 cacheSize)
{
	u16 index;
	u16 size;
	
	// already initialized --> end it first
	
	
//	if (SPR_isInitialized()) SPR_end();
	
	// alloc cache structure memory
	VDPSpriteCache = MEM_alloc(SPRITE_CACHE_SIZE * sizeof(VDPSprite));
	// reset
	toUpload = 0;
	
	// enabled sprite engine VInt processing
	VIntProcess |= PROCESS_SPRITEENGINE_TASK;
	
	size = cacheSize?cacheSize:384;
	// get start tile index for sprite cache (reserve VRAM area just before system font)
	index = TILE_FONTINDEX - size;
	
	// init tile cache engine if needed
	TC_init();
	// and create a tile cache for the sprite
	TC_createCache(&tcSprite, index, size);
}


/* FROM STANDARD SPR ENGINE */
void RSE_computeVisibility(Sprite *sprite)
{
	AnimationFrame *frame = sprite->frame;
	FrameSprite **frameSprites;
	u32 visibility;
	s16 xmin, ymin;
	s16 xmax, ymax;
	s16 fw, fh;
	u16 attr;
	u16 i;
	
	xmin = 0x80 - sprite->x;
	ymin = 0x80 - sprite->y;
	xmax = screenWidth + xmin;
	ymax = screenHeight + ymin;
	fw = frame->w;
	fh = frame->h;
	attr = sprite->attribut;
	
	i = frame->numSprite;
	// start from the last one
	frameSprites = &(frame->frameSprites[i]);
	visibility = 0;
	
	while(i--)
	{
		FrameSprite* frameSprite = *--frameSprites;
		s16 x, y;
		s16 w, h;
		
		w = ((frameSprite->vdpSprite.size_link & 0x0C00) >> 7) + 8;
		h = ((frameSprite->vdpSprite.size_link & 0x0300) >> 5) + 8;
		
		if (attr & TILE_ATTR_VFLIP_MASK)
			y = fh - (frameSprite->vdpSprite.y + h);
		else
			y = frameSprite->vdpSprite.y;
		if (attr & TILE_ATTR_HFLIP_MASK)
			x = fw - (frameSprite->vdpSprite.x + w);
		else
			x = frameSprite->vdpSprite.x;
		
		visibility <<= 1;
		
		// compute visibility
		if (((x + w) > xmin) && (x < xmax) && ((y + h) > ymin) && (y < ymax))
			visibility |= 1;
	}
	
	// store visibility info
	sprite->visibility = visibility;
}

/* FROM STANDARD SPR ENGINE */
static void RSE_SPR_update(Sprite *sprites, u16 num){
	u16 i, j;
	u16 ind;
	Sprite *sprite;
	VDPSprite *cache;
	
	// flush sprite tile cache
	TC_flushCache(&tcSprite);
	
	// do a first pass to re allocate tileset still present in cache
	sprite = sprites;
	i = num;
	while(i--)
	{
		// auto allocation
		if (sprite->fixedIndex == -1)
		{
			s32 visibility = sprite->visibility;
			
			// don't run for disabled sprite
			if (visibility != VISIBILITY_ALWAYS_OFF)
			{
				AnimationFrame *frame;
				FrameSprite **frameSprites;
				
				frame = sprite->frame;
				j = frame->numSprite;
				frameSprites = frame->frameSprites;
				
				// need update ?
				if (visibility == -1)
				{
					RSE_computeVisibility(sprite);
					visibility = sprite->visibility;
				}
				
				while(j--)
				{
					// sprite visible --> try fast re alloc
					if (visibility & 1)
						TC_reAlloc(&tcSprite, (*frameSprites)->tileset);
					
					frameSprites++;
					visibility >>= 1;
				}
			}
		}
		
		sprite++;
	}
	
	cache = VDPSpriteCache;
	
	ind = 0;
	sprite = sprites;
	i = num;
	while(i--)
	{
		u16 timer;
		s32 visibility;
		
		timer = sprite->timer;
		// handle frame animation
		if (timer)
		{
			// timer elapsed --> next frame
			if (--timer == 0) SPR_nextFrame(sprite);
			// just update remaining timer
			else sprite->timer = timer;
		}
		
		visibility = sprite->visibility;
		
		// don't run for disabled sprite
		if (visibility != VISIBILITY_ALWAYS_OFF)
		{
			AnimationFrame *frame;
			FrameSprite **frameSprites;
			u16 attr;
			s16 fw, fh;
			s16 vramInd;
			
			// need update ?
			if (visibility == -1)
			{
				RSE_computeVisibility(sprite);
				visibility = sprite->visibility;
			}
			
			frame = sprite->frame;
			attr = sprite->attribut;
			vramInd = sprite->fixedIndex;
			j = frame->numSprite;
			frameSprites = frame->frameSprites;
			fw = frame->w;
			fh = frame->h;
			
			if (vramInd == -1)
			{
				// auto allocation
				while(visibility && j--)
				{
					FrameSprite* frameSprite = *frameSprites++;
					
					// sprite visible ?
					if (visibility & 1)
					{
						if (attr & TILE_ATTR_VFLIP_MASK)
						{
							s16 sh = ((frameSprite->vdpSprite.size_link & 0x0300) >> 5) + 8;
							cache->y = sprite->y + (fh - (frameSprite->vdpSprite.y + sh));
						}
						else
							cache->y = sprite->y + frameSprite->vdpSprite.y;
						
						cache->size_link = frameSprite->vdpSprite.size_link | ++ind;
						cache->attr = (frameSprite->vdpSprite.attr ^ attr) +
						TC_alloc(&tcSprite, frameSprite->tileset, UPLOAD_VINT);
						
						if (attr & TILE_ATTR_HFLIP_MASK)
						{
							s16 sw = ((frameSprite->vdpSprite.size_link & 0x0C00) >> 7) + 8;
							cache->x = sprite->x + (fw - (frameSprite->vdpSprite.x + sw));
						}
						else
							cache->x = sprite->x + frameSprite->vdpSprite.x;
						
						cache++;
					}
					
					visibility >>= 1;
				}
			}
			else
			{
				// fixed allocation
				while(visibility && j--)
				{
					FrameSprite* frameSprite = *frameSprites++;
					
					// sprite visible ?
					if (visibility & 1)
					{
						if (attr & TILE_ATTR_VFLIP_MASK)
						{
							s16 sh = ((frameSprite->vdpSprite.size_link & 0x0300) >> 5) + 8;
							cache->y = sprite->y + (fh - (frameSprite->vdpSprite.y + sh));
						}
						else
							cache->y = sprite->y + frameSprite->vdpSprite.y;
						
						cache->size_link = frameSprite->vdpSprite.size_link | ++ind;
						cache->attr = (frameSprite->vdpSprite.attr ^ attr) + vramInd;
						
						if (attr & TILE_ATTR_HFLIP_MASK)
						{
							s16 sw = ((frameSprite->vdpSprite.size_link & 0x0C00) >> 7) + 8;
							cache->x = sprite->x + (fw - (frameSprite->vdpSprite.x + sw));
						}
						else
							cache->x = sprite->x + frameSprite->vdpSprite.x;
						
						cache++;
					}
					
					visibility >>= 1;
					vramInd += frameSprite->tileset->numTile;
				}
			}
		}
		
		sprite++;
	}
	
	// if at least one sprite is visible
	if (ind)
	{
		cache--;
		// end sprite list
		cache->size_link &= 0xFF00;
		// save number of sprite to upload
		toUpload = ind;
	}
	else
	{
		// single sprite not visible so nothing is displayed
		cache->y = 0;
		cache->size_link = 0;
		
		toUpload = 1;
	}

	//SPR_doVBlankProcess()
	if (toUpload)
	{
		// send to VRAM
		VDP_doVRamDMA((u32) VDPSpriteCache, VDP_getSpriteListAddress(), (toUpload * sizeof(VDPSprite)) / 2);
		toUpload = 0;
	}


}
static void workOnSprUpdate(){
	u32 totalSubtick = 0;
	u32 vblCount = 0;
	
	u16 loop, j;
	u16 zsort_switch = 0;
	Sprite sprites[MAX_VECTOR_BALL];
	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
	u16 angle = 0;

	static void drawVectorBalls(Sprite *sprites, u16 rx, u16 ry)
	{
		u16 loop;
		short x, y, z, xc, yc, zc;
		Vect3D_f16 _vtx, t_vtx[BALL_COUNT];
		fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
		u16 distance = 1100;
		short x_screen, y_screen;

		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen = (VDP_getScreenWidth() - 32) >> 1;
		y_screen = (VDP_getScreenHeight() - 32) >> 1;

		xc = cosFix32(rx << 4) >> 2;
		yc = sinFix32(rx << 3) >> 2;
		zc = sinFix32(rx << 2) >> 2;

		/* precalculate the rotation */
		_cosx = cosFix32(rx);
		_sinx = sinFix32(rx);
		_cosy = cosFix32(ry);
		_siny = sinFix32(ry);
		cs = fix32Mul(_cosx, _siny);
		ss = fix32Mul(_siny, _sinx);
		cc = fix32Mul(_cosx, _cosy);
		sc = fix32Mul(_sinx, _cosy);

		/* rotate the vector balls */
		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			_vtx = VECTOR_BALL_ARRAY[loop];

			//	2D rotation (on X and Y axis)
		    t_vtx[loop].x = fix32Add(fix32Mul(_vtx.x, _sinx), fix32Mul(_vtx.y, _cosx));
		    t_vtx[loop].y = fix32Sub(fix32Mul(_vtx.x, cs), fix32Add(fix32Mul(_vtx.y, ss), fix32Mul(_vtx.z, _cosy)));
		    t_vtx[loop].z = fix32Sub(fix32Mul(_vtx.x, cc), fix32Mul(_vtx.y, sc) - fix32Mul(_vtx.z, _siny));

		    t_vtx[loop].x += xc;
		    t_vtx[loop].y += yc;
		    t_vtx[loop].z += zc;
		}

		/* Z-sort the vector balls */
		if (zsort_switch == 0)
		{
			for(loop = 0; loop < BALL_COUNT; loop++)
			{
			    //	Fill the sort table
			    vball_zsort[loop].index = loop;
			    vball_zsort[loop].value = t_vtx[loop].z;
			}

			QuickSort(BALL_COUNT, vball_zsort);
		}

		//	Count 16 frames until the next depth sort
		zsort_switch++;
		zsort_switch &= 0xF;

		/* Display the vector balls using sprites */
		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			j = vball_zsort[loop].index;

			//	Classic 3D -> 2D projection
		    x = (t_vtx[j].x << 10) / (t_vtx[j].z + distance);
		    y = (t_vtx[j].y << 10) / (t_vtx[j].z + distance);		

			x >>= 3;
			y >>= 3;

			z = t_vtx[j].z;
			if (z < FIX32(0.0))
				z = FIX32(0.0);

			z >>= 5;

			if (z > 7)
				z = 7;

			SPR_setPosition(&sprites[loop], x_screen + x, y_screen + y);
			SPR_setFrame(&sprites[loop], z);
		}

		/* Update the whole list of sprites */
		u32 startSubTick = getSubTick();
		#ifndef SPR_CUSTOM_ON
		SPR_update(sprites, BALL_COUNT);
		#endif
		#ifdef SPR_CUSTOM_ON
		RSE_SPR_update(sprites, BALL_COUNT);
		#endif
		totalSubtick += getSubTick() - startSubTick; //compute the total subTick passed in SPR_update function
	}
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	SYS_disableInts();

	/* Set the palette taken from the vector ball sprite */
	VDP_setPalette(PAL2, ball_metal.palette->data);
	#ifndef SPR_CUSTOM_ON
	SPR_init(MAX_VECTOR_BALL);
	#endif
	#ifdef SPR_CUSTOM_ON
	RSE_SPR_init(MAX_VECTOR_BALL);
	#endif
	

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < BALL_COUNT; loop++)
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));

	#ifndef SPR_CUSTOM_ON
    SPR_update(sprites, BALL_COUNT);
	#endif
	#ifdef SPR_CUSTOM_ON
	RSE_SPR_update(sprites, BALL_COUNT);
	#endif

	SYS_enableInts();

	while (TRUE){
		VDP_waitVSync();
		vblCount++;
		BMP_showFPS(1);
		drawVectorBalls(sprites, angle, angle << 1);
		KDebug_AlertNumber(totalSubtick / vblCount); //average subtick in spr_update
		angle++;
	}
}