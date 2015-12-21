print("START")

gs.LoadPlugins(sys.cwd)
gs.GetFilesystem():Mount(gs.StdFileDriver())

-- create an OpenAL mixer
al = gs.ALMixer()
print(al)
print(al:Open())
channel = al:Stream("res/skaven.it")

-- wait until the user decides to exit the program
print("Playing on channel " .. channel .. ",press Ctrl+C to stop.")

egl = gs.EglRenderer()
egl:Open(1280, 720)

rse_logo = gs.LoadPicture("res/rse_logo.png")
ball_metal = gs.LoadPicture("res/ball_metal.png")
ground = gs.LoadPicture("res/ground.png")
logostart = gs.LoadPicture("res/logostart.png")
amiga_font = gs.LoadPicture("res/amiga-font.png")

shader = egl:LoadShader("res/shader_2d_color.isl")

data = gs.BinaryBlob()
data:WriteShorts({0, 1, 2})

idx = egl:NewBuffer()
egl:CreateBuffer(idx, data, gs.GpuBuffer.Index)

vtx_layout = gs.VertexLayout()
vtx_layout:AddAttribute(gs.VertexAttribute.Position, 3, gs.ValueFloat)

data = gs.BinaryBlob()
x = 0.5
y = 0.5
data:WriteFloats({-x, -y, 0.5, -x, y, 0.5, x, y, 0.5})

vtx = egl:NewBuffer()
egl:CreateBuffer(vtx, data, gs.GpuBuffer.Vertex)

while 1 do
	egl:Clear(gs.Color.Red)

	egl:SetShader(shader)
	egl:SetShaderFloat4("u_color", 0, 1, 0, 1)

	gs.DrawBuffers(egl, 3, idx, vtx, vtx_layout)

	egl:DrawFrame()
	egl:ShowFrame()

	egl:UpdateOutputWindow()	
end