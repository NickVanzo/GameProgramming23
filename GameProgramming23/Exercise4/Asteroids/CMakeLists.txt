# Game Only

file(GLOB_RECURSE Asteroids-src "*.h" "*.cpp")

add_executable(Asteroids ${Asteroids-src}
        Game/Laser/BulletComponentRender.cpp
        Game/Laser/BulletComponentRender.h
        Game/Laser/BulletComponentUpdate.cpp
        Game/Laser/BulletComponentUpdate.h
        Game/AsteroidSpawner/AsteroidSpawner.cpp
        Game/AsteroidSpawner/AsteroidSpawner.h)

target_include_directories(Asteroids PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(Asteroids MyEngine ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
    ## Copy dll's to output path
    file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)