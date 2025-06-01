#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"
#include <QStack>
class Service{
private:
    Repository* repo;
    QStack<Action> s;
    QStack<Action> redoStack;

public:
    Service(int i);
    void undo();
    void redo();
    vector<Exercise> filter_combined(QString &day,int reps);
    void add(QString name,QString day,int sets,int reps);
    void remove_ex(int i);
    void modify_ex(int i,QString name,QString day,int sets,int reps);
    ~Service() { delete repo; }
    vector<Exercise>get_all();

};
#endif // SERVICE_H
