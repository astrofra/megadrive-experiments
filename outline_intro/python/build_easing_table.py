import os
import string
import codecs
import ast
import math

filename_out			=	"../easing_table"
table_size				=	1024

def dumpCosine(_cosine_func, display_name, f):
	f.write('const u16 ' + display_name + '[] =' + '\n')
	f.write('{' + '\n')

	cr = 0
	for angle in range(0,table_size):
		_cos = int(_cosine_func(angle / table_size) * table_size)
		_str_out = str(_cos) + ', '
		if cr > 16:
			_str_out += '\n'
			cr = 0
		f.write('\t' + _str_out)
		cr += 1

	if cr != 0:
		f.write('\n')		

	f.write('};' + '\n')

def easing(x):
	return (x * x * (3 - 2 * x))

def  main():
	##	Creates the header
	f = codecs.open(filename_out + '.h', 'w')

	f.write('#include <genesis.h>\n\n')
	f.write('#define EASING_TABLE_LEN ' + str(table_size) + '\n')
	f.write('\n')

	f.write('const u16 easing_table[EASING_TABLE_LEN];' + '\n')

	f.close()

	##	Creates the C file
	f = codecs.open(filename_out + '.c', 'w')

	f.write('#include <genesis.h>\n\n')

	dumpCosine(_cosine_func = easing, display_name = 'easing_table', f = f)
	f.write('\n')

	f.close()

main()