
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// gcc glfw3_glew_custom_Cursor_concept.cpp -o glfw3_glew_custom_Cursor_concept -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" 

int main() {
  // ... GLFW initialization ...
  glewInit();

  // Load your cursor image (e.g., using stb_image or similar)
  int cursor_width, cursor_height, cursor_channels;
  unsigned char* image_data = stbi_load("assets\cursor.png", &cursor_width, &cursor_height, &cursor_channels, 0);

  if (image_data) {
    // Create a GLFWimage structure
    GLFWimage image;
    image.width = width;
    image.height = height;
    image.pixels = image_data;

    // Define the hotspot (e.g., center of the image)
    const GLFWcursorpos i = {width / 2, height / 2};

    // Create the cursor
    GLFWcursor* cursor = glfwCreateCursor(&image, i.x, i.y);

    // Set the cursor for the window
    glfwSetCursor(window, cursor);

    // Free the image data
    stbi_image_free(image_data);
  }

  // ... Game loop and rendering ...

  // Destroy the cursor when done
  glfwDestroyCursor(cursor);
  // ... GLFW termination ...
  return 0;
}