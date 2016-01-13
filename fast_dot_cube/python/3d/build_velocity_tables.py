import os
import string
import codecs
import ast
import math
from vector3 import Vector3

filename_out			=	"../../src/velocity_table"
max_ampl = 4
angle_fuzziness = 15
# table_size				=	512
# fixed_point_precision 	=	512

# def dumpCosine(_cosine_func, display_name, f):
# 	f.write('const int ' + display_name + '[] =' + '\n')
# 	f.write('{' + '\n')

# 	# _str_out = '\t'
# 	for angle in range(0,table_size):
# 		_cos = int(_cosine_func(angle * math.pi / (table_size / 2.0)) * fixed_point_precision)
# 		_str_out = str(_cos) + ','
# 		f.write(_str_out + '\n')
# 		# if angle%10 == 9:
# 		# 	f.write(_str_out + '\n')
# 		# 	_str_out = '\t'

# 	f.write('};' + '\n')

def is_almost_equal(value, target, fuzzy):
	if value > target - fuzzy and value < target + fuzzy:
		return True
	return False

def find_closest_sprite(x,y):
	base_vector = Vector3(1,0,0)
	sprite_vector = Vector3(x,y,0).normalise()
	angle = (base_vector.dot(sprite_vector))
	angle = math.acos(angle)
	angle = angle * 360.0 / (2 * math.pi)
	angle = int(angle)
	print(angle)

	if is_almost_equal(angle, 135, angle_fuzziness) or is_almost_equal(angle, 135 + 180, angle_fuzziness):
		return 0

	if is_almost_equal(angle, 112, angle_fuzziness) or is_almost_equal(angle, 112 + 180, angle_fuzziness):
		return 1	

	if is_almost_equal(angle, 90, angle_fuzziness) or is_almost_equal(angle, 270, angle_fuzziness):
		return 2

	if is_almost_equal(angle, 67, angle_fuzziness) or is_almost_equal(angle, 67 + 180, angle_fuzziness):
		return 3

	if is_almost_equal(angle, 45, angle_fuzziness) or is_almost_equal(angle, 45 + 180, angle_fuzziness):
		return 4

	if is_almost_equal(angle, 22, angle_fuzziness) or is_almost_equal(angle, 22 + 180, angle_fuzziness):
		return 5		

	if is_almost_equal(angle, 0, angle_fuzziness) or is_almost_equal(angle, 180, angle_fuzziness):
		return 6

	if is_almost_equal(angle, 180 - 22, angle_fuzziness) or is_almost_equal(angle, 360 - 22, angle_fuzziness):
		return 6		

	return -1


def  main():
	##	Creates the header
	# f = codecs.open(filename_out + '.h', 'w')

	# f.write('#define VEL_TABLE_LEN ' + str(table_size) + '\n')
	# f.write('\n')

	# f.write('extern const int tcos[COSINE_TABLE_LEN];' + '\n')
	# f.write('extern const int tsin[COSINE_TABLE_LEN];' + '\n')

	# f.close()

	##	Creates the C file
	f = codecs.open(filename_out + '.c', 'w')

	out_str = "{"

	for y in range(-max_ampl,max_ampl):

		out_str += "\n\t{ "

		for x in range(-max_ampl,max_ampl):
			# nx = (float(x + 8)) / 15.0
			# ny = (float(y + 8)) / 15.0
			sp = find_closest_sprite(x, y)
			out_str += str(sp)
			if x < 8:
				out_str +=  ', '
	
		out_str += "},\n"

	out_str += "};"
	f.write(out_str)

	f.write('\n')

	f.close()

main()