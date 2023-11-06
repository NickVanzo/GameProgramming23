# Engine Only

file(GLOB_RECURSE MyEngine-src "*.cpp")
file(GLOB_RECURSE MyEngine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(MyEngine ${MyEngine-src} ${MyEngine-hpp}
        ../../GJK-Test/main.cpp
        ../../GJK-Test/main.h
        ../../GJK-Test/GJK/Headers/Collider.h
        ../../GJK-Test/GJK/Headers/Collider.h)
target_link_libraries(MyEngine ${all_libs})
target_include_directories(MyEngine PUBLIC "Engine")
target_include_directories(MyEngine PUBLIC "3rdParty")