import os
import string
import codecs
import ast
import math
from vector3 import Vector3

filename_out			=	"../../src/sprites_traj"

rotation_steps		 	=	2048

scr_x_center 			=	160
scr_y_center 			=	100 - 16

hardware_offset			=	0x80

# Classic lissajou
def traj0x(a):
	traj_x_amplitude = 128
	return  scr_x_center + int(traj_x_amplitude * math.cos(3.0 * a * math.pi / (rotation_steps / 4.0)))

def traj0y(a):
	traj_y_amplitude = 64
	return scr_y_center + int(traj_y_amplitude * math.sin(2.0 * a * math.pi / (rotation_steps / 4.0)))

# Pseudo bouncing
def bounce0x(a):
	a *= 2.0
	traj_x_amplitude = 128
	return  scr_x_center + int(traj_x_amplitude * math.cos(a * math.pi / (rotation_steps / 4.0)))

def bounce0y(a):
	s0 = traj0y(a)
	a *= 2.0
	a += (math.pi * 0.353857)
	traj_y_amplitude = 64
	s = math.sin(2.0 * a * math.pi / (rotation_steps / 4.0))
	s *= 1.0 - ((1.0 + math.cos(8.0 * a * math.pi / (rotation_steps / 4.0))) * 0.05)
	s = 1.0 - abs(s)
	s = 2.0 * (s - 0.5)
	s *= (traj_y_amplitude * 1.45)
	s -= 4
	s = scr_y_center + s
	s = (s + s0) * 0.5
	return int(s)

# Alternate Lissajou
def traj1x(a):
	traj_x_amplitude = 128
	return  scr_x_center + int(traj_x_amplitude * math.sin(2.0 * a * math.pi / (rotation_steps / 4.0)))

def traj1y(a):
	traj_y_amplitude = 64
	return scr_y_center + int(traj_y_amplitude * math.cos(5.0 * a * math.pi / (rotation_steps / 4.0)))

# Alternate Lissajou 2
def traj2x(a):
	traj_x_amplitude = 128
	s0 = traj_x_amplitude * math.sin(2.0 * a * math.pi / (rotation_steps / 4.0))
	s1 = traj_x_amplitude * math.cos(9.0 * a * math.pi / (rotation_steps / 4.0))
	s = 0.75 * s0 + 0.25 * s1
	return  scr_x_center + int(s)

def traj2y(a):
	traj_y_amplitude = 64
	s0 = traj_y_amplitude * math.cos(5.0 * a * math.pi / (rotation_steps / 4.0))
	s1 = traj_y_amplitude * math.sin(1.0 * a * math.pi / (rotation_steps / 4.0))
	s = 0.8 * s0 + 0.2 * s1
	s *= 1.15
	s += 4
	return scr_y_center + int(s)

patterns = [	{'name': 'spr_traj', 'func_x': traj0x, 'func_y': traj0y},
				{'name': 'spr_traj_bnc', 'func_x': bounce0x, 'func_y': bounce0y},
				{'name': 'spr_traj_1', 'func_x': traj1x, 'func_y': traj1y},
				{'name': 'spr_traj_2', 'func_x': traj2x, 'func_y': traj2y}
			]

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