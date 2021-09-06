cmake_minimum_required(VERSION 3.20)
project(BulletShooter)

set(CMAKE_CXX_STANDARD 17)

#set(SDL2_INCLUDE_DIR SDL2-2.0.16/include)
#set(SDL2_LIB_DIR SDL2-2.0.16/lib/x64)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/GameManagers/BulletManager.cpp src/GameManagers/BulletManager.h src/Vector2D.cpp src/Vector2D.h src/Renderer.cpp src/Renderer.h src/GameManagers/WallManager.cpp src/GameManagers/WallManager.h src/GameObjects/Figure.cpp src/GameObjects/Figure.h src/GameObjects/Bullet.cpp src/GameObjects/Bullet.h src/GameObjects/Wall.cpp src/GameObjects/Wall.h src/EventHandler.cpp src/EventHandler.h src/Randomizer.cpp src/Randomizer.h src/Grid.cpp src/Grid.h src/CollisionManager.cpp src/CollisionManager.h src/Sector.cpp src/Sector.h)

target_link_libraries(BulletShooter ${SDL2_LIBRARIES})
