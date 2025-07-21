
on windows. (Linux use make not mingw32-make) .
install mingw32 or MSYS32
install cmake

open command prompt(with mingw32) or MSYS32 or MSYS64

mingw32-make install

C:\Windows\system32>cd ..

C:\Windows>cd ..

C:\>cd glew-2.1.0

C:\glew-2.1.0>dir
 Volume in drive C has no label.
 Volume Serial Number is 9AB1-5949

 Directory of C:\glew-2.1.0

11/11/2024  06:48 PM    <DIR>          .
11/11/2024  06:48 PM    <DIR>          ..
11/11/2024  06:50 PM    <DIR>          glew-2.1.0
               0 File(s)              0 bytes
               3 Dir(s)  76,638,453,760 bytes free

C:\glew-2.1.0>cd glew-2.1.0

C:\glew-2.1.0\glew-2.1.0>cd build

C:\glew-2.1.0\glew-2.1.0\build>cd cmake

C:\glew-2.1.0\glew-2.1.0\build\cmake>cmake -G "MinGW Makefiles" -S . -B . -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32
CMake Warning (dev) at CMakeLists.txt:5 (project):
  cmake_minimum_required() should be called prior to this top-level project()
  call.  Please see the cmake-commands(7) manual for usage documentation of
  both commands.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- The C compiler identification is GNU 8.1.0
-- The CXX compiler identification is GNU 8.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/mingw64/bin/gcc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/mingw64/bin/c++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at CMakeLists.txt:7 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Configuring done (3.4s)
-- Generating done (0.3s)
-- Build files have been written to: C:/glew-2.1.0/glew-2.1.0/build/cmake

C:\glew-2.1.0\glew-2.1.0\build\cmake>mingw32-make all
[  8%] Building C object CMakeFiles/glew.dir/C_/glew-2.1.0/glew-2.1.0/src/glew.c.obj
[ 16%] Building RC object CMakeFiles/glew.dir/C_/glew-2.1.0/glew-2.1.0/build/glew.rc.obj
[ 25%] Linking C shared library bin\glew32.dll
[ 25%] Built target glew
[ 33%] Building C object CMakeFiles/glew_s.dir/C_/glew-2.1.0/glew-2.1.0/src/glew.c.obj
[ 41%] Building RC object CMakeFiles/glew_s.dir/C_/glew-2.1.0/glew-2.1.0/build/glew.rc.obj
[ 50%] Linking C static library lib\libglew32.a
[ 50%] Built target glew_s
[ 58%] Building C object CMakeFiles/glewinfo.dir/C_/glew-2.1.0/glew-2.1.0/src/glewinfo.c.obj
[ 66%] Building RC object CMakeFiles/glewinfo.dir/C_/glew-2.1.0/glew-2.1.0/build/glewinfo.rc.obj
[ 75%] Linking C executable bin\glewinfo.exe
[ 75%] Built target glewinfo
[ 83%] Building C object CMakeFiles/visualinfo.dir/C_/glew-2.1.0/glew-2.1.0/src/visualinfo.c.obj
[ 91%] Building RC object CMakeFiles/visualinfo.dir/C_/glew-2.1.0/glew-2.1.0/build/visualinfo.rc.obj
[100%] Linking C executable bin\visualinfo.exe
[100%] Built target visualinfo

C:\glew-2.1.0\glew-2.1.0\build\cmake>mingw32-make install
[ 25%] Built target glew
[ 50%] Built target glew_s
[ 75%] Built target glewinfo
[100%] Built target visualinfo
Install the project...
-- Install configuration: "Release"
-- Installing: C:/mingw64/x86_64-w64-mingw32/lib/libglew32.dll.a
-- Installing: C:/mingw64/x86_64-w64-mingw32/bin/glew32.dll
-- Installing: C:/mingw64/x86_64-w64-mingw32/lib/libglew32.a
-- Installing: C:/mingw64/x86_64-w64-mingw32/bin/glewinfo.exe
-- Installing: C:/mingw64/x86_64-w64-mingw32/bin/visualinfo.exe
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/lib/pkgconfig/glew.pc
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/include/GL/wglew.h
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/include/GL/glew.h
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/include/GL/glxew.h
-- Old export file "C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/glew-targets.cmake" will be replaced.  Removing files [C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/glew-targets-release.cmake].
-- Installing: C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/glew-targets.cmake
-- Installing: C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/glew-targets-release.cmake
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/glew-config.cmake
-- Up-to-date: C:/mingw64/x86_64-w64-mingw32/lib/cmake/glew/CopyImportedTargetProperties.cmake

C:\glew-2.1.0\glew-2.1.0\build\cmake>



g++ triangle.cpp -o triangle -lopengl32 -lglew32 -lfreeglut -lglu32



g++ triangle.cpp -o triangle -lopengl32 -lglew32 -lfreeglut -lglu32



g++ nicegame41.cpp grid_quad_generator.cpp -o nicegame41 -lopengl32 -lglew32 -lfreeglut -lglu32



g++ nicegame42.cpp grid_quad_generator.cpp -o nicegame42 -lopengl32 -lglew32 -lfreeglut -lglu32

g++ nicegame42.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp GameObjects.cpp -o nicegame42 -lopengl32 -lglew32 -lfreeglut -lglu32

g++ nicegame43.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp  GameObjects.cpp -o nicegame43 -lopengl32 -lglew32 -lfreeglut -lglu32

g++ nicegame44.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp GameObjects.cpp -o nicegame44 -lopengl32 -lglew32 -lfreeglut -lglu32

-LC:\Windows\system32 herpmytargetcodederp.c ws2_32.dll

g++ nicegame44.cpp grid_quad_generator.cpp game_client.cpp -LC:\Windows\system32 game_server.cpp  ws2_32.dll game_shared.cpp GameObjects.cpp -o nicegame44 -lopengl32 -lglew32 -lfreeglut -lglu32

g++ nicegame44.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp GameObjects.cpp -o nicegame44 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ nicegame45.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp GameObjects.cpp -o nicegame45 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ nicegame46.cpp grid_quad_generator.cpp game_client.cpp game_server.cpp game_shared.cpp GameObjects.cpp -o nicegame46 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ udpgame1.cpp grid_quad_generator.cpp udpgame1/game_client.cpp udpgame1/game_server.cpp udpgame1/udpgame_shared.cpp udpgame1/GameObjects.cpp -o udpgame1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame1.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame2.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame3.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame4.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32,--subsystem,windows

g++ yogame5.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame5 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32,--subsystem,windows


cmake -G "MinGW Makefiles" -S . -B . -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32
mingw32-make configure
mingw32-make all
mingw32-make install

g++ main.cpp -o main.exe -lglfwdll
pacman -S mingw-w64-x86_64-glfw

Generating with command-line CMake
To make a build directory, pass the source and build directories to the cmake command. These can be relative or absolute paths. The build directory is created if it doesn't already exist.

cmake -S path/to/glfw -B path/to/build
It is common to name the build directory build and place it in the root of the source tree when only planning to build a single configuration.

cd path/to/glfw
cmake -S . -B build
Without other flags these will generate Visual Studio project files on Windows and makefiles on other platforms. You can choose other targets using the -G flag.

cmake -S path/to/glfw -B path/to/build -G Xcode
By default, GLFW will use Wayland and X11 on Linux and other Unix-like systems other than macOS. To disable support for one or both of these, set the GLFW_BUILD_WAYLAND and/or GLFW_BUILD_X11 CMake option.

cmake -S path/to/glfw -B path/to/build -D GLFW_BUILD_X11=0

cmake -S path/to/glfw -B path/to/build -D BUILD_SHARED_LIBS=ON


D:\glfw-3.4-cmake\build-glfw3

cmake -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3 -D BUILD_SHARED_LIBS=ON

cmake -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-static -D BUILD_SHARED_LIBS=OFF

cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-shared -D BUILD_SHARED_LIBS=ON
OK
cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-static -D BUILD_SHARED_LIBS=OFF

-- cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-shared2 -D BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32
cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-shared2 -D BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32


cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-shared2 -D BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32
cmake -G "MinGW Makefiles" -S D:/glfw-3.4-cmake/glfw-3.4 -B D:/glfw-3.4-cmake/build-glfw3-static2 -D BUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=C:\mingw64\x86_64-w64-mingw32

cd build-glfw3-shared2
mingw32-make all
mingw32-make install
cd ..
cd build-glfw3-static2
mingw32-make all
mingw32-make install
//build-glfw3-shared2
// glfw3_colo1.cpp

g++ glfw3_colo1.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o glfw3_colo1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32,--subsystem,windows
g++ glfw3_colo1.cpp grid_quad_generator.cpp udpgame1/GameObjects.cpp src/glad.c -o glfw3_colo1 -I path/to/glad/include -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 --subsystem,windows

g++ glfw3_colo1.cpp grid_quad_generator.cpp udpgame1/GameObjects.cpp src/glad.c -o glfw3_colo1 -I path/to/glad/include -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 


g++ glfw3_2d_platformer.cpp grid_quad_generator.cpp udpgame1/GameObjects.cpp src/glad.c -o glfw3_2d_platformer -I path/to/glad/include -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 
g++ glfw3_2d_platformer2.cpp grid_quad_generator.cpp udpgame1/GameObjects.cpp src/glad.c -o glfw3_2d_platformer2 -I path/to/glad/include -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 

// .cpp

g++ tutorial06_2.cpp -o tutorial06_2 -I D:/ogl-samples-master/ogl-samples-master/external -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 


g++ tutorial06_2.cpp D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o tutorial06_2 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 

g++ glfw3_opengl140.cpp D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o glfw3_opengl140 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 

glfw3_opengl140_2.cpp
g++ glfw3_opengl140_2.cpp D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o glfw3_opengl140_2 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lfreeglut -lglu32 -lws2_32 -lglfw3 -lgdi32 

g++ glfw3_opengl140_2.cpp opengl31\glad.c D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o glfw3_opengl140_2 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lglu32 -lws2_32 -lglfw3 -lgdi32 

g++ glfw3_opengl140_3.cpp opengl31\glad.c D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o glfw3_opengl140_3 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lglu32 -lws2_32 -lglfw3 -lgdi32 

g++ glfw3_opengl140_4.cpp opengl31\glad.c D:\ogl-master\ogl-master\common\controls.cpp D:\ogl-master\ogl-master\common\shader.cpp D:\ogl-master\ogl-master\common\texture.cpp -o glfw3_opengl140_4 -I D:/ogl-master/ogl-master -I D:/ogl-master/ogl-master/external/glm-0.9.7.1 -lopengl32 -lglew32 -lglu32 -lws2_32 -lglfw3 -lgdi32 


g++ yogame5.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame5 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32,--subsystem,windows


g++ yogame6.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame6 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ yogame7.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame7 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame8.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame8 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame9.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame9 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame10.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame10 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame11.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame11 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ okgame11.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o okgame11 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ yogame12.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame12 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ yogame13.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame13 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
	

g++ yogame14.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame14 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ algame14.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o algame14 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

Cmake GUI
D:\OpenAL_1-1_SDK SDK to use
D:\Source\freealut-master build to D:\Source\freealut-build4

CMAKE_INSTALL_PREFIX D:/Alux
D:\OpenAL_1-1_SDK\include
D:\OpenAL_1-1_SDK\libs\Win64\OpenAL-32.lib
D:\OpenAL_1-1_SDK\libs\Win32\OpenAL-32.lib
D:
cd D:\Source\freealut-master build to D:\Source\freealut-build4
mingw32-make all
mingw32-make install


g++ yogame15.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o yogame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

vao_multiple_test1.cpp
//

g++ vao_multiple_test1.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_test1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_test2.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_test2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_test3.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_test3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ vao_multiple_test4.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_test4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ algame15.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o algame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lopenal -lpthread

g++ algame15.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o algame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread

g++ algame15.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o algame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -l"D:/Alut/bin/libalut.dll"
g++ algame15.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o algame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -l"D:/OpenAL_1-1_SDK/libs/Win64/OpenAL32.lib"
g++ algame15.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32


g++ algame16.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame16 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32

algame_Box16.cpp

g++ algame_Box16.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box16 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include"

g++ algame_Box16.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box16 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

g++ algame_Box17.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box17 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

g++ algame_Box18.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box18 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

g++ algame_Box19.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box19 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

g++ algame_Box20.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box20 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D -O0 -g
for gdb zymbols

g++ algame_Box20.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o algame_Box20 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

// stbgame_Box1.cpp

g++ stbgame_Box1.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o stbgame_Box1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 


D:\games-samples-main\games-samples-main\codelabs\native-gamepad\start>D:\jdk-23\bin\java -jar bundletool-all-1.18.1.jar build-apks --bundle=app/build/outputs/bundle/debug/app-debug.aab --output=nativegamepad.apks --local-testing

D:\games-samples-main\games-samples-main\codelabs\native-gamepad\start>D:\jdk-23\bin\java -jar bundletool-all-1.18.1.jar build-apks --bundle=app/build/outputs/bundle/debug/app-debug.aab --output=nativegamepad.apks --local-testing
java -jar bundletool-all-1.0.0.jar install-apks --apks=nativegamepad.apks

java -jar bundletool-all-1.0.0.jar 
D:\games-samples-main\games-samples-main\codelabs\native-gamepad\start>
D:\jdk-23\bin\java -jar bundletool-all-1.18.1.jar install-apks --apks=nativegamepad.apks
D:\jdk-23\bin\java -jar bundletool-all-1.18.1.jar install-apks --apks=nativegamepad.apks --device-id adb-W495HES8XGJZLRZX-HQ1Jcq._adb-tls-connect._tcp
D:\jdk-23\bin\java -jar bundletool-all-1.18.1.jar install-apks --apks=nativegamepad.apks --device-id emulator-5554


g++ vao_multiple_test4.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_test4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ stbgame_Box2.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o stbgame_Box2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 
g++ stbgame_Box3.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o stbgame_Box3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D 

g++ vao_multiple_text1.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_text1 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ vao_multiple_text2.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_text2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text3.cpp grid_quad_generator.cpp  udpgame1/GameObjects.cpp -o vao_multiple_text3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text4.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp -o vao_multiple_text4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32


g++ vao_multiple_text5.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp -o vao_multiple_text5 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text6.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp -o vao_multiple_text6 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text6.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text6 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text7.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text7 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text8.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text8 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text9.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text9 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text10.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text10 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text11.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text11 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text11

g++ vao_multiple_text12.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text12 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

vao_multiple_text12


g++ vao_multiple_text13.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text13 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

vao_multiple_text13

g++ vao_multiple_text14.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text14 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32

g++ vao_multiple_text15.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp -o vao_multiple_text15 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text15

// SpriteManager.cpp
g++ vao_multiple_text16.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text16 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text16

g++ vao_multiple_text17.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text17 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text17


g++ vao_multiple_text18.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text18 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text18

g++ vao_multiple_text19.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text19 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text19

g++ vao_multiple_text20.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text20 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text20


g++ vao_multiple_text21.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text21 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text21

g++ vao_multiple_text22.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text22 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text22

g++ vao_multiple_text23.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text23 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text23

g++ vao_multiple_text24.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text24 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text24

g++ vao_multiple_text25.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text25 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text25

g++ vao_multiple_text26.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text26 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
vao_multiple_text26


D:/Source/absl/include/
D:/Source/absl/lib/

g++ vao_multiple_text27.cpp npc/ai/ai_badguy1.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text27 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text27


g++ vao_multiple_text27_tensorflow.cpp npc/ai/ai_badguy1.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text27 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text27


g++ vao_multiple_text28.cpp  engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text28 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text28

g++ vao_multiple_text29.cpp  engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text29 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text29
// updating DDS level spirmate transpacy fix

g++ vao_multiple_text30.cpp  engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text30 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text30

g++ vao_multiple_text31.cpp  engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text31 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text31


g++ vao_multiple_text32.cpp  engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text32 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text32

g++ vao_multiple_text33.cpp spritecode/MapManager.cpp scenecode/input_util.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text33 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text33

g++ vao_multiple_text34.cpp spritecode/MapManager.cpp scenecode/input_util.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text34 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text34

g++ vao_multiple_text35.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text35 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text35


g++ vao_multiple_text36.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text36 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl"
vao_multiple_text36

g++ vao_multiple_text36.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text36 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text36

tunnelgui implemented

g++ vao_multiple_text37.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text37 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text37

// https://developer.android.com/google/play/billing/test


g++ vao_multiple_text38.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text38 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text38


g++ vao_multiple_text39.cpp scenecode/colo_play_scene.h scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text39 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text39

gcc relay_server_client1.c -o relay_server_client1 -l ws2_32


g++ vao_multiple_text40.cpp scenecode/colo_play_scene.h scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text40 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text40


g++ vao_multiple_text41.cpp scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text41 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text41

g++ vao_multiple_text42.cpp scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text42 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text42

g++ vao_multiple_text43.cpp scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text43 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text43

g++ vao_multiple_text44.cpp scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text44 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text44

g++ vao_multiple_text45.cpp scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text45 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include"
vao_multiple_text45

g++ vao_multiple_text46.cpp scenecode/colo_buttons/colo_button2.cpp  scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text46 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include" -I"Libraries/glew-2.2.0-win32/glew-2.2.0/include" -I"/C/freeglut-3.6.0/include"
vao_multiple_text46
D:\games_src\android_colo_game\Libraries\glew-2.2.0-win32\glew-2.2.0\include
g++ vao_multiple_text46.cpp scenecode/colo_buttons/colo_button2.cpp  scenecode/colo_buttons/colo_button.cpp  scenecode/colo_buttons/colo_synergy_button.cpp scenecode/colo_play_scene.cpp scenecode/login_scene.cpp scenecode/anim.cpp scenecode/obstacle.cpp scenecode/obstacle_generator.cpp  scenecode/texture.cpp scenecode/our_shader.cpp scenecode/play_scene.cpp  scenecode/dialog_scene.cpp scenecode/ascii_to_geom.cpp scenecode/util.cpp scenecode/sfxman.cpp  scenecode/welcome_scene.cpp scenecode/indexbuf.cpp scenecode/vertexbuf.cpp scenecode/shader.cpp scenecode/shape_renderer.cpp scenecode/text_renderer.cpp spritecode/MapManager.cpp scenecode/ui_scene.cpp scenecode/input_util.cpp scenecode/loader_scene.cpp scenecode/scene_manager.cpp scenecode/scene.cpp engine/player/player_game.cpp UtilityCode/grid_quad_generator.cpp engine/shader/shader.cpp UtilityCode/Utility.cpp   udpgame1/GameObjects.cpp spritecode/hindi_text.cpp spritecode/save_texture.cpp spritecode/SpriteManager.cpp spritecode/SpriteManagerUtility.cpp -o vao_multiple_text46 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -I"D:/Source/tensorflow" -I"D:/Source/absl/include" -L"D:/Source/absl/lib" -I"D:/Source/protobuf-25.7/protobuf-25.7/src" -I"D:/Source/tensorflow/third_party/xla" -I"D:/Source/eigen-master/eigen-master" -I"D:/Source/tensorflow/third_party/xla/third_party/tsl" -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -lalut -I"D:/OpenAL_1-1_SDK/include" -I"Libraries/glew-2.2.0-win32/glew-2.2.0/include" -I"/C/freeglut-3.6.0/include"


gcc rebuild_game2.cpp -o rebuild_game2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" 

gcc rebuild_glfw3_game2.cpp -o rebuild_glfw3_game2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" 


gcc rebuild_glfw3_game2.cpp -o rebuild_glfw3_game2 -lopengl32 -lglew32 -lglfw3dll  -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"  -L"D:/Source/absl/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib/"

gcc rebuild_glfw3_game2.cpp   -o rebuild_glfw3_game2    -lopengl32 -lglew32 -lgdi32 -L"C:\mingw64\x86_64-w64-mingw32\lib" -lglu32 -lglfw3 -I "D:/glfw-3.4-cmake/build-glfw3-static-install/include/"  -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"   -L"D:/glfw-3.4-cmake\build-glfw3-static-install/lib"
opengl32


gcc rebuild_glfw3_game2.cpp -o rebuild_glfw3_game2 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32
// -l:libgdi32.a
// -luser32 -lkernel32

gcc rebuild_glfw3_game3.cpp -o rebuild_glfw3_game3 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


gcc rebuild_glfw3_game3.cpp ubershader/ubershader.cpp -o rebuild_glfw3_game3 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


gcc rebuild_glfw3_game2_2.cpp -o rebuild_glfw3_game2_2 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

rebuild_glfw3_game2_2.cpp

rebuild3_glfw1.cpp

g++ rebuild3_glfw1.cpp -o rebuild3_glfw1 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

g++ rebuild_glfw3_game2_2.cpp -o rebuild_glfw3_game2_2 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


g++ rebuild_glfw3_game3.cpp ubershader/ubershader.cpp  -o rebuild_glfw3_game3 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


g++ rebuild3_glfw2.cpp -o rebuild3_glfw2 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

g++ rebuild3_glfw6.cpp -o rebuild3_glfw6 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

g++ rebuild3_glfw7.cpp -o rebuild3_glfw7 -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

g++ rebuild3_glfw8.cpp colo_engine\math\triangle_rotate.cpp -o rebuild3_glfw8  -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32

g++ rebuild3_glfw9.cpp colo_engine\math\triangle_rotate.cpp -o rebuild3_glfw9  -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


g++ main_colo.cpp colo_engine\shaders\colo_uber_Shader.cpp colo_engine\loadtexture\loadtexture.cpp colo_engine\math\triangle_rotate.cpp -o main_colo -I"C:/android_pc_game/scenecode" -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32
