#pragma once

#include "GolfMap.hpp"
#include "Vec2.hpp"
#include <qDebug>
#include <algorithm>

enum CameraMode
{
    CAMERA_MODE_FREE,
    CAMERA_MODE_FOLLOW
};

class GolfCamera
{
public:
    Vec2d m_position;
    bool m_direction[4] = {false};
    CameraMode m_mode = CameraMode::CAMERA_MODE_FOLLOW;

    double m_map_width;
    double m_map_height;
    double m_map_border;

    GolfCamera() = default;
    GolfCamera(const GolfMap& map, double border) :
        m_map_width(map.m_width), m_map_height(map.m_height), m_map_border(border)
    {}

    void switch_mode() {
        switch (m_mode) {
        case CameraMode::CAMERA_MODE_FREE:
            m_mode = CameraMode::CAMERA_MODE_FOLLOW;
            break;
        case CameraMode::CAMERA_MODE_FOLLOW:
            m_mode = CameraMode::CAMERA_MODE_FREE;
            break;
        }
    }
    void move_up() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[0] = true;
        }
    }
    void move_down() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[1] = true;
        }
    }
    void move_left() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[2] = true;
        }
    }
    void move_right() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[3] = true;
        }
    }
    void stop_up() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[0] = false;
        }
    }
    void stop_down() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[1] = false;
        }
    }
    void stop_left() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[2] = false;
        }
    }
    void stop_right() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_direction[3] = false;
        }
    }
    
    void move() {
        Vec2d direction = {0, 0};
        if (m_direction[0]) {
            direction.y -= 1;
        }
        if (m_direction[1]) {
            direction.y += 1;
        }
        if (m_direction[2]) {
            direction.x -= 1;
        }
        if (m_direction[3]) {
            direction.x += 1;
        }

        direction = direction.unit() * 5;
        m_position += direction;
        m_position.x = std::max(m_map_border+20, std::min(m_map_width+m_map_border-20, m_position.x));
        m_position.y = std::max(m_map_border+20, std::min(m_map_height+m_map_border-20, m_position.y));
    }
};
