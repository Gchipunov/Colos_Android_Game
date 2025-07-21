
#include "loadtexture.h"

GLuint loadTexture(const char* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
       // std::cout << "Failed to load texture" << std::endl;
	   printf("Failed to load texture\n");
    }
    stbi_image_free(data);
    return textureID;
}

GLFWcursor* LoadCursor(GLFWwindow* window)
{

	int cursor_width, cursor_height, cursor_channels;
  unsigned char* image_data = stbi_load("assets/cursor.png", &cursor_width, &cursor_height, &cursor_channels, 0);
 GLFWcursor* cursor = NULL;
 
  if (image_data) {
    // Create a GLFWimage structure
    GLFWimage image;
    image.width = cursor_width;
    image.height = cursor_height;
    image.pixels = image_data;
// https://www.glfw.org/docs/latest/input_guide.html#:~:text=%EE%80%80GLFW%EE%80%81%20needs%20to%20poll%20the%20window%20system%20for
    // Define the hotspot (e.g., center of the image)
  //  const GLFWcursorpos i = {cursor_width / 2, cursor_height / 2};
  double xpos, ypos;
glfwGetCursorPos(window, &xpos, &ypos);
//GLFWcursorposfun 
    // Create the cursor
    //GLFWcursor* cursor = glfwCreateCursor(&image, i.x, i.y);
    // cursor = glfwCreateCursor(&image, i.x, i.y);
 cursor = glfwCreateCursor(&image, xpos, ypos);
    // Set the cursor for the window
    glfwSetCursor(window, cursor);

    // Free the image data
    stbi_image_free(image_data);
  }
  return cursor;
  
	
}

GLFWcursor* CreateCursor(GLFWwindow* window)
{
	unsigned char pixels[16 * 16 * 4];
memset(pixels, 0xff, sizeof(pixels));
 
GLFWimage image;
image.width = 16;
image.height = 16;
image.pixels = pixels;
 
GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
glfwSetCursor(window, cursor);
return cursor;

}