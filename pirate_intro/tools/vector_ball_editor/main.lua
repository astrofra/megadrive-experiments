SCR_W = 800
SCR_H = 800

camera_node = nil
camera_rotation = gs.Vector3()
balls = {}
mesh_root = nil

-- GUI

gui = gs.GetDearImGui()
check = true
ball_combo = 0
color = gs.Color(1, 0, 1)

function updateGui()
	if gui:Begin("GUI") then
		-- check = gui:Checkbox("Check", check)

		-- if gui:CollapsingHeader("Header", true) then
		-- 	if gui:Button("Button") then
		-- 		print("Button pressed")
		-- 	end

			ball_combo = gui:Combo("Ball selector", getVectorBallNameList(), ball_combo)
			-- color = gui:ColorButton(color)
		-- end
	end

	gui:End()
end

-- View

function drawGrid()
end

function updateCamera()
	camera_node:GetTransform():SetRotation(camera_rotation)
end

function updateVectorBallMesh()
	print(tostring(#balls) .. " vector balls found!")
	names = getVectorBallNameList()
	for n = 1, #balls do
		new_node = plus:AddSphere(scn, gs.Matrix4.Identity, balls[n].size)
		new_node:GetTransform():SetPosition(balls[n].pos)
		new_node:GetTransform():SetParent(mesh_root)
		new_node:SetName(names[n])
	end
end

-- Vectorball operations

function getVectorBallNameList()
	names = {}
	for n = 1, #balls do
		table.insert(names, "Ball " .. tostring(n))
	end

	return names
end

function addVectorBall(_pos, _size)
	_pos = _pos or gs.Vector3()
	_size = _size or 0.5 
	table.insert(balls, {pos = _pos, color_id = 0, size = _size})
end

function createBasicObject()
	for n = 0, 2 do
		addVectorBall(gs.Vector3(0, 0, n))
	end
end

function truncateNumber(n)
	return math.floor(n * 10) / 10
end

function main()
	plus = gs.GetPlus()
	plus:RenderInit(SCR_W, SCR_H)

	scn = plus:NewScene()

	env = plus:AddEnvironment(scn, gs.Color.White * 0.25, gs.Color.Blue * 0.15) 

	cam = plus:AddCamera(scn, gs.Matrix4.TranslationMatrix({0, 0, -10}))
	light_0 = plus:AddLight(scn, gs.Matrix4.TranslationMatrix({6, 4, -6}))
	-- plus:AddCube(scn, gs.Matrix4.TranslationMatrix({0, 0.5, 0}))
	camera_node = plus:AddDummy(scn)
	camera_node:SetName("camera_node")
	cam:GetTransform():SetParent(camera_node)
	light_0:GetTransform():SetParent(camera_node)

	mesh_root = plus:AddDummy(scn)
	mesh_root:SetName("mesh_root")

	createBasicObject()
	updateVectorBallMesh()

	while not plus:IsAppEnded() do
		dt = plus:UpdateClock()

		plus:UpdateScene(scn, dt)
		str_debug = "Editor"
		str_debug = str_debug .. " " .. "[Camera : (" .. tostring(truncateNumber(camera_rotation.x)) .. "," .. tostring(truncateNumber(camera_rotation.y)) .. "," .. tostring(truncateNumber(camera_rotation.z)) .. ")]"
		plus:Text2D(5, 5, str_debug)

		camera_rotation = camera_rotation + gs.Vector3(1 / dt:to_ms() * 0.125, 1 / dt:to_ms() * 0.25, 0)

		updateGui()
		updateCamera()
		plus:Flip()
	end
end

main()
