#include "GolfPlayer.hpp"

GolfPlayer::GolfPlayer()
    : m_strokes(0)
{}

void GolfPlayer::player_impulse(QPointF cursor_pos) {
    m_strokes++;
}
