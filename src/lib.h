#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

std::string version();
int versionMajor();
int versionMinor();
int versionPatch();

using namespace std::string_literals;

struct Node {
    std::string key;
    std::vector<std::unique_ptr<Node>> children;
    bool value = false;
};

bool add(std::unique_ptr<Node> &node, const std::string &value, std::unique_ptr<Node> &parent);
void introspect(const std::unique_ptr<Node> &node, const std::string &prefix = "");
void nicknames(const std::unique_ptr<Node> &node, const std::string &prefix = "");
