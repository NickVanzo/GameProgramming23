# Engine Only
file(GLOB_RECURSE MyEngine-src "*.cpp")
file(GLOB_RECURSE MyEngine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(MyEngine ${MyEngine-src} ${MyEngine-hpp})

message(424243)
message(${EXTRA_LIBS})
target_link_libraries(MyEngine ${all_libs})
#target_link_libraries(MyEngine SRE ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${OPENVR_LIB})

target_include_directories(MyEngine PUBLIC ${MYENGINE_INCLUDE_DIR})
target_include_directories(MyEngine PUBLIC "3rdParty")

#target_include_directories(MyEngine PUBLIC ${MYENGINE_INCLUDE_DIR})
#target_link_libraries(MyEngine ${all_libs})


#target_include_directories(MyEngine PUBLIC "3rdParty")