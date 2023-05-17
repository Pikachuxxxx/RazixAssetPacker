#include <iostream>

#include "exporter/MeshExporter.h"
#include "importer/MeshImporter.h"

int main(int argc, char* argv[])
{
    // TODO: Use command line args

    // Results of the mesh import
    Razix::Tool::AssetPacker::MeshImportResult import_result;
    // Mesh import options
    Razix::Tool::AssetPacker::MeshImportOptions import_options{};

    // Importer
    Razix::Tool::AssetPacker::MeshImporter importer;
    bool                                   result = importer.importMesh("C:/Dev/Game Engines/Razix/Sandbox/Assets/Meshes/Source/YBot.gltf", import_result, import_options);

    if (!result) {
        std::cout << "[ERROR!] Mesh Importing Failed" << std::endl;
        return EXIT_FAILURE;
    }

    // Export Options
    Razix::Tool::AssetPacker::MeshExportOptions export_options{};
    export_options.outputDirectory = "C:/Dev/Game Engines/Razix/Sandbox/Assets/Meshes/";
    // Exporter
    Razix::Tool::AssetPacker::MeshExporter exporter;
    result = exporter.exportMesh(import_result, export_options);

    if (!result) {
        std::cout << "[ERROR!] Mesh Export Failed" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}