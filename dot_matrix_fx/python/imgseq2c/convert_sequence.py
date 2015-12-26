import os
import math
import gs
import codecs

fx_folder_list = ['tore_tunnel']
filename_out = "../../src/img_seq"

in_file_ext = '.png'
w = 40
h = 30
tile_steps = (1 << 4)

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

	for fx_path in fx_folder_list:
		image_count = 0
		total_str = ''
		for img in os.listdir(fx_path):
			if img.find(in_file_ext) > -1:
				image_count += 1
				pic_path = os.path.join(fx_path, img)
				print("Loading picture '" + pic_path + "'.")
				pic = gs.LoadPicture(pic_path)

				out_str = '\t'
				for y in range(h):
					for x in range(w):
						texel = pic.GetPixelRGBA(x,y)
						quant_texel = quantizeTexel(texel.x)
						if quant_texel < 10:
							out_str += ' ' + str(int(quant_texel)) + ','
						else:
							out_str += str(int(quant_texel)) + ','
					out_str += '\n\t'

				out_str += '\n'
				total_str += out_str

	f.write('/* ' + fx_path + ' */\n')
	f.write('#define ' + fx_path + '_IMG_COUNT ' + str(image_count) + '\n')
	f.write('#define ' + fx_path + '_IMG_LEN ' + str(int(w * h / tile_steps)) + '\n\n')
	f.write('const u16 ' + fx_path + '_seq[] = \n')
	f.write('{\n')	
	f.write(total_str)
	f.write('};\n')	

	# image_count = 0
	# frame_offset = 3
	# input_picture_width = 512


	# def loadFacePicture(eye_key, face_key, pic_index):
	# 	print('Picture eye (' + face_keys[eye_key] + '), face (' + face_keys[face_key] + ').')
	# 	pic_path = 'frame_' + face_keys[eye_key] + '_' + face_keys[face_key] + '_' + '{0:05}'.format(pic_index) + in_file_ext
	# 	pic_path = os.path.join(in_path, pic_path)
	# 	print('Loading file ' + pic_path)
	# 	pic = gs.LoadPicture(pic_path)
	# 	return pic

	# for file_entry in os.listdir(in_path):
	# 	# file_path = os.path.join(in_path, file_entry)
	# 	if file_entry.find(in_file_ext) > -1:
	# 		image_count += 1

	# print("Found {0:010} images".format(image_count))

	# # load all images, face by face
	# # and composite them into a single picture

	# new_cubemap_pic = gs.Picture(input_picture_width * 3, input_picture_width * 4, gs.Picture.RGBA8)
	# input_picture_rect = gs.iRect(0, 0, input_picture_width, input_picture_width)

	# # for eye in ['eye_right']:
	# for idx in range(image_count):
	# 	frame_idx = idx + frame_offset
	# 	new_cubemap_pic.ClearRGBA(1, 0, 1, 1)

	# 	eye = 'eye_right'
	# 	tmp_pic = loadFacePicture(eye, 'front', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'right', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width * 2, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'left', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(0, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'back', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(0, input_picture_width))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'bottom', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width, input_picture_width))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'top', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width * 2, input_picture_width))
	# 	tmp_pic.Free()

	# 	new_cubemap_pic.Blit(new_cubemap_pic, gs.iRect(0, 0, input_picture_width * 3, input_picture_width * 2), gs.iVector2(0, input_picture_width * 2))

	# 	eye = 'eye_left'
	# 	tmp_pic = loadFacePicture(eye, 'front', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'right', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width * 2, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'left', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(0, 0))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'back', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(0, input_picture_width))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'bottom', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width, input_picture_width))
	# 	tmp_pic.Free()
	# 	tmp_pic = loadFacePicture(eye, 'top', frame_idx)
	# 	new_cubemap_pic.Blit(tmp_pic, input_picture_rect, gs.iVector2(input_picture_width * 2, input_picture_width))
	# 	tmp_pic.Free()

	# 	eye = 'stereo'

	# 	# Final save
	# 	final_pic_path = 'frame_' + eye + '_' + '{0:05}'.format(idx) + '.png'
	# 	final_pic_path = os.path.join(out_path, final_pic_path)
	# 	saved_result = gs.SavePicture(new_cubemap_pic, final_pic_path, 'STB', 'format:png')

	# 	if not saved_result:
	# 		print('Save failed! : ' + final_pic_path)

main()