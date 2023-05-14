#pragma once

#include <glm/glm.hpp>
#include <stdint.h>

#define AST_VERSION 1

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

#define RAZIX_ASSET_VERSION 0x1

            /* Type of the asset file */
            enum AssetType : uint8_t
            {
                ASSET_MESH     = 0,
                ASSET_MATERIAL = 1
            };

            /* Header contents of the binary asset file */
            struct BINFileHeader
            {
                uint32_t magic;   /* Magic number to verify that this is a Razix Asset file indeed  */
                uint8_t  version; /* Version of the asset file                                      */
                uint8_t  type;    /* Type of the asset : AssetType                                  */
            };

            struct BINMeshFileHeader
            {
                uint32_t  mesh_count;
                uint32_t  material_count;
                uint32_t  vertex_count;
                uint32_t  skeletal_vertex_count;
                uint32_t  index_count;
                glm::vec3 max_extents;
                glm::vec3 min_extents;
                char      name[150];
            };

        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix