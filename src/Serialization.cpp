#include "Serialization.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool Serialization::save(const Grid& grid, const std::string& filename) {
    try {
        json j;
        
        j["infinite"] = grid.isInfinite();
        
        auto aliveCells = grid.getAliveCells();
        json cellsArray = json::array();
        
        for (const auto& cell : aliveCells) {
            cellsArray.push_back({{"x", cell.x}, {"y", cell.y}});
        }
        
        j["cells"] = cellsArray;
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << j.dump(4);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Save error: " << e.what() << std::endl;
        return false;
    }
}

bool Serialization::load(Grid& grid, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        json j;
        file >> j;
        
        grid.clear();
        
        if (j.contains("cells") && j["cells"].is_array()) {
            for (const auto& item : j["cells"]) {
                if (item.contains("x") && item.contains("y")) {
                    grid.setCell(item["x"].get<int32_t>(), item["y"].get<int32_t>(), true);
                }
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Load error: " << e.what() << std::endl;
        return false;
    }
}
