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
from random import seed
from utils import *

current_scenario = 0  # <------- SET ME TO 0, 1, ...

filename_out = "../../outline_intro/simulation"
scale_factor = 10.0
md_screen_w = 320/scale_factor
md_screen_h = 224/scale_factor
sphere_radius = (md_screen_w / 40.0) # / 2.0
max_bullet = 40
framerate = 50
g_dict = {}
ground = None

sprite_specs = {'sphere': {'offset': 4, 'length': 4, 'angle': 45},
                'sphere_black': {'offset': 0, 'length': 4, 'angle': 45},
                'sphere_red': {'offset': 8, 'length': 4, 'angle': 45},
                'cube': {'offset': 12, 'length': 9, 'angle': 90},
                'elastic_cube': {'offset': 12, 'length': 9, 'angle': 90, 'restitution': 1.0},
                'elastic_sphere': {'offset': 8, 'length': 4, 'angle': 45, 'restitution': 1.0}}


def tile_quantizer(x):
	x /= sphere_radius
	x = int(x)
	x *= sphere_radius
	return x

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
ground = scene.add_physic_plane(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,-md_screen_h / 2,0), gs.Vector3(0,0,0)))


def enable_ground(flag):
	global ground, node_list
	ground[1].SetEnabled(flag)

	# if flag is False:
	# 	for _node in node_list:
	# 		if _node.GetComponent("RigidBody").GetIsSleeping():
	# 			print("Node is sleeping!")
	# 			_node.GetComponent("RigidBody").SetIsSleeping(False)
	# 			_node.GetComponent("RigidBody").ApplyLinearImpulse(gs.Vector3(0,-10,0))
	# 			_node.GetComponent("RigidBody").ApplyLinearForce(gs.Vector3(0,-10,0))


def node_is_bullet(node):
	if node.GetName().find('type;') > -1:
		return True
	return False


def node_get_type(node):
	n = node.GetName()
	n = n.split(';')
	for i in range(len(n)):
		if n[i] == 'type':
			return n[i + 1]
	return None


def node_get_size(node):
	n = node.GetName()
	n = n.split(';')
	for i in range(len(n)):
		if n[i] == 'size':
			return int(n[i + 1])
	return 1


def make_solid_pos(x,y):
	return gs.Vector3(x, y, 0.0)


def throw_bullet(size=1.0, mass=1.0, type='sphere', spread_angle=1.0, spread_pos=1.0):
	world = gs.Matrix4.TransformationMatrix(make_solid_pos(uniform(md_screen_w * -0.01 * size * spread_pos, md_screen_w * 0.01 * size * spread_pos), md_screen_h / 2 + (sphere_radius * size)), gs.Vector3())
	if type.find('sphere') > -1:
		new_bullet, rigid_body = scene.add_physic_sphere(scn, world, sphere_radius * size, mass=mass)
	elif type.find('cube') > -1:
		new_bullet, rigid_body = scene.add_physic_cube(scn, world, sphere_radius * size * 1.6, sphere_radius * size * 1.6, sphere_radius * size * 1.6, mass=mass)

	if type.find('elastic') > -1:
		rigid_body.SetRestitution(1.15)

	ejection_vector = world.GetY() + gs.Vector3(uniform(-1.0, 1.0), uniform(0.0, 1.0), 0.0) * spread_angle
	rigid_body.ApplyLinearImpulse(ejection_vector * (-50 / scale_factor))
	new_bullet.SetName('type;' + type + ';size;' + str(int(size)) + ';mass;' + str(int(mass)))


def throw_bullets_at_interval(dt, interval=1.0, mass=1.0, type='sphere', spread_angle=0.0, spread_pos=1.0):
	global throw_bullet_timeout, bullet_count
	if not (type in throw_bullet_timeout):
		throw_bullet_timeout[type] = interval * 0.5
	throw_bullet_timeout[type] += dt

	if bullet_count < max_bullet and throw_bullet_timeout[type] > interval:
		throw_bullet_timeout[type] = 0.0
		throw_bullet(mass=mass, type=type, spread_angle=spread_angle, spread_pos=spread_pos)
		bullet_count += 1


def angle_to_image_index(angle=0.0, type='sphere', size=1.0):
	angle = -degrees(angle)
	print(angle)
	angle %= sprite_specs[type]['angle']
	angle *= (sprite_specs[type]['length']/sprite_specs[type]['angle'])
	angle = int(angle)
	angle += sprite_specs[type]['offset']
	return angle


# Scenario 0 ###########################################################################################################

def setup_scenario_0():
	# walls
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * -0.2), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * 0.2), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * -0.4), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 8, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * 0.4), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 8, depth=sphere_radius, mass=0.0)


def execute_scenario_0(dt, dt_sum):
	if not ('state' in g_dict):
		g_dict['state'] = 0
		enable_ground(True)

	if g_dict['state'] == 0:
		if dt_sum < 12.0:
			interval = RangeAdjust(dt_sum, 0.0, 5.0, 3.0, 0.25)
			interval = Clamp(interval, 0.25, 3.0)
			throw_bullets_at_interval(dt, interval * 1.35, type='cube')
			throw_bullets_at_interval(dt, interval * 2.0, type='elastic_cube', spread_pos=5.0)
		else:
			g_dict['state'] = 1

	if g_dict['state'] == 1:
		if dt_sum < 14.0:
			throw_bullets_at_interval(dt, 0.5, type='elastic_cube', spread_pos=10.0)
		else:
			throw_bullet(1.0, 35.0, type='sphere_black')
			g_dict['state'] = 2

	if g_dict['state'] == 2:
		throw_bullets_at_interval(dt, 0.5, type='elastic_sphere', mass=0.25)
		if dt_sum > 17.0:
			throw_bullet(1.0, 30.0, type='sphere_black')
			g_dict['state'] = 3

	if g_dict['state'] == 3:
		throw_bullets_at_interval(dt, 0.5, type='elastic_sphere', mass=0.25)
		throw_bullets_at_interval(dt, 0.25, type='elastic_cube', mass=0.15, spread_pos=5.0)
		if dt_sum > 19.0:
			throw_bullet(1.0, 25.0, type='sphere_black')
			g_dict['state'] = 4

	if g_dict['state'] == 4:
		throw_bullets_at_interval(dt, 0.5, type='elastic_sphere', mass=0.25)
		throw_bullets_at_interval(dt, 0.25, type='elastic_cube', mass=0.15, spread_pos=5.0)
		if dt_sum > 23.0:
			enable_ground(False)
			g_dict['state'] = 5

	if g_dict['state'] == 5:
		if dt_sum < 25.0:
			throw_bullets_at_interval(dt, 0.25, type='elastic_cube', mass=0.15, spread_pos=5.0)

		if dt_sum > 26.0:
			return False

	return True


# Scenario 1 ###########################################################################################################

def setup_scenario_1():
	# walls
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.1), tile_quantizer(md_screen_h * 0.25), 0),gs.Vector3(0,0, pi * 0.25)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.1), tile_quantizer(md_screen_h * -0.15), 0),gs.Vector3(0,0, pi * -0.25)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.1), tile_quantizer(md_screen_h * -0.5), 0),gs.Vector3(0,0, pi * 0.25)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)


def execute_scenario_1(dt, dt_sum):
	if not ('state' in g_dict):
		g_dict['state'] = 0
		enable_ground(False)

	if g_dict['state'] == 0:
		if dt_sum < 12.0:
			interval = RangeAdjust(dt_sum, 0.0, 3.0, 3.0, 0.1)
			interval = Clamp(interval, 0.1, 3.0)
			if uniform(0.0, 1.0) < 0.1:
				throw_bullets_at_interval(dt, interval, mass=25.0, type='sphere_black')
			else:
				throw_bullets_at_interval(dt, interval)
		else:
			g_dict['state'] = 1

	if g_dict['state'] == 1:
		if dt_sum > 15.0:
			return False

	return True


# Scenario 2 ###########################################################################################################

def setup_scenario_2():
	# walls
	# scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * -0.2), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
	# 					  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)
	# scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * 0.2), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
	# 					  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * -0.4), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 8, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_h * 0.4), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 8, depth=sphere_radius, mass=0.0)

	scene.add_physic_sphere(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,-md_screen_h * 0.25,0),gs.Vector3(0,0,0)),
	 					  radius=sphere_radius * 4.0, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)


def execute_scenario_2(dt, dt_sum):
	if not ('state' in g_dict):
		g_dict['state'] = 0
		enable_ground(True)

	if g_dict['state'] == 0:
		if dt_sum < 20.0:
			interval = RangeAdjust(dt_sum, 0.0, 2.0, 3.0, 0.25)
			interval = Clamp(interval, 0.25, 3.0)
			throw_bullets_at_interval(dt, interval)
		else:
			g_dict['state'] = 1

	if g_dict['state'] == 1:
		if dt_sum > 12.0:
			throw_bullet(1.0, 35.0, type='sphere_black')
			g_dict['state'] = 2

	if g_dict['state'] == 2:
		if dt_sum > 16.0:
			throw_bullet(1.0, 30.0, type='sphere_black')
			g_dict['state'] = 3

	if g_dict['state'] == 3:
		if dt_sum > 18.0:
			throw_bullet(1.0, 25.0, type='sphere_black')
			g_dict['state'] = 4

	if g_dict['state'] == 4:
		if dt_sum > 20.0:
			enable_ground(False)
			g_dict['state'] = 5

	if g_dict['state'] == 5:
		if dt_sum > 25.0:
			return False

	return True


# Scenario 3 ###########################################################################################################

def setup_scenario_3():

	scene.add_physic_sphere(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,-md_screen_h * 0.25,0),gs.Vector3(0,0,0)),
	 					  radius=sphere_radius * 4.0, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.48), 0.0,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.48), 0.0,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.48), md_screen_h * 0.5,0),gs.Vector3(0,0,pi * 0.5)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.48), md_screen_h * 0.5,0),gs.Vector3(0,0,pi * 0.5)),
						  width=sphere_radius * 2.0, height=sphere_radius * 12.0, depth=sphere_radius, mass=0.0)

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.2), md_screen_h * 0.5,0),gs.Vector3(0,0,pi * 0.5)),
						  width=sphere_radius * 2.0, height=sphere_radius * 10.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.2), md_screen_h * 0.5,0),gs.Vector3(0,0,pi * 0.5)),
						  width=sphere_radius * 2.0, height=sphere_radius * 10.0, depth=sphere_radius, mass=0.0)

def execute_scenario_3(dt, dt_sum):
	if not ('state' in g_dict):
		g_dict['state'] = 0
		enable_ground(True)

	if g_dict['state'] == 0:
		if dt_sum < 22.0:
			interval = RangeAdjust(dt_sum, 0.0, 10.0, 3.0, 0.5)
			interval = Clamp(interval, 0.5, 3.0)
			throw_bullets_at_interval(dt, interval, type='elastic_cube', mass=0.25)
			throw_bullets_at_interval(dt, 2.35, type='sphere', mass=0.25)
		else:
			g_dict['state'] = 1

	if g_dict['state'] == 1:
		if dt_sum > 22.0:
			enable_ground(False)
			g_dict['state'] = 5

	if g_dict['state'] == 5:
		if dt_sum > 25.0:
			return False

	return True


# Scenario 4 ###########################################################################################################

def setup_scenario_4():

	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * -0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)
	scene.add_physic_cube(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(tile_quantizer(md_screen_w * 0.48), -md_screen_h * 0.5,0),gs.Vector3(0,0,0)),
						  width=sphere_radius * 2.0, height=sphere_radius * 16.0, depth=sphere_radius, mass=0.0)


def execute_scenario_4(dt, dt_sum):
	if not ('state' in g_dict):
		g_dict['state'] = 0
		enable_ground(True)

	if g_dict['state'] == 0:
		if dt_sum < 10.0:
			interval = RangeAdjust(dt_sum, 0.0, 5.0, 3.0, 0.25)
			interval = Clamp(interval, 0.25, 3.0)
			throw_bullets_at_interval(dt, interval, type='cube')
		else:
			g_dict['state'] = 1

	if g_dict['state'] == 1:
		if dt_sum > 20.0:
			enable_ground(False)
			g_dict['state'] = 5

	if g_dict['state'] == 5:
		if dt_sum > 25.0:
			return False

	return True


scenario_list = [[setup_scenario_0, execute_scenario_0],
				[setup_scenario_1, execute_scenario_1],
				[setup_scenario_2, execute_scenario_2],
				[setup_scenario_3, execute_scenario_3],
				[setup_scenario_4, execute_scenario_4]]

# Main ========================================================================

seed(0)

null_bullet = {'position': gs.Vector3(0,-128,0) * (1.0/scale_factor), 'rotation': gs.Vector3(0,0,0), 'type': 'sphere', 'size': 1.0}
throw_bullet_timeout = {}
fixed_step = True
record_motion = False
record_done = False
bullet_count = 0
stream_list = []
node_list = []

dt_sum = 0.0

# Start simulation & record
scenario_list[current_scenario][0]()

while not input.key_press(gs.InputDevice.KeyEscape) and not record_done:
	if fixed_step:
		dt_sec = 1.0 / float(framerate)
	else:
		dt_sec = clock.update()

	dt_sum += dt_sec

	if not record_motion and dt_sum > 0.0:
		record_motion = True

	if not scenario_list[current_scenario][1](dt_sec, dt_sum):
		record_motion = False
		record_done = True

	scene.update_scene(scn, dt_sec)


	node_list = []
	for _node in scn.GetNodes():
		if node_is_bullet(_node):
			node_list.append(_node)
			_node.GetComponent("RigidBody").SetIsSleeping(False)


	if record_motion:
		new_frame = []
		for current_node in node_list:
			_pos = current_node.GetTransform().GetPosition()
			if md_screen_w * -0.5 < _pos.x < md_screen_w * 0.5:
				if md_screen_h * -0.5 < _pos.y < md_screen_h * 0.5:
					new_motion = {'type': node_get_type(current_node), 'size': node_get_size(current_node),
									'position': _pos, 'rotation': current_node.GetTransform().GetRotation()}
					new_frame.append(new_motion)

		if len(new_frame) < max_bullet:
			for i in range(max_bullet - len(new_frame)):
				new_frame.append(null_bullet)

		stream_list.append(new_frame)

	render.text2d(5, 25, "@%.2f FPS" % (1 / dt_sec))
	render.text2d(5, 40, "@%.2f sec" % (dt_sum))
	render.flip()

# Dump record

if len(stream_list) > 0:
	f = codecs.open(filename_out + '_' + str(current_scenario) + '.h', 'w')

	f.write('#include "genesis.h"\n\n')
	f.write('#define SIMULATION_' + str(current_scenario) + '_FRAME_LEN ' + str(len(stream_list)) + '\n')
	f.write('#define SIMULATION_' + str(current_scenario) + '_NODE_LEN ' + str(max_bullet) + '\n\n')

	f.write('const s16 ' + 'physics_sim_' + str(current_scenario) + '[] =' + '\n')
	f.write('{\n')

	out_str = ''
	frame_idx = 0

	for frame_record in stream_list:
		if frame_idx%10 == 0:
			out_str = '\t/* Frame #' + str(frame_idx) + ' */\n\t'
		else:
			out_str = '\t'

		for node_record in frame_record:
			tmp_str = str(int((node_record['position'].x + (md_screen_w * 0.5)) * scale_factor) + 0x80 - 8) + ', '
			tmp_str += str(int(((md_screen_h * 0.5) - node_record['position'].y) * scale_factor) + 0x80 - 8) + ', '
			tmp_str += str(angle_to_image_index(node_record['rotation'].z, node_record['type'], node_record['size']))
			tmp_str += ', '
			out_str += tmp_str

		out_str += '\n'
		f.write(out_str)

		frame_idx += 1

	f.write('};\n\n')

	f.close()