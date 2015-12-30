import gs
import gs.plus
import gs.plus.render as render
import gs.plus.camera as camera
import gs.plus.input as input
import gs.plus.scene as scene
import gs.plus.clock as clock
from math import pi, cos, sin, asin


def add_kapla_tower(scn, width, height, length, radius, level_count: int, x=0, y=0, z=0):
	"""Create a Kapla tower, return a list of created nodes"""
	level_y = y + height / 2

	for i in range(level_count // 2):
		def fill_ring(r, ring_y, size, r_adjust, y_off):
			step = asin((size * 1.01) / 2 / (r - r_adjust)) * 2
			cube_count = (2 * pi) // step
			error = 2 * pi - step * cube_count
			step += error / cube_count  # distribute error

			a = 0
			while a < (2 * pi - error):
				world = gs.Matrix4.TransformationMatrix(gs.Vector3(cos(a) * r + x, ring_y, sin(a) * r + z), gs.Vector3(0, -a + y_off, 0))
				scene.add_physic_cube(scn, world, width, height, length, 2)
				a += step

		fill_ring(radius - length / 2, level_y, width, length / 2, pi / 2)
		level_y += height
		fill_ring(radius - length + width / 2, level_y, length, width / 2, 0)
		fill_ring(radius - width / 2, level_y, length, width / 2, 0)
		level_y += height


gs.plus.create_workers()

render.init(1280, 720, "../pkg.core")

scn = scene.new_scene()
cam = scene.add_camera(scn, gs.Matrix4.TranslationMatrix(gs.Vector3(0, 3.5, -12.5)))
cam.transform.SetRotation(gs.Vector3(pi * 5.0 / 180.0, pi * -5.0 / 180.0,0))

scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.65, -0.45, 0)), gs.Light.Model_Linear, 150)
scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.55, pi, 0.2)), gs.Light.Model_Linear, diffuse=gs.Color(0.3, 0.3, 0.4))
scene.add_physic_plane(scn)

# nodes = add_kapla_tower(scn, 0.5, 2, 2, 6, 16)

width, height, length = 1, 1, 1

def make_solid_pos(x,y):
	return gs.Vector3(x * 1.15, y + height * 0.5, cos(x * y + x) * 0.25)

for y in range(3):
	for x in range(-2, 2):
		world = gs.Matrix4.TransformationMatrix(make_solid_pos(x,y), gs.Vector3(0, pi * 0.25 * cos(x * y + x + y + 0.1) * 0.25, 0))
		new_cube = scene.add_physic_cube(scn, world, width, height, length, 2)

# fps = camera.fps_controller(0, 3.5, -12.5)

thrown_bullet = False
fixed_step = True

dt_sum = 0.0

while not input.key_press(gs.InputDevice.KeyEscape):
	if fixed_step:
		dt_sec = 1.0 / 120.0 
	else:
		dt_sec = clock.update()

	dt_sum += dt_sec

	if not thrown_bullet and dt_sum > 1.0:
		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-0.25,40), gs.Vector3())
		ball, rigid_body = scene.add_physic_cube(scn, world, width, height, length, 2)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)

		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-0.65,55), gs.Vector3())
		ball, rigid_body = scene.add_physic_cube(scn, world, width, height, length, 2)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)

		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-1.25,58), gs.Vector3())
		ball, rigid_body = scene.add_physic_cube(scn, world, width, height, length, 2)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)		

		thrown_bullet = True

	# fps.update_and_apply_to_node(cam, dt_sec)

	scene.update_scene(scn, dt_sec)

	render.text2d(5, 25, "@%.2fFPS" % (1 / dt_sec))
	render.text2d(5, 5, "Move around with QSZD, left mouse button to look around")
	render.flip()
