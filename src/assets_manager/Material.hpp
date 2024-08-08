#pragma once

#include <string>

#include "json.hpp"

#include <QImage>

class Material
{
public:
    Material(const std::string &name, double friction, double restitution, const QImage &image);
    Material(nlohmann::basic_json<> json);
    ~Material();

    const std::string &name() const { return m_name; }
    double friction() const { return m_friction; }
    double restitution() const { return m_restitution; }
    const QImage &texture() const { return m_texture; }

private:
    std::string m_name;
    double m_friction;
    double m_restitution;
    QImage m_texture;
};
