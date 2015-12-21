import os
import string
import codecs
import ast
import math
from vector3 import Vector3

filename_out			=	"../../src/sprites_traj"

rotation_steps		 	=	1024

traj_x_amplitude 		=	128
traj_y_amplitude 		=	64

sprite_padding			=	8

scr_x_center 			=	160
scr_y_center 			=	100 - 16

hardware_offset			=	0x80

def  main():
	##	Creates the header
	f = codecs.open(filename_out + '.h', 'w')
	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n\n')

	f.write('#define SPRT_TABLE_LEN ' + str(rotation_steps * 2) + '\n')
	f.write('#define SCR_X_CENTER ' + str(scr_x_center + hardware_offset) + '\n')
	f.write('#define SCR_Y_CENTER ' + str(scr_y_center + hardware_offset) + '\n')
	f.write('\n')

	f.write('extern const u16 spr_traj[SPRT_TABLE_LEN << 1];' + '\n')

	f.close()

	##	Creates the C file
	f = codecs.open(filename_out + '.c', 'w')

	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n')
	f.write('#include "' + filename_out.split('/')[-1] + '.h"\n\n')

	f.write('const u16 spr_traj[] =' + '\n')
	f.write('{' + '\n')

	# _str_out = '\t'
	for angle in range(rotation_steps * 2):
		f.write('\t/* Step #' + str(angle) + ' */\n\t');
		x = scr_x_center + int(traj_x_amplitude * math.cos(3.0 * angle * math.pi / (rotation_steps / 2.0)))
		y = scr_y_center + int(traj_y_amplitude * math.sin(2.0 * angle * math.pi / (rotation_steps / 2.0)))
		_str_out = str(x + hardware_offset) + ',' + str(y + hardware_offset) + ','
		f.write(_str_out)

		# if angle%15 == 0:
		f.write('\n')

	f.write('};' + '\n')

	f.close()

main()