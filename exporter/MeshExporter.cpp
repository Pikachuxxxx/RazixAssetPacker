#include "MeshExporter.h"

#include <chrono>
#include <fstream>
#include <iostream>

#define WRITE_AND_OFFSET(stream, dest, size, offset) \
    stream.write((char*) dest, size);                \
    offset += size;                                  \
    stream.seekg(offset);

namespace Razix {
    namespace Tool {
        namespace AssetPacker {

            bool MeshExporter::exportMesh(const MeshImportResult& import_result, const MeshExportOptions& options)
            {
                auto start = std::chrono::high_resolution_clock::now();

                std::string materials_path = "Materials/";

                for (size_t i = 0; i < import_result.submeshes.size(); i++) {
                    const auto submesh = import_result.submeshes[i];

                    std::string export_path = options.outputDirectory + "/" + import_result.name + "/" + submesh.name + ".rzmesh";

                    // Export the Mesh
                    std::fstream f(export_path, std::ios::out | std::ios::binary);

                    if (f.is_open()) {
                        BINFileHeader fh{};
                        char*         magic = new char[18];

                        magic[0]  = 'r';
                        magic[1]  = 'a';
                        magic[2]  = 'z';
                        magic[3]  = 'i';
                        magic[4]  = 'z';
                        magic[5]  = '_';
                        magic[6]  = 'e';
                        magic[7]  = 'n';
                        magic[8]  = 'g';
                        magic[9]  = 'i';
                        magic[10] = 'n';
                        magic[11] = 'e';
                        magic[12] = '_';
                        magic[13] = 'a';
                        magic[14] = 's';
                        magic[15] = 's';
                        magic[16] = 'e';
                        magic[17] = 't';

                        fh.magic   = magic;
                        fh.version = RAZIX_ASSET_VERSION;
                        fh.type    = ASSET_MESH;

                        BINMeshFileHeader header{};

                        // Copy Name
                        strcpy(&header.name[0], import_result.name.c_str());
                        header.name[import_result.name.size()] = '\0';

                        header.index_count           = submesh.index_count;
                        header.vertex_count          = submesh.vertex_count;
                        header.skeletal_vertex_count = import_result.skeletal_vertices.size();
                        header.material_count        = import_result.materials.size();
                        header.mesh_count            = import_result.submeshes.size();
                        header.max_extents           = import_result.max_extents;
                        header.min_extents           = import_result.min_extents;

                        size_t offset = 0;

                        // Write Asset File header
                        WRITE_AND_OFFSET(f, (char*) &fh, sizeof(BINFileHeader), offset);

                        // Write mesh header
                        WRITE_AND_OFFSET(f, (char*) &header, sizeof(BINMeshFileHeader), offset);

                        // Write vertices
                        if (import_result.vertices.size() > 0) {
                            uint32_t start_vtx_idx = submesh.base_vertex;
                            auto&    data          = import_result.vertices;
                            auto     subData       = std::vector<Graphics::RZVertex>(data.begin() + start_vtx_idx, data.begin() + start_vtx_idx + submesh.vertex_count);

                            WRITE_AND_OFFSET(f, (char*) &subData[0], sizeof(Graphics::RZVertex) * submesh.vertex_count, offset);
                        }

                        // Write skeletal vertices
                        if (import_result.skeletal_vertices.size() > 0) {
                            WRITE_AND_OFFSET(f, (char*) &import_result.skeletal_vertices[0], sizeof(Graphics::RZSkeletalVertex) * import_result.skeletal_vertices.size(), offset);
                        }

                        // Write indices
                        if (import_result.indices.size() > 0) {
                            uint32_t start_idx_idx = submesh.base_index;
                            auto     data          = import_result.indices;
                            auto     subData       = std::vector<uint32_t>(data.begin() + start_idx_idx, data.begin() + start_idx_idx + submesh.index_count);

                            WRITE_AND_OFFSET(f, (char*) &subData[0], sizeof(uint32_t) * submesh.index_count, offset);
                        }

                        // Write mesh headers
                        if (import_result.submeshes.size() > 0) {
                            WRITE_AND_OFFSET(f, (char*) &submesh, sizeof(SubMesh), offset);
                        }

                        f.close();

                    } else
                        return false;
                }

                auto                          finish = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> time   = finish - start;

                std::cout << "Successfully Exported mesh in " << time.count() << " seconds" << std::endl;
                return true;
            }
        }    // namespace AssetPacker
    }        // namespace Tool
}    // namespace Razix