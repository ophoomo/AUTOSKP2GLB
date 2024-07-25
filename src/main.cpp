#include <iostream>
#include "spdlog/spdlog.h"
#include "header/convert.h"

int main() {
    spdlog::info("start program");

    std::string input_filepath  = "./input.skp";
    std::string output_filepath  = "./output.glb";

    convert_skp2glb(input_filepath, output_filepath);

    spdlog::info("end program");
    system("pause");
    return 0;
}