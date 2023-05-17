#pragma once

#include "common/intermediate_types.h"

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            struct MeshExportOptions
            {
                std::string outputDirectory;
                bool        useCompression = true;
                bool        outputMetadata = false;
            };

            class MeshExporter
            {
            public:
                MeshExporter()  = default;
                ~MeshExporter() = default;

                bool exportMesh(const MeshImportResult& import_result, const MeshExportOptions& options);
                bool exportMaterial() {}
            };

        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix