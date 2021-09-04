cmake_minimum_required(VERSION 3.20)
project(BulletShooter)

set(CMAKE_CXX_STANDARD 17)

#set(SDL2_INCLUDE_DIR SDL2-2.0.16/include)
#set(SDL2_LIB_DIR SDL2-2.0.16/lib/x64)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(BulletShooter main.cpp GameManagers/BulletManager.cpp GameManagers/BulletManager.h Vector2D.cpp Vector2D.h Renderer.cpp Renderer.h GameManagers/WallManager.cpp GameManagers/WallManager.h GameObjects/Figure.cpp GameObjects/Figure.h GameObjects/Bullet.cpp GameObjects/Bullet.h GameObjects/Wall.cpp GameObjects/Wall.h EventHandler.cpp EventHandler.h Randomizer.cpp Randomizer.h Grid.cpp Grid.h CollisionManager.cpp CollisionManager.h)

target_link_libraries(BulletShooter ${SDL2_LIBRARIES})
