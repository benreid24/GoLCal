include(compile_shaders)
compile_shaders(
    TARGET GoLCal
    SHADER_MODULE golcal_shaders
    
    SHADERS
	vertex.vert
    fragment.frag
)
