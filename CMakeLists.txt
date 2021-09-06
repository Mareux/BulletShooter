cmake_minimum_required(VERSION 3.20)
project(BulletShooter)

set(CMAKE_CXX_STANDARD 17)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.16/lib/x64")
    set(SDL2_TTF_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf-2.0.15/lib/x64")
else ()
    set(SDL2_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.16/lib/x86")
    set(SDL2_TTF_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf-2.0.15/lib/x86")
endif ()

set(SDL2_LIBRARY "${SDL2_LIBRARY_PATH}/SDL2.lib;${SDL2_LIBRARY_PATH}/SDL2main.lib")
set(SDL2_TTF_LIBRARY "${SDL2_TTF_LIBRARY_PATH}/SDL2_ttf.lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.16/include)
link_directories(${SDL2_LIBRARY})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf-2.0.15/include)
link_directories(${SDL2_TTF_LIBRARY})

add_executable(${PROJECT_NAME} src/main.cpp src/GameManagers/BulletManager.cpp src/GameManagers/BulletManager.h src/Vector2D.cpp src/Vector2D.h src/Renderer.cpp src/Renderer.h src/GameManagers/WallManager.cpp src/GameManagers/WallManager.h src/GameObjects/Bullet.cpp src/GameObjects/Bullet.h src/GameObjects/Wall.cpp src/GameObjects/Wall.h src/EventHandler.cpp src/EventHandler.h src/Randomizer.cpp src/Randomizer.h src/Grid.cpp src/Grid.h src/CollisionManager.cpp src/CollisionManager.h src/thread_pool.h src/TheGame.cpp src/TheGame.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIBRARY_PATH}/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_TTF_LIBRARY_PATH}/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_TTF_LIBRARY_PATH}/libfreetype-6.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_TTF_LIBRARY_PATH}/zlib1.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})