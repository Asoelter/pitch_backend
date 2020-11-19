# CMakeList.txt : CMake project for pitch_backend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_backend WIN32 "WinMain.cpp")

# TODO: Add tests and install targets if needed.

target_link_libraries(${PROJECT_NAME} Ws2_32.lib)


function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

addDirectory(networking)
add_subdirectory(dependencies)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
