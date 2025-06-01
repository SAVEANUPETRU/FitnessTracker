#include "Exercise.h"
Exercise :: Exercise(QString name, QString day, int sets, int reps){
    this->name = name;
    this->day = day;
    this->sets = sets;
    this->reps = reps;
}

QString Exercise :: getName(){
    return this->name;
}
QString Exercise :: getDay(){
    return this->day;
}
int Exercise :: getSets(){
    return this->sets;
}
int Exercise:: getReps(){
    return this->reps;
}
void Exercise :: setName(QString name){
    this->name=name;
}
void Exercise :: setDay(QString day){
    this->day=day;
}
void Exercise :: setReps(int reps){
    this->reps=reps;
}
void Exercise :: setSets(int sets){
    this->sets=sets;
}

int Action::get_option(){
    return this->option;
}
int Action::get_poz(){
    return this->pozition;
}
Exercise Action::get_ex(){
    return this->s;
}
Action::Action(int op, int poz, Exercise c) {
    this->option = op;
    this->pozition = poz;
    this->s = c;
}
