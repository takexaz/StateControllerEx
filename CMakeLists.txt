cmake_minimum_required (VERSION 3.15)

project (StateControllerExtension VERSION 0.1.0 LANGUAGES CXX)

file (GLOB src src/*.cpp src/*.c)
file (GLOB include include/*.hpp include/*.h)

add_library (
	${PROJECT_NAME} SHARED
	${src}
	${include}
)
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Mebius REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Mebius::Mebius)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".mx")

target_compile_features (${PROJECT_NAME} PRIVATE cxx_std_20)

target_compile_definitions (
	${PROJECT_NAME}
	PRIVATE
	STCEX_EXPORT
	PLOG_IMPORT
	UNICODE
	_UNICODE
	$<$<CONFIG:Debug>: 
		_DEBUG
		DEBUG
	>
	$<$<CONFIG:Release>:
		NDEBUG
	>
)

target_compile_options (
	${PROJECT_NAME}
	PRIVATE
	/W4
	/arch:AVX
	/fp:fast
	/GS
	/GT
	/MP
	/nologo
	/Oi
	/Qpar
	/utf-8
	$<$<CONFIG:Debug>:
		/JMC
		/LDd
		/Ob0
		/Od
		/RTC1
	>
	$<$<CONFIG:Release>:
		/GA
		/GL
		/Gy
		/guard:cf-
		/LD
		/Os
	>
)
target_link_options (
	${PROJECT_NAME}
	PRIVATE
	/LTCG
	/nologo
	$<$<CONFIG:Debug>:
		/debug
		/opt:noref
	>
	$<$<CONFIG:Release>:
		/opt:ref
	>
)

target_include_directories (
	${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories (
	${PROJECT_NAME}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/share>
	$<INSTALL_INTERFACE:include>
)

install (
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}-config
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include
)

install (
	EXPORT ${PROJECT_NAME}-config
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION cmake
)

install (
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/
	DESTINATION include
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file (
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	COMPATIBILITY SameMajorVersion
)

install (
	FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	DESTINATION cmake
)

# デバッグフォルダにコンパイルの産物をコピー
set(DEBUG_DIR "${CMAKE_SOURCE_DIR}/../!MUGEN_DEBUG/mods/StateControllerExtension/")
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEBUG_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" ${DEBUG_DIR}
)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" ${DEBUG_DIR}
)
ELSE(CMAKE_BUILD_TYPE MATCHES Release)
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove -f "${DEBUG_DIR}/${PROJECT_NAME}.pdb"
)
ENDIF()