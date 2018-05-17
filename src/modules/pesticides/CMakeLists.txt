px4_add_module(
	MODULE modules__pesticides
	MAIN pesticides
	STACK_MAIN 5000
	COMPILE_FLAGS
	SRCS
		pesticides.c
    DEPENDS
		platforms__common
	)
