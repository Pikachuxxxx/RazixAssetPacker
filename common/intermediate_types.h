#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Razix/Graphics/RZVertexFormat.h"

#include "bin_file_header.h"

namespace Razix {
    namespace Graphics {
        class RZMaterial;
    }
}    // namespace Razix

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            /**
             * Submesh is a part of mesh that will be drawn, can be used to split a mesh into multiple small sub-meshes
             * Or it can be used to create multiple materials for a mesh. [Design TBD]
             */
            struct SubMesh
            {
                uint32_t  material_index; /* The index of the material that this submesh will use to render */
                uint32_t  index_count;    /* Total indices count in the sub mesh */
                uint32_t  vertex_count;   /* Total vertices count in the sub mesh */
                uint32_t  base_vertex;    /* vertex offset into the Vertex Buffer of the parent mesh  */
                uint32_t  base_index;     /* index offset into the index buffer of the parent mesh */
                glm::vec3 max_extents;    /* Maximum extents of the sub mesh */
                glm::vec3 min_extents;    /* Minimum extents of the sub mesh */
                char      name[150];      /* Name of the sub-mesh */
            };

            //--------------------------------------------------------------------------------
            //Mesh Import Result
            //--------------------------------------------------------------------------------

            struct MeshImportResult
            {
                std::string                                    name;
                std::vector<Razix::Graphics::RZVertex>         vertices;
                std::vector<Razix::Graphics::RZSkeletalVertex> skeletal_vertices;
                std::vector<uint32_t>                          indices;
                std::vector<SubMesh>                           submeshes;
                std::vector<Graphics::RZMaterial*>             materials;
                glm::vec3                                      max_extents;
                glm::vec3                                      min_extents;
            };
        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix