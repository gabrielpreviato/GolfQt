#pragma once

#include <QMap>
#include <QSharedPointer>

#include <string>

#include "Material.hpp"

class AssetsManager
{
public:
    AssetsManager(std::string path="assets/assets.json");
    ~AssetsManager();

    QWeakPointer<const Material> getMaterial(const std::string& name) const;
private:
    QMap<std::string, QSharedPointer<const Material>> m_materials;
    void addMaterial(QSharedPointer<const Material> material);
};

inline AssetsManager G_ASSETS_MANAGER = AssetsManager();

