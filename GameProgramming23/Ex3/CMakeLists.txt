file(GLOB_RECURSE Sources "*.h" "*.cpp") # will get all the .cpp and all the .h files in directory and subdirectories
add_executable(Ex3 ${Sources}
		Exercise3/Headers/Asteroids.h
        Exercise3/Classes/GameManager.cpp
		Exercise3/Headers/GameManager.h)

target_link_libraries(Ex3 ${all_libs})

# Copy project data to output path
file(COPY Exercise3/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY Exercise3/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY Exercise3/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)