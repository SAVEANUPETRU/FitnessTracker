#ifndef EXERCISE_H
#define EXERCISE_H
#include <QString>
class Exercise{
private:
    QString name;
    QString day;
    int sets;
    int reps;
public:
    Exercise()=default;
    Exercise(QString name, QString day, int sets, int reps);
    int getReps();
    int getSets();
    QString getName();
    QString getDay();
    void setReps(int reps);
    void setSets(int sets);
    void setName(QString name);
    void setDay(QString day);
};

class Action{
private:
    int option;
    int pozition;
    Exercise s;
public:
    Action(int op,int poz, Exercise c);
    int get_poz();
    int get_option();
    Exercise get_ex();
};
#endif // EXERCISE_H

