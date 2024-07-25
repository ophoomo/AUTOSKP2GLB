#ifndef EXTRACT_H
#define EXTRACT_H

#include "SketchUpAPI/sketchup.h"
#include "tiny_gltf.h"

struct Face {
    std::vector<float> vertices;
    std::vector<uint16_t> indices;
};

struct Group {
    std::vector<Face> faces;
};

struct Extract {
    std::vector<Face> faces;
    std::vector<Group> groups;
};

uint16_t get_vertex_index(size_t length, std::vector<SUVertexRef> vectors, SUVertexRef target);
void extract_faces_from_group(SUEntitiesRef group_entities, std::vector<SUFaceRef>& faces);

Extract extract_model(SUModelRef &skpModel);
std::vector<Face> extract_faces(SUEntitiesRef entities);
std::vector<Group> extract_groups(SUEntitiesRef entities);
std::vector<float> extract_instances(SUEntitiesRef entities);

#endif //EXTRACT_H
