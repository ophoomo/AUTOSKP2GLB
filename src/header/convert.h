#ifndef CONVERT_H
#define CONVERT_H

#include "SketchUpAPI/sketchup.h"
#include "tiny_gltf.h"

SUModelRef load_sketchup_model(const std::string &filepath);
void convert_skp2glb(const std::string &inputPath, const std::string &outputPath);

#endif //CONVERT_H
