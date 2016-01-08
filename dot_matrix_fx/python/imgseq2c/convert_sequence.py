import os
import math
import gs
import codecs

fx_folder_list = ['tore_tunnel', 'star_tunnel']
filename_out = "../../src/img_seq"

in_file_ext = '.png'
tile_bits = 4
tile_steps = (1 << tile_bits)
w = 40
h = 30

def quantizeTexel(texel):
	texel *= tile_steps
	texel /= 255.0
	texel = int(texel)
	return texel


def main():

	gs.MountFileDriver(gs.StdFileDriver())

	f = codecs.open(filename_out + '.c', 'w')
	f.write('#include <genesis.h>\n')
	f.write('#include <gfx.h>\n\n')

	fh = codecs.open(filename_out + '.h', 'w')
	fh.write('#include <genesis.h>\n')
	fh.write('#include <gfx.h>\n\n')
	fh.write('#define TILE_BITS ' + str(tile_bits) + '\n')
	fh.write('#define TILE_STEPS ' + str(tile_steps) + '\n\n')	

	for fx_path in fx_folder_list:
		fh.write('/* ' + fx_path + ' */\n')

		image_count = 0
		word_count = 0
		total_str = ''
		for img in os.listdir(fx_path):
			if img.find(in_file_ext) > -1:
				image_count += 1
				pic_path = os.path.join(fx_path, img)
				print("Loading picture '" + pic_path + "'.")
				pic = gs.LoadPicture(pic_path)

				out_str = '\t/* image #' + str(image_count - 1) + ' */\n'
				out_str += '\t'
				for y in range(h):
					tex_list = []
					for x in range(w):
						texel = pic.GetPixelRGBA(x,y)
						quant_texel = quantizeTexel(texel.x)
						tex_list.append(quant_texel)
						if len(tex_list) == 4:
							packed_texel = (tex_list[0] << (tile_bits * 3)) | (tex_list[1] << (tile_bits * 2)) | (tex_list[2] << tile_bits) | tex_list[3]
							word_count += 1
							tex_list = []
							out_str += str(int(packed_texel)) + ','
					out_str += '\n\t'

				out_str += '\n'
				total_str += out_str

		f.write('/* ' + fx_path + ' */\n')
		f.write('const u16 ' + fx_path + '_seq[] = \n')
		f.write('{\n')	
		f.write(total_str)
		f.write('};\n\n')	

		fh.write('#define ' + fx_path + '_IMG_COUNT ' + str(image_count) + '\n')
		fh.write('#define ' + fx_path + '_IMG_LEN ' + str(int(w * h * tile_bits / 16)) + '\n\n')
		# f.write('#define ' + fx_path + '_IMG_WORD_COUNT ' + str(int(w * h / tile_steps)) + '\n\n')

		fh.write('const u16 ' + fx_path + '_seq[' + str(word_count) + '];\n\n')
	
main()