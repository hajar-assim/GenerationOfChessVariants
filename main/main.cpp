#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <cadmium/celldevs/core/coupled.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include "include/chessVariantCell.hpp"
#include "include/chessVariantState.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <config.json> [simulation_time]" << std::endl;
        std::cerr << "  config.json: Path to the scenario configuration file" << std::endl;
        std::cerr << "  simulation_time: Optional simulation duration (default: 60)" << std::endl;
        return 1;
    }

    std::string configPath = argv[1];
    double simTime = (argc == 3) ? std::stod(argv[2]) : 60.0;

    // Extract scenario name from config path for output file
    std::filesystem::path configFile(configPath);
    std::string configName = configFile.stem().string();

    std::cout << "=== Chess Variant Cell-DEVS Simulation ===" << std::endl;
    std::cout << "Configuration: " << configPath << std::endl;
    std::cout << "Simulation time: " << simTime << " generations" << std::endl;

    // Create logs directory if it doesn't exist
    std::filesystem::create_directories("logs");
    std::string logFile = "logs/" + configName + "_output.csv";

    try {
        // Load JSON configuration
        std::ifstream configStream(configPath);
        if (!configStream.is_open()) {
            std::cerr << "Error: Could not open configuration file: " << configPath << std::endl;
            return 1;
        }
        nlohmann::json config = nlohmann::json::parse(configStream);
        configStream.close();

        // Create Cell-DEVS coupled model from JSON config
        auto model = std::make_shared<CellDEVSCoupled<ChessVariantState, ChessVariantCell>>("chessVariant", config);

        // Create root coordinator with CSV logger
        auto rootCoordinator = RootCoordinator(model);

        // Set up CSV logging
        auto logger = std::make_shared<CSVLogger>(logFile, ";");
        rootCoordinator.setLogger(logger);

        // Run simulation
        std::cout << "Starting simulation..." << std::endl;
        rootCoordinator.start();
        rootCoordinator.simulate(simTime);
        rootCoordinator.stop();

        std::cout << "Simulation completed successfully." << std::endl;
        std::cout << "Output written to: " << logFile << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during simulation: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
