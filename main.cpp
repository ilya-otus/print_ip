#include "lib.h"
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

int main(int argc, char *argv[])
{
    auto logger = spdlog::stdout_logger_mt("console");
    if (argc > 1) {
        bool isVersionRequired = std::string(argv[1]).compare("-v") == 0;
	if (isVersionRequired) {
	    logger->info("version {} was started", version());
	}
    } else {
	std::cout << "build " << versionPatch() << std::endl;
	std::cout << "Hello, World!" << std::endl;
    }
    return 0;
}
