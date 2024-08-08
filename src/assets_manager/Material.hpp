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

    const std::string &name() const;
    double friction() const;
    double restitution() const;
    const QImage &image() const;

private:
    std::string m_name;
    double m_friction;
    double m_restitution;
    QImage m_image;
};
