#include <iostream>
#include <format>
#include <filesystem>
#include <cstdlib>
#include <string>
#include "../src/face_detection.cpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string photo_dir_path = argv[1];
    std::string save_dir_path = argv[2]; 

    for (const auto& entry : fs::directory_iterator(photo_dir_path)) {
        std::string filename = entry.path().filename();
    }
}