function(add_test_module)
	cmake_parse_arguments(
		"ARG"
		""
		"NAME;PATH"
		"DEPENDS"
		${ARGN}
	)

	add_executable(
		${ARG_NAME}
		${ARG_PATH}
	)

	target_link_libraries(
		${ARG_NAME}
		${ARG_DEPENDS}
	)

	add_test(NAME ${ARG_NAME} COMMAND ${ARG_NAME})
endfunction(add_test_module)