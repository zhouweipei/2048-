#ifndef MY2048_5_H
#define MY2048_5_H
#include <QObject>
#include <QColor>
#include <QJsonObject>
#include <QString>
#include <QMessageBox>
#define ROWS 5
#define COLUMNS 5
class MY2048_5 :public QObject
{
    Q_OBJECT
    Q_ENUMS(Move_Direcation)
    Q_PROPERTY(int score READ score )
    Q_PROPERTY(int bestScore READ bestScore )
    Q_PROPERTY(int step READ step )
    Q_PROPERTY(int totalStep READ totalStep )
public:
    MY2048_5(QObject *parent = nullptr);
    ~MY2048_5();
    enum Move_Direcation{
        Move_Up=0,
        Move_Down,
        Move_Left,
        Move_Right,
    };
    Q_INVOKABLE void start();
    Q_INVOKABLE void move(Move_Direcation direcation);
    Q_INVOKABLE QColor color(const int &index);
    Q_INVOKABLE QColor numColor(const int &index);
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool load();
    Q_INVOKABLE void exit();
    Q_INVOKABLE void reordering();

     int score() const;


     int bestScore() const;


     int step() const;


     int totalStep() const;


     void read(QJsonObject &json);
     void Mydialog();
     bool nextGame();
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
   // int m_lastScore;
    typedef std::vector<int>Panel;
    typedef std::vector<Panel>State;
    typedef std::vector<int> ScoreState;

    Panel m_number;
    Panel m_index;
    State m_state;
    ScoreState m_scoreState;
    int m_preIndex;
    int m_nextIndex;

    bool m_addFlag;
    bool m_addRight;
    bool m_addleft;
    bool m_add_Up;
    bool m_add_Down;
    bool m_moveFlag;
};
#endif // MY2048_5_H
