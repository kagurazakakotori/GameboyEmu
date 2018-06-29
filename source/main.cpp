#include <iostream>
#include "Gameboy.h"
#include "version.h"

static void showVersion()
{
    std::cout << "GameboyEmu version: " << VERSION_MAJOR << "." << VERSION_MINOR<< "." << VERSION_BUILD << std::endl;
}

static void showUsage(char* name)
{
    std::cout << "Usage: " << name << " [-h | --help] [-v | --version] [-o | --open <path_to_rom>] (-z | --zoom <level>)" << std::endl
              << std::endl
              << "Commands:" << std::endl
              << "  -h, --help                  this help" << std::endl
              << "  -v, --version               show version and exit" << std::endl
              << "  -o, --open <path_to_rom>    open gameboy rom and run" << std::endl
              << "Options:" << std::endl
              << "  -z, --zoom <level>          set emulator window zoom level" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string romPath;
    float       zoomLevel = 1;
    bool        open = false;

    if (argc < 2) {
        showVersion();
        showUsage(argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            showUsage(argv[0]);
            return EXIT_SUCCESS;
        }
        else if ((arg == "-v") || (arg == "--version")) {
            showVersion();
            return EXIT_SUCCESS;
        }
        else if ((arg == "-o") || (arg == "--open")) {
            if (i + 1 < argc) {
                i++;  // get next argument
                romPath = argv[i];
                open    = true;
            }
            else {
                std::cout << arg << " requires an argument" << std::endl;
                showUsage(argv[0]);
                return EXIT_FAILURE;
            }
        }
        else if ((arg == "-z") || (arg == "--zoom")) {
            if (open == true) {
                if (i + 1 < argc) {
                    i++;  // get next argument
                    zoomLevel = atof(argv[i]);
                    if (zoomLevel < 1) {
                        zoomLevel = 1;
                        std::cout << termcolor::yellow << "[WARN] Invalid zoom option, using 1x instead" << termcolor::reset << std::endl;
                    }
                }
            }
            else {
                std::cout << arg << " must be after -o or --open command" << std::endl;
                showUsage(argv[0]);
                return EXIT_FAILURE;
            }
        }
        else {
            std::cout << "Unknown option: " << arg << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "[INFO] GameboyEmu ver " << VERSION_MAJOR << "." << VERSION_MINOR<< "." << VERSION_BUILD << std::endl;
    std::cout << "[INFO] 2018 Kagurazaka Kotori <kagurazakakotori@gmail.com>" << std::endl;
    std::cout << termcolor::yellow << "[WARN] This is a unstable version. Use at your own risk" << termcolor::reset << std::endl;
    std::cout << "[INFO] Emulator window zoom level: " << zoomLevel << "x" << std::endl;

    gb::Gameboy gameboy;

    gameboy.loadRom(romPath);
    gameboy.init(zoomLevel);
    gameboy.run();

    return EXIT_SUCCESS;
}