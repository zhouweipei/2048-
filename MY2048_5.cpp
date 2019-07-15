#include "MY2048_5.h"
#include <ctime>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>
#include <QTimer>
#include <vector>
#include <algorithm>
MY2048_5::MY2048_5(QObject *parent)
    :QObject(parent)
{

    connect(this,SIGNAL(backed()),this,SLOT(goBack()));

}

MY2048_5::~MY2048_5()
{

}

void MY2048_5::start()
{
    initMum();
}

QColor MY2048_5::color(const int &index)//通过number来判断方块颜色
{
    int num=m_number[index];
    QColor color;
    switch (num) {
        case 0: color=QColor(255,0,255);break;
        case 2: color=QColor(250,220,180);break;
        case 4: color=QColor(230,130,230);break;
        case 8: color=QColor(0,255,130);break;
        case 16: color=QColor(252,150,200);break;
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

QColor MY2048_5::numColor(const int &index)//数字颜色
{
    if(m_number[index]>8192)
        return QColor(0,0,0);
    else {
        return  QColor(100,20,255);
    }
}

int MY2048_5::show(const int &index)//返回数字
{
    return m_number[index];
}

void MY2048_5::move(Move_Direcation direcation)//控制方块的移动合并和刷新
{
    //if(!m_step){}


    m_scoreState.push_back(m_score);
    added(direcation);

    moved(direcation);
   // m_lastScore=m_score;
    //std::cout<<m_lastScore<<std::endl;
//    for (int i=0;i<16;i++) {
//        std::cout<<i <<m_number[i]<<std::endl;
//    }

   // std::cout<<m_index.size()<<std::endl;
    freshed(m_addFlag||m_moveFlag);
    if(m_add_Up==false&&m_moveFlag==false&&nextGame()==true&&m_addleft==false&&m_add_Down==false&&m_addRight==false)
        Mydialog();
    if(m_bestScore<m_score)
        m_bestScore=m_score;

}

void MY2048_5::goBack()//撤销功能
{
    if(m_step>0){
        m_number=m_state[m_step-1];
        m_state.pop_back();
        m_score=m_scoreState[m_step-1];
        m_scoreState.pop_back();
        m_step-=1;
     //   m_score=m_lastScore;

    }
}

void MY2048_5::reordering()
{
    //srand((unsigned long)time(NULL));
   random_shuffle(m_number.begin(),m_number.end());
}

void MY2048_5::initMum()//初始化游戏
{
    m_number.clear();
    m_number=Panel(25,0);
    int firstNum=rand()%25;
    int secondNum=rand()%25;
    while (secondNum==firstNum) {
        secondNum=rand()%25;
    }
    m_number[firstNum]=2;
    m_number[secondNum]=2;
    m_step=0;
    m_score=0;
    m_bestScore=0;
    m_totalStep=0;
    //m_lastScore=0;

    m_state.clear();
    m_state.push_back(m_number);
   // std::cout<<"start"+m_index.size();

}

void MY2048_5::Mydialog()//提示游戏结束
{
    QMessageBox msgBox;
    msgBox.setText("Please Click The New Game");
    msgBox.exec();
}

int MY2048_5::score() const
{
    return m_score;
}

int MY2048_5::bestScore() const
{
    return m_bestScore;
}

int MY2048_5::step() const
{
    return m_step;
}

int MY2048_5::totalStep() const
{
    return m_totalStep;
}

void MY2048_5::write(QJsonObject &json)//往JSON文档里写数据
{
    json["score"] =m_score;
    json["bestScore"]=m_bestScore;
    json["step"]=m_step;
    json["totalStep"]=m_totalStep;
    QJsonArray numIndex;
    for ( int i=0;i<m_number.size();i++)
    {
        json["num"] =m_number[i];
        numIndex.append(json["num"]);
    }
    json["num"]=numIndex;

 //   std::cout<<m_index.size();

}

bool MY2048_5::save()//保存游戏
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

bool MY2048_5::nextGame()//判断游戏是否结束
{

    for (int i=0;i<25;i++) {
        if(m_number[i]==0)
            return false;
    }
    return true;

}

void MY2048_5::read(QJsonObject &json)//将json文档里的数据读出来
{

    if(json.contains("score") && json["score"].isDouble())
        m_score=json["score"].toInt();
    if(json.contains("bestScore") && json["bestScore"].isDouble())
        m_bestScore=json["bestScore"].toInt();
    if(json.contains("step") && json["step"].isDouble())
        m_step=json["step"].toInt();
    if(json.contains("totalStep") && json["totalStep"].isDouble())
        m_totalStep=json["totalStep"].toInt();
    if(json.contains("num")&& json["num"].isArray())
    {
        QJsonArray numIndex=json["num"].toArray();
        m_number.clear();
        m_number.reserve(numIndex.size());
        for (int i=0;i<numIndex.size();++i) {
          m_number[i]=numIndex[i].toInt();
        }
    }
}

bool MY2048_5::load()//读取本地保存的游戏数据
{

     // if(load())
      //      remove("save.json");

    QFile saveFile(QStringLiteral("save.json"));

    if(!saveFile.open(QIODevice::ReadOnly))
    {
        qWarning("aa");
        return false;
    }

    QByteArray saveDate=saveFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveDate));
    QJsonObject json(loadDoc.object());
    read(json);
    return true;
}

void MY2048_5::exit()//终止游戏
{
    QApplication* app;
    app->exit(0);
}

void MY2048_5::added(Move_Direcation direcation)//控制方块的相加
{
    if(direcation==Move_Down)
    {
        m_addFlag=false;
        m_add_Down=false;
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
                    m_number[m_nextIndex]=0;
                    m_number[m_preIndex]+=m_number[m_preIndex];
                    m_score+=m_number[m_preIndex];
                    m_preIndex=m_nextIndex-4;
                    m_nextIndex=m_preIndex-4;
                    m_addFlag=true;
                    m_add_Down=true;
                }
            }
        }

    }
    if(direcation==Move_Up)
    {
        m_addFlag=false;
        m_add_Up=false;
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
                    m_number[m_nextIndex]=0;
                    m_number[m_preIndex]+=m_number[m_preIndex];
                    m_score+=m_number[m_preIndex];
                    m_preIndex=m_nextIndex+4;
                    m_nextIndex=m_preIndex+4;
                    m_addFlag=true;
                    m_add_Up=true;
                }
            }
        }

    }
    if(direcation==Move_Right)
    {
        m_addFlag=false;
        m_addRight=false;
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
                    m_number[m_nextIndex]=0;
                    m_number[m_preIndex]+=m_number[m_preIndex];
                    m_score+=m_number[m_preIndex];
                    m_preIndex=m_nextIndex-1;
                    m_nextIndex=m_preIndex-1;
                    m_addFlag=true;
                    m_addRight=true;
                }
            }
        }
    }
    if(direcation==Move_Left)
    {
        m_addFlag=false;
        m_addleft=false;
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
                    m_number[m_nextIndex]=0;
                    m_number[m_preIndex]+=m_number[m_preIndex];
                    m_score+=m_number[m_preIndex];
                    m_preIndex=m_nextIndex+1;
                    m_nextIndex=m_preIndex+1;
                    m_addFlag=true;
                    m_addleft=true;
                }
            }
        }
    }

}
void MY2048_5::moved(Move_Direcation direcation)//控制方向的移动
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
void MY2048_5::freshed(bool freshed)//刷新操作
{
    if(freshed){
        m_step+=1;
        m_totalStep+=1;
//        for (int i=0;i<16;i++) {
//            std::cout<<i <<m_number[i]<<std::endl;
//        }
        m_index.clear();//计数数组清零


//        int nsize=m_number.size();
        for (int i=0;i<25;i++) {
            if(m_number[i]==0){
                m_index.push_back(i);
            }//用数组m_index保存数字为空的数字下标
        }
        int randIndex=rand()%m_index.size();
        m_number[m_index[randIndex]]=2;//将空数字块随机赋值为2
//        std::cout<<m_index[randIndex]<<std::endl;
//        std::cout<<m_number[m_index[randIndex]]<<std::endl;
        m_state.push_back(m_number);//重新保存数字块数组


    }

}
