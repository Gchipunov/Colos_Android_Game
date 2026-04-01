# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("coloduobagabundos")

# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(coloduobagabundos SHARED
        android_main.cpp
        AndroidOut.cpp
        colo_engine.cpp
		input_util.cpp
		scene.cpp
		scene_manager.cpp
		welcome_scene.cpp
		indexbuf.cpp
		util.cpp
		vertexbuf.cpp
		ui_scene.cpp
		
		colo_context/quad_shader.cpp
		colo_context/quad_renderer.cpp
		colo_context/asset_shader_loader.cpp
		
		colo_engine3/perpective_camera/perpective_camera.cpp
		
		)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(coloduobagabundos
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)