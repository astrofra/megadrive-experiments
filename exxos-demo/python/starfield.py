## Starfield 3D

import gs
import random

max_stars = 0
stars = []
starfield_size = gs.Vector3(50, 50, 500)
camera_velocity = gs.Vector3()
pos_dt = gs.Vector3()


def init_stars(_max_stars = 500):
	global stars, max_stars, starfield_size
	max_stars = _max_stars

	def rand_point_within_size():
		global starfield_size
		return gs.Vector3(random.uniform(-starfield_size.x, starfield_size.x),
		                  random.uniform(-starfield_size.y, starfield_size.y),
		                  random.uniform(-starfield_size.z, starfield_size.z))

	for i in range(max_stars):
		stars.append({'pos':rand_point_within_size(), 'intensity':1.0})


def set_camera_velocity(vec):
	global camera_velocity, pos_dt
	camera_velocity = vec
	framerate = 60.0
	while framerate > 0 and pos_dt.Len() < 5.0 :
		pos_dt = camera_velocity * (1.0 / framerate)
		framerate -= 1.0

def update_stars(dt):
	global camera_velocity, starfield_size, stars, max_stars

	for i in range(max_stars):
		pos = stars[i]['pos']
		pos += camera_velocity * dt

		if pos.x > starfield_size.x:
			pos.x -= starfield_size.x
		else:
			if pos.x < -starfield_size.x:
				pos.x += starfield_size.x

		if pos.y > starfield_size.y:
			pos.y -= starfield_size.y
		else:
			if pos.y < -starfield_size.y:
				pos.y += starfield_size.y

		if pos.z > starfield_size.z :
			pos.z -= starfield_size.z 
		else:
			if pos.z < 0.0 :
				pos.z += starfield_size.z 

		stars[i]['pos'] = pos #/!\ try to comment this line


def draw_stars(rctx):
	global pos_dt, starfield_size, stars, max_stars

	for i in range(max_stars):
		pos_a = stars[i]['pos'] - pos_dt
		pos_b = stars[i]['pos']

		rctx.line3d(pos_a.x, pos_a.y, pos_a.z, pos_b.x, pos_b.y, pos_b.z, start_color=gs.Color.Black, end_color=gs.Color.White)