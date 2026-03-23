// chess variant cell-devs simulation driver
// reads a json config and runs the simulation with csv logging
// usage: ./chess_variant <config.json> [sim_time]

#include "nlohmann/json.hpp"
#include <cadmium/modeling/celldevs/grid/coupled.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "include/chessVariantCell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

std::shared_ptr<GridCell<ChessVariantState, double>> addGridCell(
    const coordinates& cellId,
    const std::shared_ptr<const GridCellConfig<ChessVariantState, double>>& cellConfig) {
    auto cellModel = cellConfig->cellModel;
    if (cellModel == "chessVariant") {
        return std::make_shared<ChessVariantCell>(cellId, cellConfig);
    } else {
        throw std::bad_typeid();
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Program used with wrong parameters. The program must be invoked as follows:" << std::endl;
        std::cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 500)]" << std::endl;
        return -1;
    }

    std::string configFilePath = argv[1];
    double simTime = (argc > 2) ? std::stod(argv[2]) : 500;

    // output goes to logs/<config_name>_grid_log.csv
    std::filesystem::create_directories("logs");
    std::string configName = std::filesystem::path(configFilePath).stem().string();
    // strip _config suffix if present so log name matches viewer convention
    std::string baseName = configName;
    if (baseName.size() > 7 && baseName.substr(baseName.size() - 7) == "_config") {
        baseName = baseName.substr(0, baseName.size() - 7);
    }
    std::string logFile = "logs/" + baseName + "_grid_log.csv";

    auto model = std::make_shared<GridCellDEVSCoupled<ChessVariantState, double>>(
        "chessVariant", addGridCell, configFilePath);
    model->buildModel();

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(logFile, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(simTime);
    rootCoordinator.stop();

    std::cout << "Simulation complete. Output: " << logFile << std::endl;
}
