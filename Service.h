#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"
#include <QStack>
#include <memory>
class Service{
private:
    std::unique_ptr<Repository> repo;
    QStack<Action> s;
    QStack<Action> redoStack;
    int path;

public:
    Service(int i);
    void undo();
    void redo();
    vector<Exercise> filter_combined(QString &day,int reps);
    void add(QString name,QString day,int sets,int reps);
    void remove_ex(int i);
    void modify_ex(int i,QString name,QString day,int sets,int reps);
    vector<Exercise>get_all();
    ~Service();

};
#endif // SERVICE_H
