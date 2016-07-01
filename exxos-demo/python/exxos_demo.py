# ---------------------------------------------------------------------
#                            EXXOS DEMO    
# ---------------------------------------------------------------------

import gs
import gs.plus.render as render
import gs.plus.clock as clock
import gs.plus.scene as scene
import math
import random
import json
import easygui
from utils import *
from graphic_routines import *
from screen_specs import *
import starfield


def resolution_requester():
	res_list = ["320x200", "640x400", "800x600", "1280x720", "1600x900", "1920x1080", "1920x1200"]
	choice = easygui.choicebox(msg='Select your screen resolution', title='Screen Resolution', choices=(res_list))
	if choice is not None:
		demo_screen_size[0] = int(choice.split("x")[0])
		demo_screen_size[1] = int(choice.split("x")[1])


def engine_init():
	global al, channel
	try:
		gs.LoadPlugins(gs.get_default_plugins_path())
	except:
		pass
	render.init(demo_screen_size[0], demo_screen_size[1], "pkg.core")

	# mount the system file driver
	gs.MountFileDriver(gs.StdFileDriver("assets/"), "@assets/")

	al = None
	channel = None


def play_music():
	global al, channel
	# create an OpenAL mixer and wrap it with the MixerAsync interface
	al = gs.MixerAsync(gs.ALMixer())
	al.Open()
	future_channel = al.Stream("@assets/xo2s.xm")
	channel = future_channel.get()


def render_space_screen():
	seq_duration = 20.0
	fx_timer = 0.0
	while fx_timer < seq_duration:
		dt_sec = clock.update()
		fx_timer += dt_sec
		render.clear()
		render.set_blend_mode2d(render.BlendAlpha)

		x_star = RangeAdjust(fx_timer, 0.0, seq_duration, demo_screen_size[0], -53 * zoom_size())
		x_moon = RangeAdjust(fx_timer, seq_duration * 0.475, seq_duration, demo_screen_size[0], -60 * zoom_size())
		x_planet = RangeAdjust(fx_timer, seq_duration * 0.65, seq_duration, demo_screen_size[0], -95 * zoom_size())

		render.image2d(x_star, (demo_screen_size[1] - 53 * zoom_size()) * 0.5, zoom_size(), "@assets/space_star.png")

		render.image2d(x_moon, (demo_screen_size[1] - 60 * zoom_size()) * 0.5, zoom_size(), "@assets/space_moon.png")

		render.image2d(x_planet, 0, zoom_size(), "@assets/space_planet.png")

		render.set_blend_mode2d(render.BlendOpaque)
		render.flip()


def render_landscape_screen():
	seq_duration = 40.0
	fx_timer = 0.0
	y_offset = 50
	logo_freq = 6
	while fx_timer < seq_duration:
		dt_sec = clock.update()
		fx_timer += dt_sec
		render.clear()
		render.set_blend_mode2d(render.BlendAlpha)

		render.image2d((demo_screen_size[0] - 320 * zoom_size()) * 0.5, (demo_screen_size[1] - (34 + y_offset) * zoom_size()) * 0.5, zoom_size(), "@assets/landscape_mountains.png")
		render.image2d((demo_screen_size[0] - 100 * zoom_size()) * 0.5, (demo_screen_size[1] - (80 + y_offset) * zoom_size()) * 0.5, zoom_size(), "@assets/landscape_stones.png")

		x, y = math.cos(fx_timer / seq_duration * math.pi * 2 * logo_freq) * 16, math.sin(fx_timer / seq_duration * math.pi * 5 * logo_freq) * 16
		render.image2d((demo_screen_size[0] - (187 + x) * zoom_size()) * 0.5, (demo_screen_size[1] - (106 - 80 + y) * zoom_size()) * 0.5, zoom_size(), "@assets/logo_exxos.png")


		render.set_blend_mode2d(render.BlendOpaque)
		render.flip()


def render_mask_screen():
	mask_segment_list = wireframe_json_to_segment_list("@assets/exxos_mask.json")

	scn = scene.new_scene()

	while not scn.IsReady():
		scene.update_scene(scn, 0.0)

	# Add an environment to the scene
	env = gs.Environment()
	env.SetBackgroundColor(gs.Color.Black)
	scn.AddComponent(env)

	# Add a camera
	render_camera = gs.Node()
	render_camera.AddComponent(gs.Transform())
	render_camera.AddComponent(gs.Camera())
	scn.AddNode(render_camera)
	scn.SetCurrentCamera(render_camera)
	render_camera.GetTransform().SetPosition(gs.Vector3(0, 0, -50))

	# Create a (parent) node to rotate the mask
	master_node = gs.Node()
	master_node.AddComponent(gs.Transform())
	scn.AddNode(master_node)

	# Init the starfield
	starfield.init_stars()
	starfield.set_camera_velocity(gs.Vector3(0, 0, -50))

	segment_nodes_list = []
	for seg in mask_segment_list:
		node_a, node_b = gs.Node(), gs.Node()
		tr_a, tr_b = gs.Transform(), gs.Transform()
		tr_a.SetPosition(gs.Vector3(seg[0][0], seg[0][1], seg[0][2]))
		tr_b.SetPosition(gs.Vector3(seg[1][0], seg[1][1], seg[1][2]))
		tr_a.SetParent(master_node)
		tr_b.SetParent(master_node)
		node_a.AddComponent(tr_a)
		node_b.AddComponent(tr_b)
		scn.AddNode(node_a)
		scn.AddNode(node_b)
		segment_nodes_list.append([node_a, node_b])

	seq_duration = 20.0
	fx_timer = 0.0
	while fx_timer < seq_duration:

		render.clear()
		dt_sec = clock.update()

		master_node.GetTransform().SetRotation(master_node.GetTransform().GetRotation() + gs.Vector3(1, 1, 1) * dt_sec * 0.25)
		scene.update_scene(scn, dt_sec)

		# render.commit_3d()
		# render.set_depth_write3d(False)

		starfield.update_stars(dt_sec)
		starfield.draw_stars(render)

		for seg in segment_nodes_list:
			pos_a = seg[0].GetTransform().GetWorld().GetTranslation()
			pos_b = seg[1].GetTransform().GetWorld().GetTranslation()
			render.line3d(pos_a.x, pos_a.y, pos_a.z, pos_b.x, pos_b.y, pos_b.z, start_color=gs.Color.Blue, end_color=gs.Color.Blue)

		render.flip()

		fx_timer += dt_sec


# resolution_requester()
engine_init()

play_music()
render_mask_screen()
render_space_screen()
render_landscape_screen()
