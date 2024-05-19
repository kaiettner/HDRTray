#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Config.h"

namespace config {

static const std::string config_filename = "config.cfg";

std::vector<unsigned int> ReadConfigFile()
{
    std::ifstream file(config_filename);
    std::vector<unsigned int> displayDevices;
    std::string line;

    if (!file) {
        throw std::runtime_error("Unable to open file: " + config_filename);
    }

    while (std::getline(file, line)) {
        if (!line.empty() && line.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            try {
                unsigned int id = std::stoul(line);
                displayDevices.push_back(id);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid input: " + line);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Out of range: " + line);
            }
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error occurred while reading the file: " + config_filename);
    }

    return displayDevices;
}

}