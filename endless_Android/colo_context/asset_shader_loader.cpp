
#include "asset_shader_loader.h"

/*
std::string ColoShaderLoader::loadTextAsset(AAssetManager *assetManager, const std::string &assetPath) {

   //  loadCompressedTexture( assetPath.c_str(), 0);
  //  AAsset* asset = AAssetManager_open(assetManager, "a.pkm", AASSET_MODE_BUFFER);
    AAsset* asset = AAssetManager_open(assetManager, assetPath.c_str(), AASSET_MODE_BUFFER);
    if (!asset) {
        // Handle error
        return NULL;
    }

    size_t assetLength = AAsset_getLength(asset);
    unsigned char* buffer = new unsigned char[assetLength];
    AAsset_read(asset, buffer, assetLength);



    AAsset_close(asset);
	
	//return std::string((std::istreambuf_iterator<char>(file)),
	return std::string((std::istreambuf_iterator<char>(buffer)),
                        std::istreambuf_iterator<char>());
	}
	*/
	// m_assetMgr
	std::string ColoAssetShaderLoader::loadTextAsset(AAssetManager *assetManager, const std::string &assetPath) {
    if (assetManager == nullptr) return "";

    // Open asset in buffering mode
    AAsset* asset = AAssetManager_open(assetManager, assetPath.c_str(), AASSET_MODE_BUFFER);
    if (!asset) {
        // Log error here if you have a logger (e.g., __android_log_print)
        return ""; 
    }

    // Get the size and read into a vector
    off_t assetLength = AAsset_getLength(asset);
    std::vector<char> buffer(assetLength);
    
    int readResult = AAsset_read(asset, buffer.data(), assetLength);
    AAsset_close(asset);

    if (readResult < 0) return "";

    // Convert vector to string
    return std::string(buffer.begin(), buffer.end());
}
	