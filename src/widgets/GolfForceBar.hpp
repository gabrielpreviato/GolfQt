#pragma once
#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>


class GolfForceBar : public QWidget {
    Q_OBJECT
public:
    int m_force = 0;

    GolfForceBar(QWidget* parent = nullptr);

    void setForce(int forceValue);

private:
    QProgressBar* m_progress_bar;
};
