#include "src/lib.h"
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

int main(int argc, char *argv[])
{
    auto root = std::make_unique<Node>();
    for (std::string line; std::getline(std::cin, line); ) {
        add(root, line, root);
    }
    introspect(root);
    nicknames(root);
    return 0;
}
