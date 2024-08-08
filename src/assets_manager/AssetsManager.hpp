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

    void addMaterial(QSharedPointer<const Material> material);
    QWeakPointer<const Material> getMaterial(const QString& name) const;
private:
    QMap<std::string, QSharedPointer<const Material>> m_materials;
};
