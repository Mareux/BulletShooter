cmake_minimum_required(VERSION 3.20)
project(BulletShooter)

set(CMAKE_CXX_STANDARD 17)


find_package( OpenCL REQUIRED )


add_executable(BulletShooter main.cpp BulletManager.cpp BulletManager.h Vector2D.cpp Vector2D.h Renderer.cpp Renderer.h)

target_link_libraries(BulletShooter OpenCL::OpenCL)
