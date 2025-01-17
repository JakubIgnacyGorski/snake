cmake_minimum_required(VERSION 3.26)
include(FetchContent)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

# Windows specific config
# To możecie zmienić jeśli zainstalujecie SFML-a w innym miejscu
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/lib/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Snake main.cpp
        snakeBody.cpp
        snakeBody.h)
add_executable(Snake-SFML main-sfml.cpp
        snakeBody.cpp
        snakeBody.h
        snakeViewer.cpp
        snakeViewer.h
        snakeController.cpp
        snakeController.h
        snakeMenu.cpp
        snakeMenu.h
        snakeScoreboard.cpp
        snakeScoreboard.h
        FontManager.cpp
        FontManager.h
        snakeScoreboardViewer.cpp
        snakeScoreboardViewer.h
        TextureManager.cpp
        TextureManager.h
        ColorsConsts.h
)

if (TARGET Snake-SFML) # Źródło: https://cmake.org/cmake/help/latest/command/if.html
    file (COPY fonts DESTINATION . FILES_MATCHING PATTERN "*.ttf")
    file (COPY textures DESTINATION . FILES_MATCHING PATTERN "*.png")
endif ()

target_link_libraries(Snake-SFML sfml-graphics)