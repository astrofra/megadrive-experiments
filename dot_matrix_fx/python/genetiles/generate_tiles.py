import os
import math
import gs
import codecs

pattern_folder_list = ['round']
filename_out = "../../src/res/"

tile_bits = 4
tile_steps = (1 << tile_bits)

w = 8
h = (8 * tile_steps)

def main():

	gs.MountFileDriver(gs.StdFileDriver())

	for pic_path in pattern_folder_list:
		new_tile_pic = gs.Picture(w, h, gs.Picture.RGBA8)

		for i in range(tile_steps):
			new_tile_pic.ClearRGBA(0,0,0,1)
			new_tile_pic.SetPenMode(gs.Picture.PenNone)
			new_tile_pic.SetFillMode(gs.Picture.BrushSolid)

			luma = float(i) / float(tile_steps)

			x = float(w) / 2.0
			y = (i * w) + (float(w) / 2.0)
			radius = (w / 2.0) * math.pow(luma, 0.5)

			new_tile_pic.SetFillColorRGBA(luma, luma, luma, 1.0)
			new_tile_pic.AddCircle(x, y, radius)
			# print("luma = " + str(luma) + ", radius = " + str(radius))

		new_tile_pic.DrawPath()

		final_pic_path = os.path.join(filename_out, 'pat_' + pic_path + '.png')
		saved_result = gs.SavePicture(new_tile_pic, final_pic_path, 'STB', 'format:png')
		new_tile_pic.Free()	

main()