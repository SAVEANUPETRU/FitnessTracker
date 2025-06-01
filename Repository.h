#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "Exercise.h"
#include <vector>
#include <stack>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
using namespace std;
class Repository{
protected:
    vector<Exercise> v;
public:
    Repository(QString path);
    virtual ~Repository() = default;
    virtual void add_ex(Exercise* ex);
    virtual void remove_ex(int i);
    virtual void modify_ex(int i,QString name,QString day,int sets,int reps);
    virtual std::vector<Exercise> getAll() const;

};

class RepositoryCsv : public Repository{
public:
    RepositoryCsv(QString path);
};

class RepositoryJson : public Repository{
public:
    RepositoryJson(QString path);
};

#endif
