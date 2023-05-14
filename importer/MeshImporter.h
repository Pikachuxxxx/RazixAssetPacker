#pragma once

#include "common/intermediate_types.h"

#include <assimp/material.h>

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            struct MeshImportOptions
            {
                bool  flipUVs        = false;
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

            private:
                void readMaterial(const std::string& materialsDirectory, aiMaterial* aiMat, Graphics::MaterialData& material);

                bool findTexurePath(const std::string& materialsDirectory, aiMaterial* aiMat, uint32_t index, aiTextureType textureType, std::string& material);

            private:
                bool m_IsGlTF = false;
            };
        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix