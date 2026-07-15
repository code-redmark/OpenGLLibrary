cmake_minimum_required (VERSION 3.10)
project ("OpenGLLibrary")

file(GLOB_RECURSE C_SRC "EASUI/*.c")

add_executable("OpenGLLibrary"
		${C_SRC}
)
