#include "MY2048.h"
#include <ctime>
#include <QDebug>

MY2048::MY2048(QObject *parent)
    :QObject(parent)
{
    m_score=0;
}
MY2048::~MY2048()
{

}
void MY2048::start()
{
    initMum();
}
QColor MY2048::color(const int &index)
{
    int num=m_number[index];
    QColor color;
    switch (num) {
        case 0: color=QColor(255,255,255);break;
        case 2: color=QColor(250,220,180);break;
        case 4: color=QColor(230,130,230);break;
        case 8: color=QColor(0,255,130);break;
        case 16: color=QColor(100,100,200);break;
        case 32: color=QColor(255,170,0);break;
        case 64: color=QColor(170,255,50);break;
        case 128: color=QColor(255,100,70);break;
        case 256: color=QColor(154,205,50);break;
        case 512: color=QColor(255,215,0);break;
        case 1024: color=QColor(0,255,255);break;
        case 2048: color=QColor(0,255,0);break;
        case 4096: color=QColor(255,255,0);break;
        case 8192: color=QColor(255,0,0);break;
        default:color=QColor(0,0,0);break;
    }
    return color;
}
QColor MY2048::numColor(const int &index)
{
    if(m_number[index]>8192)
        return QColor(0,0,0);
    else {
        return  QColor(255,255,255);
    }
}
int MY2048::show(const int &index)
{
    return m_number[index];
}
void MY2048::initMum()
{
    m_number.clear();
    m_number=Panel(16,0);
    int firstNum=rand()%16;
    int secondNum=rand()%16;
    while (secondNum==firstNum) {
        secondNum=rand()%16;
    }
    m_number[firstNum]=2;
    m_number[secondNum]=1024;
}
int MY2048::score() const
{
    return m_score;
}
int MY2048::bestScore() const
{
    return m_bestScoore;
}
int MY2048::step() const
{
    return m_step;
}
int MY2048::totalStep() const
{
    return m_totalStep;
}
void MY2048::added(Move_Direcation direcation)
{
    if(direcation==Move_Down)
    {
        m_addFlag=false;

    }
}
