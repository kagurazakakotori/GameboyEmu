#include <iostream>
#include "Gameboy.h"

#define VERSION "0.0.2"

static void showVersion()
{
    std::cout << "GameboyEmu version: " << VERSION << std::endl;
}

static void showUsage(char* name)
{
    std::cout << "Usage: " << name << " [-h | --help] [-v | --version] [-o | --open <path_to_rom>]" << std::endl
              << std::endl
              << "Commands:" << std::endl
              << "  -h, --help                this help" << std::endl
              << "  -v, --version             show version and exit" << std::endl
              << "  -o, --open path_to_rom    open gameboy rom and run" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string romPath;

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
            }
            else {
                std::cout << arg << " requires an argument" << std::endl;
                showUsage(argv[0]);
                return EXIT_FAILURE;
            }
        }
        else {
            std::cout << "Unknown option: " << arg << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "[INFO] GameboyEmu ver " << VERSION << std::endl;
    std::cout << "[INFO] 2018 Kagurazaka Kotori <kagurazakakotori@gmail.com>" << std::endl;
    std::cout << termcolor::yellow << "[WARN] This is a unstable version. Use at your own risk" << termcolor::reset << std::endl;

    gb::Gameboy gameboy;

    gameboy.loadRom(romPath);
    gameboy.init();
    gameboy.run();

    return EXIT_SUCCESS;
}