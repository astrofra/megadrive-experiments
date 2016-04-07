import gs
import gs.plus
import gs.plus.render as render
import gs.plus.camera as camera
import gs.plus.input as input
import gs.plus.scene as scene
import gs.plus.clock as clock
from math import pi, cos, sin, asin, radians
import codecs

filename_out			=	"../src/simulation"
scale_factor			=	5.0

md_screen_w             =   320/10.0
md_screen_h             =   220/10.0

gs.plus.create_workers()
gs.LoadPlugins(gs.get_default_plugins_path())

render.init(1024, int(1024 * md_screen_h / md_screen_w), "../pkg.core")

scn = scene.new_scene()
scn.GetPhysicSystem().SetDefaultRigidBodyAxisLock(gs.LockZ)
scn.GetPhysicSystem().SetDebugVisuals(True)

cam = scene.add_camera(scn, gs.Matrix4.TranslationMatrix(gs.Vector3(0, 0.0, -10.0)))

# screen = scene.add_plane(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,0,0), gs.Vector3(radians(-90),0,0)), width=md_screen_w, depth=md_screen_h)

scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.65, -0.45, 0)), gs.Light.Model_Linear, 150)
scene.add_light(scn, gs.Matrix4.RotationMatrix(gs.Vector3(0.55, pi, 0.2)), gs.Light.Model_Linear, diffuse=gs.Color(0.3, 0.3, 0.4))
scene.add_physic_plane(scn, mat=gs.Matrix4.TransformationMatrix(gs.Vector3(0,-md_screen_h / 30,0), gs.Vector3(0,0,0)))

# nodes = add_kapla_tower(scn, 0.5, 2, 2, 6, 16)

width = 0.5

node_list = []
rb_list = []
stream_list = []


def make_solid_pos(x,y):
	return gs.Vector3(x * 1.15, y + width * 0.5, cos(x * y + x) * 0.15)

cube_masks = [	[0,0,1,0],
				[0,1,1,0],
				[1,1,1,1]]

for y in range(3):
	for x in range(-2, 2):
		if cube_masks[y][x + 2] == 1:
			world = gs.Matrix4.TransformationMatrix(make_solid_pos(x,y), gs.Vector3(0, pi * 0.25 * cos(x * y + x + y + 0.1) * 0.25, 0))
			new_cube, rigid_body = scene.add_physic_sphere(scn, world, width)
			node_list.append(new_cube)
			rb_list.append(rigid_body)

thrown_bullet = False
fixed_step = True
record_motion = False
record_done = False

dt_sum = 0.0

# Start simulation & record

while not input.key_press(gs.InputDevice.KeyEscape) and not record_done:
	if fixed_step:
		dt_sec = 1.0 / 120.0
	else:
		dt_sec = clock.update()

	dt_sum += dt_sec
	print(dt_sum)

	if not thrown_bullet and dt_sum > 1.0:
		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-0.25,40), gs.Vector3())
		new_cube, rigid_body = scene.add_physic_sphere(scn, world, width)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)
		node_list.append(new_cube)
		rb_list.append(rigid_body)

		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-0.65,55), gs.Vector3())
		new_cube, rigid_body = scene.add_physic_sphere(scn, world, width)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)
		node_list.append(new_cube)
		rb_list.append(rigid_body)

		world = gs.Matrix4.TransformationMatrix(make_solid_pos(-1.25,58), gs.Vector3())
		new_cube, rigid_body = scene.add_physic_sphere(scn, world, width)
		rigid_body.ApplyLinearImpulse(world.GetY() * -5)
		node_list.append(new_cube)
		rb_list.append(rigid_body)

		thrown_bullet = True

	# fps.update_and_apply_to_node(cam, dt_sec)

	scene.update_scene(scn, dt_sec)

	if not record_motion and dt_sum > 2.0:
		record_motion = True
	else:
		if record_motion and dt_sum > 8.0:
			record_motion = False
			record_done = True

	if record_motion:
		new_frame = []
		for current_node in node_list:
			new_motion = {'position': current_node.GetTransform().GetPosition() * scale_factor, 'rotation': current_node.GetTransform().GetRotation()}
			new_frame.append(new_motion)

		stream_list.append(new_frame)

	render.text2d(5, 25, "@%.2fFPS" % (1 / dt_sec))
	render.flip()

# Dump record

f = codecs.open(filename_out + '.h', 'w')

f.write('#include "genesis.h"\n\n')
f.write('#define SIMULATION_FRAME_LEN ' + str(len(stream_list)) + '\n')
f.write('#define SIMULATION_NODE_LEN ' + str(len(node_list)) + '\n\n')

f.write('const fix16 ' + 'physics_sim' + '[] =' + '\n')
f.write('{\n')

out_str = ''
frame_idx = 0

for frame_record in stream_list:
	if frame_idx%10 == 0:
		out_str = '\t/* Frame #' + str(frame_idx) + ' */\n\t'
	else:
		out_str = '\t'

	for node_record in frame_record:
		out_str += "FIX16({0:.4f}".format(node_record['position'].x) + '), ' + "FIX16({0:.4f}".format(node_record['position'].y) + '), ' + "FIX16({0:.4f}".format(node_record['position'].z) + '), '

	out_str += '\n'
	f.write(out_str)

	frame_idx += 1

f.write('};\n\n')

f.close()