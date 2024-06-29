#pragma once

#include "Vec2.hpp"

enum CameraMode
{
    CAMERA_MODE_FREE,
    CAMERA_MODE_FOLLOW
};

class GolfCamera
{
public:
    Vec2d m_position;
    CameraMode m_mode = CameraMode::CAMERA_MODE_FOLLOW;

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
            m_position.y -= 10;
            m_position.y = std::max(0.0, m_position.y);
        }
    }
    void move_down() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_position.y += 10;
            m_position.y = std::min(1000.0, m_position.y);
        }
    }
    void move_left() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_position.x -= 10;
            m_position.x = std::max(0.0, m_position.x);
        }
    }
    void move_right() {
        if (m_mode == CameraMode::CAMERA_MODE_FREE) {
            m_position.x += 10;
            m_position.x = std::min(1000.0, m_position.x);
        }
    }
};
