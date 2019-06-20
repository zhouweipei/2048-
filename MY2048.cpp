#include "MY2048.h"
#include <ctime>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

MY2048::MY2048(QObject *parent)
    :QObject(parent)
{
    load();
    connect(this,SIGNAL(backed()),this,SLOT(goBack()));

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
        case 0: color=QColor(255,0,255);break;
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
void MY2048::move(Move_Direcation direcation)
{
    added(direcation);
    moved(direcation);
    freshed(m_addFlag||m_moveFlag);
    if(m_bestScore<m_score)
        m_bestScore=m_score;
}
void MY2048::goBack()
{
    if(m_step>0){
        m_number=m_state[m_step-1];
        m_state.pop_back();
        m_step-=1;

    }
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
    m_number[secondNum]=2;
    m_step=0;
    m_score=0;
    m_bestScore=0;
    m_totalStep=0;

    m_state.clear();
    m_state.push_back(m_number);

}

int MY2048::score() const
{
    return m_score;
}
void MY2048::setScore(const int score)
{
    m_step=score;
}

int MY2048::bestScore() const
{
    return m_bestScore;
}
void MY2048::setBestScore(const int bestScore)
{
    m_bestScore=bestScore;
}

int MY2048::step() const
{
    return m_step;
}
void MY2048::setStep(const int step)
{
    m_step=step;
}

int MY2048::totalStep() const
{
    return m_totalStep;
}
void MY2048::setTotalStep(const int totalStep)
{
    m_totalStep=totalStep;
}

void MY2048::write(QJsonObject &json)
{
    json["score"] =m_score;
    json["bestScore"]=m_bestScore;
    json["step"]=m_step;
    json["totalStep"]=m_totalStep;
}
bool MY2048::save()
{
    QFile saveFile(QStringLiteral("save.json"));
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file");
        return  false;
    }
    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    return true;
}

void MY2048::read(QJsonObject &json)
{
    if(json.contains("score") && json["score"].isDouble())
        m_score=json["score"].toInt();
    if(json.contains("bestScore") && json["bestScore"].isDouble())
        m_bestScore=json["bestScore"].toInt();
    if(json.contains("step") && json["step"].isDouble())
        m_step=json["step"].toInt();
    if(json.contains("totalStep") && json["totalStep"].isDouble())
        m_totalStep=json["totalStep"].toInt();
}

bool MY2048::load()
{
    QFile loadFile(QStringLiteral("save.json"));
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open save file.");
        return false;
    }

    QByteArray saveDate=loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveDate));
    QJsonObject json(loadDoc.object());
    read(json);
    return true;
}

void MY2048::added(Move_Direcation direcation)
{
    if(direcation==Move_Down)
    {
        m_addFlag=false;
        for (int i=0;i<COLUMNS;i++) {
            m_preIndex=i;
            m_nextIndex=m_preIndex+4;
            while(m_nextIndex<=i+12){
                if(m_number[m_preIndex]==0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+4;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex+=4;
                    continue;
                }
                if(m_number[m_preIndex]!=m_number[m_nextIndex])
                {
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+4;
                }else {
                    m_number[m_preIndex]=0;
                    m_number[m_nextIndex]+=m_number[m_nextIndex];
                    m_score+=m_number[m_nextIndex];
                    m_preIndex=m_nextIndex+4;
                    m_nextIndex=m_preIndex+4;
                    m_addFlag=true;
                }
            }
        }

    }
    if(direcation==Move_Up)
    {
        m_addFlag=false;
        for (int i=0;i<COLUMNS;i++) {
            m_preIndex=i+12;
            m_nextIndex=m_preIndex-4;
            while(m_nextIndex>=i){
                if(m_number[m_preIndex]==0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-4;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex-=4;
                    continue;
                }
                if(m_number[m_preIndex]!=m_number[m_nextIndex])
                {
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-4;
                }else {
                    m_number[m_preIndex]=0;
                    m_number[m_nextIndex]+=m_number[m_nextIndex];
                    m_score+=m_number[m_nextIndex];
                    m_preIndex=m_nextIndex-4;
                    m_nextIndex=m_preIndex-4;
                    m_addFlag=true;
                }
            }
        }

    }
    if(direcation==Move_Right)
    {
        m_addFlag=false;
        for (int i=0;i<ROWS;i++) {
            m_preIndex=i*4;
            m_nextIndex=m_preIndex+1;
            while(m_nextIndex<=i*4+3){
                if(m_number[m_preIndex]==0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+1;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex+=1;
                    continue;
                }
                if(m_number[m_preIndex]!=m_number[m_nextIndex])
                {
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+1;
                }else {
                    m_number[m_preIndex]=0;
                    m_number[m_nextIndex]+=m_number[m_nextIndex];
                    m_score+=m_number[m_nextIndex];
                    m_preIndex=m_nextIndex+1;
                    m_nextIndex=m_preIndex+1;
                    m_addFlag=true;
                }
            }
        }
    }
    if(direcation==Move_Left)
    {
        m_addFlag=false;
        for (int i=0;i<ROWS;i++) {
            m_preIndex=i*4+3;
            m_nextIndex=m_preIndex-1;
            while(m_nextIndex>=i*4){
                if(m_number[m_preIndex]==0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-1;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex-=1;
                    continue;
                }
                if(m_number[m_preIndex]!=m_number[m_nextIndex])
                {
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-1;
                }else {
                    m_number[m_preIndex]=0;
                    m_number[m_nextIndex]+=m_number[m_nextIndex];
                    m_score+=m_number[m_nextIndex];
                    m_preIndex=m_nextIndex-1;
                    m_nextIndex=m_preIndex-1;
                    m_addFlag=true;
                }
            }
        }
    }

}
void MY2048::moved(Move_Direcation direcation)
{
    if(direcation==Move_Down)
    {
        m_moveFlag=false;
        for (int i=0;i<COLUMNS;i++) {
            m_preIndex=i+12;
            m_nextIndex=m_preIndex-4;
            while(m_nextIndex>=i){
                if(m_number[m_preIndex]!=0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-4;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex-=4;
                    continue;
                }else {
                    m_number[m_preIndex]=m_number[m_nextIndex];
                    m_number[m_nextIndex]=0;
                    m_preIndex=m_preIndex-4;
                    m_nextIndex=m_nextIndex-4;
                    m_moveFlag=true;
                }
            }
        }
    }
    if(direcation==Move_Up)
    {
        m_moveFlag=false;
        for (int i=0;i<COLUMNS;i++) {
            m_preIndex=i;
            m_nextIndex=m_preIndex+4;
            while(m_nextIndex<=i+12){
                if(m_number[m_preIndex]!=0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+4;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex+=4;
                    continue;
                }else {
                    m_number[m_preIndex]=m_number[m_nextIndex];
                    m_number[m_nextIndex]=0;
                    m_preIndex=m_preIndex+4;
                    m_nextIndex=m_nextIndex+4;
                    m_moveFlag=true;
                }
            }
        }
    }
    if(direcation==Move_Right)
    {
        m_moveFlag=false;
        for (int i=0;i<ROWS;i++) {
            m_preIndex=i*4+3;
            m_nextIndex=m_preIndex-1;
            while(m_nextIndex>=i*4){
                if(m_number[m_preIndex]!=0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex-1;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex-=1;
                    continue;
                }else {
                    m_number[m_preIndex]=m_number[m_nextIndex];
                    m_number[m_nextIndex]=0;
                    m_preIndex=m_preIndex-1;
                    m_nextIndex=m_nextIndex-1;
                    m_moveFlag=true;
                }
            }
        }
    }
    if(direcation==Move_Left)
    {
        m_moveFlag=false;
        for (int i=0;i<ROWS;i++) {
            m_preIndex=i*4;
            m_nextIndex=m_preIndex+1;
            while(m_nextIndex<=i*4+3){
                if(m_number[m_preIndex]!=0){
                    m_preIndex=m_nextIndex;
                    m_nextIndex=m_preIndex+1;
                    continue;
                }
                if(m_number[m_nextIndex]==0)
                {
                    m_nextIndex+=1;
                    continue;
                }else {
                    m_number[m_preIndex]=m_number[m_nextIndex];
                    m_number[m_nextIndex]=0;
                    m_preIndex=m_preIndex+1;
                    m_nextIndex=m_nextIndex+1;
                    m_moveFlag=true;
                }
            }
        }
    }

}
void MY2048::freshed(bool freshed)
{
    if(freshed){
        m_step+=1;
        m_totalStep+=1;

        m_index.clear();
        for (size_t i=0;i<m_number.size();i++) {
            if(!m_number[i])
                m_index.push_back(i);
        }

        int randIndex=rand()%m_index.size();
        m_number[m_index[randIndex]]=2;
        m_state.push_back(m_number);

    }
}
