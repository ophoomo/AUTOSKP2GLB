#include "header/gltf.h"
#include "header/extract.h"

#include "spdlog/spdlog.h"


void export_to_glb(const std::string& output_filepath, const Extract& extract) {
    tinygltf::Model model;
    tinygltf::TinyGLTF gltf;

    model.asset.version = "2.0";
    model.asset.generator = "SKP2GLB";

    tinygltf::Scene scene;
    model.scenes.push_back(scene);
    model.defaultScene = 0;

    if (!extract.faces.empty()) {
        for (const auto& face : extract.faces) {
            create_faces(model, face.vertices, face.indices);
        }
    }

    if (!extract.groups.empty()) {
        for (const auto& group : extract.groups) {
            // create_faces(model, face.vertices, face.indices);
        }
    }

    gltf.WriteGltfSceneToFile(&model, output_filepath, true, true, true, false);
    spdlog::info("export GLB model path {}", output_filepath);
}

void create_faces(tinygltf::Model &model, const std::vector<float>& vertices, const std::vector<uint16_t>& indices) {
    spdlog::info("create face");
    tinygltf::Buffer vertexBuffer;
    vertexBuffer.data.resize(vertices.size() * sizeof(float));
    memcpy(vertexBuffer.data.data(), vertices.data(), vertices.size() * sizeof(float));

    tinygltf::Buffer indexBuffer;
    indexBuffer.data.resize(indices.size() * sizeof(uint16_t));
    memcpy(indexBuffer.data.data(), indices.data(), indices.size() * sizeof(uint16_t));

    model.buffers.push_back(vertexBuffer);
    model.buffers.push_back(indexBuffer);

    tinygltf::BufferView vertexBufferView;
    vertexBufferView.buffer = 0;
    vertexBufferView.byteOffset = 0;
    vertexBufferView.byteLength = vertexBuffer.data.size();
    vertexBufferView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

    tinygltf::BufferView indexBufferView;
    indexBufferView.buffer = 1;
    indexBufferView.byteOffset = 0;
    indexBufferView.byteLength = indexBuffer.data.size();
    indexBufferView.target = TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER;

    model.bufferViews.push_back(vertexBufferView);
    model.bufferViews.push_back(indexBufferView);

    tinygltf::Accessor vertexAccessor;
    vertexAccessor.bufferView = 0;
    vertexAccessor.byteOffset = 0;
    vertexAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
    vertexAccessor.count = vertices.size() / 3;
    vertexAccessor.type = TINYGLTF_TYPE_VEC3;

    tinygltf::Accessor indexAccessor;
    indexAccessor.bufferView = 1;
    indexAccessor.byteOffset = 0;
    indexAccessor.componentType = TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT;
    indexAccessor.count = indices.size();
    indexAccessor.type = TINYGLTF_TYPE_SCALAR;

    model.accessors.push_back(vertexAccessor);
    model.accessors.push_back(indexAccessor);

    tinygltf::Primitive primitive;
    primitive.attributes["POSITION"] = 0;
    primitive.indices = 1;
    primitive.mode = TINYGLTF_MODE_TRIANGLE_STRIP;

    tinygltf::Mesh mesh;
    mesh.primitives.push_back(primitive);

    model.meshes.push_back(mesh);

    tinygltf::Node node;
    node.mesh = 0;

    model.nodes.push_back(node);
    model.scenes[0].nodes.push_back(0);
}
