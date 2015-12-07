    .globl   setVDPPalette
    .type    setVDPPalette, @function

Palette:
   dc.w 0x0000 
   dc.w 0x000E 
   dc.w 0x00E0 
   dc.w 0x0E00 
   dc.w 0x0000 
   dc.w 0x0EEE 
   dc.w 0x00EE 
   dc.w 0x008E 
   dc.w 0x0E0E 
   dc.w 0x0808 
   dc.w 0x0444 
   dc.w 0x0888 
   dc.w 0x0EE0 
   dc.w 0x000A 
   dc.w 0x0600 
   dc.w 0x0060 
	
setVDPPalette:
.set	GFX_CTRL,0xC00004
.set	GFX_DATA,0xC00000
		
		*	000000 – VRAM Read		0x00
		*	100000 – VRAM Write		0x10
		*	000100 – CRAM Read		0x04
		*	110000 – CRAM Write		0x18
		*	001000 – VSRAM Read		
		*	101000 – VSRAM Write	0x14
		
		* 1000 0000 0000 0000 0000 0000 0000 0011
		* VRAM W						ADDR

	move.l #0x40000003, GFX_CTRL
	move.w #0x8F02, GFX_CTRL
	move.l #0xC0000003, GFX_CTRL
	
	lea Palette, %a0          
	move.l #0x07, %d0         
 
loop:
	move.l (%a0)+, 0x00C00000 
	dbra %d0, loop