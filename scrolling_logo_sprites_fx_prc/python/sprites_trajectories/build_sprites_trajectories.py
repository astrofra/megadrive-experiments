import os
import string
import codecs
import ast
import math
from vector3 import Vector3

filename_out			=	"../../src/sprites_traj"
sprite_count			=	32

rotation_steps		 	=	256

traj_x_amplitude 		=	128
traj_y_amplitude 		=	64

sprite_padding			=	16

scr_x_center 			=	160
scr_y_center 			=	128

def  main():
	##	Creates the header
	f = codecs.open(filename_out + '.h', 'w')
	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n\n')

	f.write('#define SPRT_TABLE_LEN ' + str(sprite_count * rotation_steps * 2) + '\n')
	f.write('#define SPRITE_COUNT ' + str(sprite_count) + '\n')
	f.write('#define ROTATION_STEPS ' + str(rotation_steps) + '\n')
	f.write('\n')

	f.write('extern const u16 spr_traj[SPRT_TABLE_LEN];' + '\n')

	f.close()

	##	Creates the C file
	f = codecs.open(filename_out + '.c', 'w')

	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n')
	f.write('#include "' + filename_out.split('/')[-1] + '.h"\n\n')

	f.write('const u16 spr_traj[] =' + '\n')
	f.write('{' + '\n')

	# _str_out = '\t'
	for step in range(rotation_steps):
		f.write('\t/* Step #' + str(step) + ' */\n\t');
		for sprite in range(sprite_count):
			angle = step + sprite_padding * sprite
			x = scr_x_center + int(traj_x_amplitude * math.cos(angle * math.pi / (rotation_steps / 2.0)))
			y = scr_y_center + int(traj_y_amplitude * math.sin(angle * math.pi / (rotation_steps / 2.0)))
			_str_out = str(x) + ',' + str(y) + ','
			f.write(_str_out)

		# if angle%15 == 0:
		f.write('\n')

	f.write('};' + '\n')

	f.close()

main()