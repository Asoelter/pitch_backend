# CMakeList.txt : CMake project for pitch_backend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_backend WIN32 "WinMain.cpp" "game/card.h" "game/card.cpp")

target_link_libraries(${PROJECT_NAME} Ws2_32.lib)


function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

add_subdirectory(third_party/covid)
include_directories(third_party/covid)
target_link_libraries(${PROJECT_NAME} covid)
target_include_directories(${PROJECT_NAME} PUBLIC thir_party/covid)

add_subdirectory(pitch_common)
include_directories(pitch_common)
target_link_libraries(${PROJECT_NAME} pitch_common)
target_include_directories(${PROJECT_NAME} PUBLIC pitch_common)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
