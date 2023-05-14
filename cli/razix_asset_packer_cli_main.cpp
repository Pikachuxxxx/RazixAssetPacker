#include <iostream>

#include "importer/MeshImporter.h"

int main(int argc, char* argv[])
{
    // Results of the mesh import
    Razix::Tool::AssetPacker::MeshImportResult importResult;
    // Mesh import options
    Razix::Tool::AssetPacker::MeshImportOptions import_options{};

    Razix::Tool::AssetPacker::MeshImporter importer;
    bool                                   result = importer.importMesh("C:/Dev/Game Engines/Razix/Sandbox/Assets/Meshes/Source/Chess/scene.gltf", importResult, import_options);

    if (result)
        return EXIT_SUCCESS;
    else {
        std::cout << "[ERROR!] Mesh Importing Failed" << std::endl;
        return EXIT_FAILURE;
    }
}