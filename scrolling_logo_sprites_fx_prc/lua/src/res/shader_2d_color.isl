in { vec4 u_color; }

variant {
	vertex {
		out { vec4 v_color; }

		source %{
			v_color = u_color;
			%out.position% = vec4(vPosition, 1.0);
		%}
	}

	pixel {
		in { vec4 v_color; }

		source %{
			%out.color% = v_color;
		%}
	}
}
