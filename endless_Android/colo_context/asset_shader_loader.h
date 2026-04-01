#ifndef COLO_ASSET_SHADER_LOADER_H
#define COLO_ASSET_SHADER_LOADER_H

//#include <string>
//#include <GLES2/gl2.h>

#include <memory>
#include <android/asset_manager.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ColoAssetShaderLoader {
public:
    // Reads a file into a string
   // static std::string LoadShaderSource(const char* filePath);
    static std::string  loadTextAsset(AAssetManager *assetManager, const std::string &assetPath);

    // Loads, compiles, and links a VS and FS from files
    // Returns the Program ID, or 0 on failure
  //  static GLuint CreateProgramFromFiles(const char* vertPath, const char* fragPath);

private:
    // Internal helper for compilation errors
   // static GLuint CompileShader(GLenum type, const char* source);
};

#endif

