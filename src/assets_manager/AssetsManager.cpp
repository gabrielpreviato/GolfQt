#include "AssetsManager.hpp"

#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

AssetsManager::AssetsManager(std::string path) {
    std::ifstream file{path};
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

    json data = json::parse(file);
    for (auto& material : data["materials"]) {
        addMaterial(QSharedPointer<const Material>(new Material(material)));
    }
}

AssetsManager::~AssetsManager() {}

void AssetsManager::addMaterial(QSharedPointer<const Material> material) {
    m_materials[material->name()] = material;
}

