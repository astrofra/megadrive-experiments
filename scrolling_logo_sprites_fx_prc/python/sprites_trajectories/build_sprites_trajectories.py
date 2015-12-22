import os
import string
import codecs
import ast
import math
from vector3 import Vector3

filename_out			=	"../../src/sprites_traj"

rotation_steps		 	=	2048

traj_x_amplitude 		=	128
traj_y_amplitude 		=	64

scr_x_center 			=	160
scr_y_center 			=	100 - 16

hardware_offset			=	0x80

def traj0x(angle):
	return  scr_x_center + int(traj_x_amplitude * math.cos(3.0 * angle * math.pi / (rotation_steps / 4.0)))

def traj0y(angle):
	return scr_y_center + int(traj_y_amplitude * math.sin(2.0 * angle * math.pi / (rotation_steps / 4.0)))

patterns = [{'name': 'spr_traj', 'func_x': traj0x, 'func_y': traj0y}]

def  main(): 
	##	Creates the header
	f = codecs.open(filename_out + '.h', 'w')
	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n\n')

	f.write('#define SPRT_TABLE_LEN ' + str(rotation_steps) + '\n')
	f.write('#define SCR_X_CENTER ' + str(scr_x_center + hardware_offset) + '\n')
	f.write('#define SCR_Y_CENTER ' + str(scr_y_center + hardware_offset) + '\n')
	f.write('\n')

	for pat in patterns:
		f.write('extern const u16 ' + pat['name'] + '[SPRT_TABLE_LEN << 1];' + '\n')

	f.close()

	##	Creates the C file
	f = codecs.open(filename_out + '.c', 'w')

	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n')
	f.write('#include "' + filename_out.split('/')[-1] + '.h"\n\n')

	for pat in patterns:
		f.write('const u16 ' + pat['name'] + '[] =' + '\n')
		f.write('{' + '\n')

		# _str_out = '\t'
		for angle in range(rotation_steps):
			f.write('\t/* Step #' + str(angle) + ' */\n\t');
			x = pat['func_x'](angle) # scr_x_center + int(traj_x_amplitude * math.cos(3.0 * angle * math.pi / (rotation_steps / 2.0)))
			y = pat['func_y'](angle) # scr_y_center + int(traj_y_amplitude * math.sin(2.0 * angle * math.pi / (rotation_steps / 2.0)))
			_str_out = str(x + hardware_offset) + ',' + str(y + hardware_offset) + ','
			f.write(_str_out)

			# if angle%15 == 0:
			f.write('\n')

		f.write('};' + '\n')

	f.close()

main()