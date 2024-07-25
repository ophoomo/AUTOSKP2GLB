#include "header/convert.h"

#include "header/extract.h"
#include "header/gltf.h"
#include "spdlog/spdlog.h"

SUModelRef load_sketchup_model(const std::string& filepath) {
    spdlog::info("load SketchUp model from {}", filepath);
    SUModelRef model = SU_INVALID;
    SUModelLoadStatus status;
    SUResult res = SUModelCreateFromFileWithStatus(&model, filepath.c_str(), &status);
    if (res != SU_ERROR_NONE) {
        spdlog::error("Failed to load SketchUp model");
    }
    return model;
}


void convert_skp2glb(const std::string& inputPath, const std::string& outputPath)
{
    SUInitialize();

    SUModelRef model = load_sketchup_model(inputPath);
    Extract extract = extract_model(model);
    SUModelRelease(&model);

    export_to_glb(outputPath, extract);

    SUTerminate();
}
