#pragma once

#include <QImage>
#include <string>

class Material {
public:
    std::string m_name;
    QImage m_texture;
    double m_friction = 1.0;
    double m_restitution = 1.0;

    Material() : m_texture(QImage())
    {}
    Material(std::string name, double friction, double restitution, const QImage& texture) : m_name(name), m_texture(texture), m_friction(friction), m_restitution(restitution)
    {}
    Material(const Material& other) : m_name(other.m_name), m_texture(other.m_texture), m_friction(other.m_friction), m_restitution(other.m_restitution)
    {}
    ~Material()
    {}
};
