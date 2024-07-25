#ifndef GLTF_H
#define GLTF_H

#include "extract.h"
#include "tiny_gltf.h"

void export_to_glb(const std::string &output_filepath, const Extract& extract);
void create_faces(tinygltf::Model &model, const std::vector<float>& vertices, const std::vector<uint16_t>& indices);

#endif //GLTF_H
