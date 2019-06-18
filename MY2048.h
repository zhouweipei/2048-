#ifndef MY2048_H
#define MY2048_H
#include <QObject>
#include <QColor>

#define ROWS 4
#define COLUMNS 4
class MY2048 :public QObject
{
    Q_OBJECT
    Q_ENUMS(Move_Direcation)
    Q_PROPERTY(int score READ score)
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
     int score() const;
     int bestScore() const;
     int step() const;
     int totalStep() const;
signals:
   void backd();
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
    int m_bestScoore;
    int m_step;
    int m_totalStep;

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
