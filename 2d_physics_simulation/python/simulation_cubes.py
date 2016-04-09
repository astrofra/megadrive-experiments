import gs
import gs.plus
import gs.plus.render as render
import gs.plus.camera as camera
import gs.plus.input as input
import gs.plus.scene as scene
import gs.plus.clock as clock
from math import pi, cos, sin, asin, radians, degrees
import codecs
from random import uniform

filename_out = "../../outline_intro/simulation"
scale_factor = 10.0
md_screen_w = 320/scale_factor
md_screen_h = 200/scale_factor
sphere_radius = (md_screen_w / 40.0) # / 2.0
max_bullet = 40
framerate = 50

gs.plus.create_workers()
gs.LoadPlugins(gs.get_default_plugins_path())

render.init(1024, int(1024 * md_screen_h / md_screen_w), "../pkg.core")

scn = scene.new_scene()
scn.GetPhysicSystem().SetDefaultRigidBodyAxisLock(gs.LockZ + gs.LockRotX + gs.LockRotY)
scn.GetPhysicSystem().SetDebugVisuals(True)

cam = scene.add_camera(scn, gs.Matrix4.TranslationMatrix(gs.Vector3(0, 0.0, -md_screen_w * 1.15)))

screen = scene.add_plane(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,0,0), gs.Vector3(radians(-90),0,0)), width=md_screen_w, depth=md_screen_h)

scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.65, -0.45, 0)), gs.Light.Model_Linear, 150)
scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.55, pi, 0.2)), gs.Light.Model_Linear, diffuse=gs.Color(0.3, 0.3, 0.4))
scene.add_physic_plane(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,-md_screen_h / 2,0), gs.Vector3(0,0,0)))

# walls
scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(md_screen_h * -0.2, -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
                      width=sphere_radius, height=sphere_radius * 10.0, depth=sphere_radius, mass=0.0)
scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(md_screen_h * 0.2, -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
                      width=sphere_radius, height=sphere_radius * 10.0, depth=sphere_radius, mass=0.0)


def make_solid_pos(x,y):
	return gs.Vector3(x, y, 0.0)


def throw_bullet():
	world = gs.Matrix4.TransformationMatrix(make_solid_pos(uniform(md_screen_w * -0.01, md_screen_w * 0.01), md_screen_h / 2), gs.Vector3())
	new_bullet, rigid_body = scene.add_physic_sphere(scn, world, sphere_radius)
	rigid_body.ApplyLinearImpulse(world.GetY() * (-50 / scale_factor))
	new_bullet.SetName("bullet")


def throw_bullets_at_interval(dt, interval=1.0):
	global throw_bullet_timeout, bullet_count
	throw_bullet_timeout += dt

	if bullet_count < max_bullet and throw_bullet_timeout > interval:
		throw_bullet_timeout = 0.0
		throw_bullet()
		bullet_count += 1


def angle_to_image_index(angle):
	angle = -degrees(angle)
	print(angle)
	angle = angle%45
	angle *= (4/45)
	angle = int(angle)
	return angle


null_bullet = {'position': gs.Vector3(0,-128,0) * (1.0/scale_factor), 'rotation': gs.Vector3(0,0,0)}
throw_bullet_timeout = 0.0
fixed_step = True
record_motion = False
record_done = False
bullet_count = 0
stream_list = []
node_list = []

dt_sum = 0.0

# Start simulation & record

while not input.key_press(gs.InputDevice.KeyEscape) and not record_done:
	if fixed_step:
		dt_sec = 1.0 / float(framerate)
	else:
		dt_sec = clock.update()

	dt_sum += dt_sec
	throw_bullets_at_interval(dt_sec, 0.25)

	scene.update_scene(scn, dt_sec)

	if not record_motion and dt_sum > 0.0:
		record_motion = True
	else:
		if record_motion and dt_sum > 25.0:
			record_motion = False
			record_done = True

	node_list = []
	for _node in scn.GetNodes():
		if _node.GetName() == "bullet":
			node_list.append(_node)

	if record_motion:
		new_frame = []
		for current_node in node_list:
			_pos = current_node.GetTransform().GetPosition()
			if md_screen_w * -0.5 < _pos.x < md_screen_w * 0.5:
				if md_screen_h * -0.5 < _pos.y < md_screen_h * 0.5:
					new_motion = {'position': _pos, 'rotation': current_node.GetTransform().GetRotation()}
					new_frame.append(new_motion)

		if len(new_frame) < max_bullet:
			for i in range(max_bullet - len(new_frame)):
				new_frame.append(null_bullet)

		stream_list.append(new_frame)

	render.text2d(5, 25, "@%.2fFPS" % (1 / dt_sec))
	render.flip()

# Dump record

if len(stream_list) > 0:
	f = codecs.open(filename_out + '.h', 'w')

	f.write('#include "genesis.h"\n\n')
	f.write('#define SIMULATION_FRAME_LEN ' + str(len(stream_list)) + '\n')
	f.write('#define SIMULATION_NODE_LEN ' + str(max_bullet) + '\n\n')

	f.write('const s16 ' + 'physics_sim' + '[] =' + '\n')
	f.write('{\n')

	out_str = ''
	frame_idx = 0

	for frame_record in stream_list:
		if frame_idx%10 == 0:
			out_str = '\t/* Frame #' + str(frame_idx) + ' */\n\t'
		else:
			out_str = '\t'

		for node_record in frame_record:
			tmp_str = str(int((node_record['position'].x + (md_screen_w * 0.5)) * scale_factor) + 0x80) + ', '
			tmp_str += str(int(((md_screen_h * 0.5) - node_record['position'].y) * scale_factor) + 0x80) + ', '
			tmp_str += str(angle_to_image_index(node_record['rotation'].z))
			tmp_str += ', '
			out_str += tmp_str

		out_str += '\n'
		f.write(out_str)

		frame_idx += 1

	f.write('};\n\n')

	f.close()