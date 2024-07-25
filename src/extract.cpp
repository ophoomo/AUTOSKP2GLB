#include "header/extract.h"

#include "spdlog/spdlog.h"

// void check_error(SUResult result, const char* msg) {
//     if (result != SU_ERROR_NONE) {
//         std::cerr << msg << std::endl;
//         exit(1);
//     }
// }

uint16_t get_vertex_index(size_t length, std::vector<SUVertexRef> vectors, SUVertexRef target) {
    for (size_t i = 0; i < length; i++) {
        SUPoint3D point{}, point_target{};
        SUVertexGetPosition(vectors[i], &point);
        SUVertexGetPosition(target, &point_target);

        if (point.x == point_target.x && point.y == point_target.y && point.z == point_target.z) return i;
    }

    return -1;
}

void extract_faces_from_group(SUEntitiesRef group_entities, std::vector<SUFaceRef>& faces) {
    size_t face_count = 0;
    SUEntitiesGetNumFaces(group_entities, &face_count);

    std::vector<SUFaceRef> group_faces(face_count);
    SUEntitiesGetFaces(group_entities, face_count, group_faces.data(), &face_count);

    faces.insert(faces.end(), group_faces.begin(), group_faces.end());
}

Extract extract_model(SUModelRef &skp_model) {
    spdlog::info("start extract model");

    Extract extract{};

    SUEntitiesRef entities = SU_INVALID;
    SUModelGetEntities(skp_model, &entities);

    std::vector<Face> faces = extract_faces(entities);
    extract.faces = faces;

    std::vector<Group> groups = extract_groups(entities);
    extract.groups = groups;

    return extract;
}

std::vector<Face> extract_faces(SUEntitiesRef entities) {
    std::vector<Face> result;

    size_t face_count = 0;
    SUEntitiesGetNumFaces(entities, &face_count);
    spdlog::info("found {} face", face_count);

    std::vector<SUFaceRef> faces(face_count);
    SUEntitiesGetFaces(entities, face_count, faces.data(), &face_count);

    for (const auto& face : faces) {

        std::vector<float> vertices;
        std::vector<uint16_t> indices;

        Face result_face{};

        size_t vertex_count = 0;
        SUFaceGetNumVertices(face, &vertex_count);

        std::vector<SUVertexRef> vertices_refs(vertex_count);
        SUFaceGetVertices(face, vertex_count, vertices_refs.data(), &vertex_count);

        for (size_t i = 0; i < vertex_count; i++) {
            SUPoint3D point{};
            SUVertexGetPosition(vertices_refs[i], &point);
            vertices.push_back(point.x);
            vertices.push_back(point.z);
            vertices.push_back(point.y);
        }

        size_t edge_count = 0;
        SUFaceGetNumEdges(face, &edge_count);

        std::vector<SUEdgeRef> edges(edge_count);
        SUFaceGetEdges(face, edge_count, edges.data(), &edge_count);

        for(const auto& edge : edges) {
            SUVertexRef start, end;
            SUEdgeGetStartVertex(edge, &start);
            SUEdgeGetEndVertex(edge, &end);

            uint16_t start_index = get_vertex_index(vertex_count, vertices_refs, start);
            uint16_t end_index =  get_vertex_index(vertex_count, vertices_refs, end);

            if (start_index > -1) indices.push_back(start_index);
            if (end_index > -1) indices.push_back(end_index);
        }

        result_face.vertices = vertices;
        result_face.indices = indices;

        result.push_back(result_face);
    }

    return result;
}

std::vector<Group> extract_groups(SUEntitiesRef entities) {
    std::vector<Group> result;

    // size_t group_count = 0;
    // SUEntitiesGetNumGroups(entities, &group_count);
    // spdlog::info("found {} groups", group_count);
    //
    // std::vector<SUGroupRef> groups(group_count);
    // SUEntitiesGetGroups(entities, group_count, groups.data(), &group_count);
    //
    // for (const auto& group : groups) {
    //     SUEntitiesRef group_entities = SU_INVALID;
    //     SUGroupGetEntities(group, &group_entities);
    //
    //     std::vector<SUFaceRef> faces;
    //     extract_faces_from_group(group_entities, faces);
    //
    //     for (const auto& face : faces) {
    //         std::vector<float> vertices;
    //         std::vector<uint16_t> indices;
    //
    //         Face result_face{};
    //
    //         size_t vertex_count = 0;
    //         SUFaceGetNumVertices(face, &vertex_count);
    //
    //         std::vector<SUVertexRef> vertices_refs(vertex_count);
    //         SUFaceGetVertices(face, vertex_count, vertices_refs.data(), &vertex_count);
    //
    //         for (size_t i = 0; i < vertex_count; i++) {
    //             SUPoint3D point{};
    //             SUVertexGetPosition(vertices_refs[i], &point);
    //             vertices.push_back(point.x);
    //             vertices.push_back(point.z);
    //             vertices.push_back(point.y);
    //         }
    //
    //         size_t edge_count = 0;
    //         SUFaceGetNumEdges(face, &edge_count);
    //
    //         std::vector<SUEdgeRef> edges(edge_count);
    //         SUFaceGetEdges(face, edge_count, edges.data(), &edge_count);
    //
    //         for (const auto& edge : edges) {
    //             SUVertexRef start, end;
    //             SUEdgeGetStartVertex(edge, &start);
    //             SUEdgeGetEndVertex(edge, &end);
    //
    //             uint16_t start_index = get_vertex_index(vertex_count, vertices_refs, start);
    //             uint16_t end_index = get_vertex_index(vertex_count, vertices_refs, end);
    //
    //             if (start_index != uint16_t(-1)) indices.push_back(start_index);
    //             if (end_index != uint16_t(-1)) indices.push_back(end_index);
    //         }
    //
    //         result_face.vertices = vertices;
    //         result_face.indices = indices;
    //
    //         result.push_back(result_face);
    //     }
    // }

    return result;
}

std::vector<float> extract_instances(SUEntitiesRef entities) {
    std::vector<float> data;

    size_t instances_count = 0;
    SUEntitiesGetNumInstances(entities, &instances_count);
    spdlog::info("found {} instances", instances_count);

    std::vector<SUComponentInstanceRef> instances(instances_count);
    SUEntitiesGetInstances(entities, instances_count, instances.data(), &instances_count);

    for (const auto& instance : instances) {

    }

    return data;
}
