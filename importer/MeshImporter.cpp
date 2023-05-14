#include "MeshImporter.h"

#include <chrono>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/pbrmaterial.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <unordered_map>
#include <unordered_set>

#include "Razix/Graphics/Materials/RZMaterialData.h"

std::string GetFilePathExtension(const std::string& FileName)
{
    auto pos = FileName.find_last_of('.');
    if (pos != std::string::npos)
        return FileName.substr(pos + 1);
    return "";
}

std::string RemoveFilePathExtension(const std::string& FileName)
{
    auto pos = FileName.find_last_of('.');
    if (pos != std::string::npos)
        return FileName.substr(0, pos);
    return FileName;
}

std::string GetFileName(const std::string& FilePath)
{
    auto pos = FilePath.find_last_of('/');
    if (pos != std::string::npos)
        return FilePath.substr(pos + 1);
    return FilePath;
}

std::string GetFileLocation(const std::string& FilePath)
{
    auto pos = FilePath.find_last_of('/');
    if (pos != std::string::npos)
        return FilePath.substr(0, pos + 1);
    return FilePath;
}

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            bool MeshImporter::importMesh(const std::string& meshFilePath, MeshImportResult& result, MeshImportOptions& options)
            {
                bool isGlTF = false;

                if (meshFilePath[0] == '/' && meshFilePath[1] == '/') {
                    std::cout << "[ERROR!] Using virtual path! Please check your path and try again." << std::endl;
                    return false;
                }

                std::string extension     = GetFilePathExtension(meshFilePath);
                std::string directoryPath = GetFileLocation(meshFilePath);
                std::string meshName      = GetFileName(meshFilePath);
                meshName                  = RemoveFilePathExtension(meshName);

                std::cout << "Importing Mesh...\n";

                auto start = std::chrono::high_resolution_clock::now();

                const aiScene*   scene = nullptr;
                Assimp::Importer importer;

                scene = importer.ReadFile(meshFilePath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_ImproveCacheLocality | aiProcess_JoinIdenticalVertices);

                if (scene) {
                    result.name = meshName;

                    result.submeshes.resize(scene->mNumMeshes);
                    result.materials.resize(scene->mNumMaterials);

                    uint32_t                 vertex_count = 0;
                    uint32_t                 index_count  = 0;
                    uint32_t                 unnamed_mats = 1;
                    std::vector<uint32_t>    temp_indices;
                    std::vector<std::string> texturePaths;

                    // Read the Materials
                    for (uint32_t i = 0; i < scene->mNumMaterials; i++) {
                    }

                } else {
                    std::cout << "[ERROR!] Failed to load model\n";
                    return false;
                }
                return true;
            }
        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix