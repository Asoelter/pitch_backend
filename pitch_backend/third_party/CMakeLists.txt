cmake_minimum_required(VERSION 3.8)

find_path(COVID_INCLUDE_DIR ...)
find_library(COVID_LIBRARY ...)

if(COVID_INCLUDE_DIR AND COVID_LIBRARY)
	message("COVID INCLUDE DIR BELOW")
	message(COVID_INCLUDE_DIR)
	add_library(covid INTERFACE)
	target_include_directories(covid INTERFACE ${COVID_INCLUDE_DIR})
	target_link_libraries(covid INTERFACE ${COVID_LIBRARY})
	add_subdirectory(covid)
else()
	message("COVID NOT FOUND")
endif()

message("END OF FILE")