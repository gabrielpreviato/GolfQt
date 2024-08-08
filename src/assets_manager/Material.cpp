#include "Material.hpp"

Material::Material(const std::string &name, double friction, double restitution, const QImage &image)
    : m_name(name)
    , m_friction(friction)
    , m_restitution(restitution)
    , m_texture(image)
{}

Material::Material(nlohmann::basic_json<> json)
    : m_name(json["name"])
    , m_friction(json["friction"])
    , m_restitution(json["restitution"])
    , m_texture(QImage(QString::fromStdString(json["image"])))
{}

Material::~Material() {}

