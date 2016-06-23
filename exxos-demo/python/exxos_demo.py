# ---------------------------------------------------------------------
#                            EXXOS DEMO    
# ---------------------------------------------------------------------

import gs
import gs.plus.render as render
import gs.plus.clock as clock
import math
import random
import json
import easygui
from utils import *
from graphic_routines import *
from screen_specs import *


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
	future_channel = al.Stream("@assets/xo2s.mod")
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


def render_lanscape_screen():
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


# resolution_requester()
engine_init()

play_music()
render_space_screen()
render_lanscape_screen()
