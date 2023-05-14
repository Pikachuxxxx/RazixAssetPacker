#pragma once

#include "common/intermediate_types.h"

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            struct MeshImportOptions
            {
                bool  flipUVs        = false;
                bool  compressMesh   = false;
                bool  encodeVertices = false;
                bool  encodeIndices  = false;
                float mergeDistance  = 0.05f;
            };

            class MeshImporter
            {
            public:
                MeshImporter()  = default;
                ~MeshImporter() = default;

                bool importMesh(const std::string& meshFilePath, MeshImportResult& result, MeshImportOptions& options = MeshImportOptions());
            };
        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix