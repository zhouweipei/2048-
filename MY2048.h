#ifndef MY2048_H
#define MY2048_H
#include <QObject>
#include <QColor>
#include <QJsonObject>
#include <QString>
#define ROWS 4
#define COLUMNS 4
class MY2048 :public QObject
{
    Q_OBJECT
    Q_ENUMS(Move_Direcation)
    Q_PROPERTY(int score READ score WRITE setScore)
    Q_PROPERTY(int bestScore READ bestScore WRITE setBestScore)
    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(int totalStep READ totalStep WRITE setTotalStep)
public:
    MY2048(QObject *parent = nullptr);
    ~MY2048();
    enum Move_Direcation{
        Move_Up=0,
        Move_Down,
        Move_Left,
        Move_Right,
        Move_Invalid
    };
    Q_INVOKABLE void start();
    Q_INVOKABLE void move(Move_Direcation direcation);
    Q_INVOKABLE QColor color(const int &index);
    Q_INVOKABLE QColor numColor(const int &index);
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool load();

     int score() const;
     void setScore(const int score);

     int bestScore() const;
     void setBestScore(const int bestScore);

     int step() const;
     void setStep(const int step);

     int totalStep() const;
     void setTotalStep(const int totalStep);

     void read(QJsonObject &json);

     void write(QJsonObject &json);
signals:
   void backed();
   //void exit();
public slots:
    int show(const int &index);

    void goBack();
private:
    void initMum();
    void added(Move_Direcation direcation);
    void moved(Move_Direcation direcation);
    void freshed(bool freshed);

    int m_score;
    int m_bestScore;
    int m_step;
    int m_totalStep;
    int m_lastScore;
    typedef std::vector<int>Panel;
    typedef std::vector<Panel>State;

    Panel m_number;
    Panel m_index;
    State m_state;
    int m_preIndex;
    int m_nextIndex;

    bool m_addFlag;
    bool m_moveFlag;
};

#endif // MY2048_H
