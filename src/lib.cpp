#include "lib.h"
#include "../version.h"

std::string version() {
    std::string version = std::to_string(versionMajor()) + "." +
        std::to_string(versionMinor()) + "." +
        std::to_string(versionPatch());
    return version;
}

int versionMajor() {
    return PROJECT_VERSION_MAJOR;
}
int versionMinor() {
    return PROJECT_VERSION_MINOR;
}
int versionPatch() {
    return PROJECT_VERSION_PATCH;
}

bool add(std::unique_ptr<Node> &node, const std::string &value, std::unique_ptr<Node> &parent) {
    if (node->key.empty() && node->children.empty()) {
        node->key = value;
        node->value = true;
        return true;
    }
    if (node->key == value) {
        node->value = true;
        return true;
    }
    auto commonLength = std::max(value.size(), node->key.size());
    auto valueSubstr = value.substr(0, commonLength);
    auto keySubstr = node->key.substr(0, commonLength);
    while(commonLength != 0) {
        if (valueSubstr == keySubstr) {
            break;
        }
        --commonLength;
        valueSubstr = value.substr(0, commonLength);
        keySubstr = node->key.substr(0, commonLength);
    }
    if (valueSubstr == value) {
        auto diff = node->key.substr(value.size());
        auto newNode = std::make_unique<Node>();
        newNode->key = diff;
        newNode->children.clear();
        std::move(node->children.begin(), node->children.end(), std::back_inserter(newNode->children));
        newNode->value = node->value;
        node->key = value;
        node->children.clear();
        node->children.emplace_back(std::move(newNode));
        node->value = true;
        return true;
    } else if (keySubstr == node->key) {
        auto diff = value.substr(node->key.size());
        for (auto &child: node->children) {
            if (add(child, diff, node)) {
                return true;
            }
        }
        auto newNode = std::make_unique<Node>();
        newNode->key = diff;
        newNode->value = true;
        node->children.emplace_back(std::move(newNode));
        return true;
    }
    if (commonLength != 0 || parent == node) {
        auto diffK = node->key.substr(commonLength);
        auto newNodeK = std::make_unique<Node>();
        newNodeK->key = diffK;
        newNodeK->children.clear();
        std::move(node->children.begin(), node->children.end(), std::back_inserter(newNodeK->children));
        newNodeK->value = node->value;

        auto diffV = value.substr(commonLength);
        auto newNodeV = std::make_unique<Node>();
        newNodeV->key = diffV;
        newNodeV->children.clear();
        newNodeV->value = true;

        node->key = keySubstr;
        node->children.clear();
        node->children.emplace_back(std::move(newNodeK));
        node->children.emplace_back(std::move(newNodeV));
        node->value = false;
        return true;
    }
    return false;
}

void introspect(const std::unique_ptr<Node> &node, const std::string &prefix) {
    std::cout << "\"" << node->key << "\"";
    if (node->value) {
        std::cout << "$";
    }
    std::cout << std::endl;
    auto newPrefix = prefix;
    if (node->children.size() > 1) {
        newPrefix += "| ";
    } else {
        newPrefix += "  ";
    }
    for (const auto &child: node->children) {
        std::cout << prefix << "+ ";
        introspect(child, newPrefix);
    }
}

void nicknames(const std::unique_ptr<Node> &node, const std::string &prefix) {
    if (node->value) {
        if(node->children.empty()) {
            std::cout << prefix << node->key << " " << prefix << node->key[0];
        } else {
            std::cout << prefix << node->key << " " << prefix << node->key;
        }
        std::cout << std::endl;
    }
    auto newPrefix = prefix + node->key;
    for (const auto &child: node->children) {
        nicknames(child, newPrefix);
    }
}
