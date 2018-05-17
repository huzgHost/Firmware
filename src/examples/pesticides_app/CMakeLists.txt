px4_add_module(
	MODULE examples__pesticides_app
	MAIN pesticides_app
	STACK_MAIN 2000
	SRCS
		pesticides_app.c
	DEPENDS
		platforms__common
	)

# 测试主题是否发送
