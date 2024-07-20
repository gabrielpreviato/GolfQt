#pragma once
#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>


class GolfForceBar : public QWidget {
Q_OBJECT
public:
    int m_force = 0;

    GolfForceBar(QWidget* parent = nullptr) 
        : QWidget(parent), m_progress_bar(new QProgressBar())
    {
        m_progress_bar= new QProgressBar(this);
        m_progress_bar->setOrientation(Qt::Horizontal);
        m_progress_bar->setMinimum(0);                
        m_progress_bar->setMaximum(100);              // Adjust max as needed

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_progress_bar);
    }

    void setForce(int forceValue) {
        m_progress_bar->setValue(forceValue);
        m_force = forceValue;
    }

private:
    QProgressBar* m_progress_bar;
};
