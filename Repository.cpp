#include "Repository.h"
#include <QDebug>
Repository::Repository(QString path) {}
void Repository::add_ex(Exercise *ex){
    v.push_back(*ex);
}
void Repository::remove_ex(int i){
    v.erase(v.begin() + i);
}
void Repository::modify_ex(int i, QString name, QString day, int sets, int reps) {
    if (i < 0 || i >= v.size()) {
        qDebug() << "Index invalid la modify_ex!";
        return;
    }
    v[i].setName(name);
    v[i].setDay(day);
    v[i].setSets(sets);
    v[i].setReps(reps);
}

vector<Exercise> Repository::getAll() const {
    return v;
}

RepositoryCsv::RepositoryCsv(QString path) : Repository(path) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts;
            if (line.contains(";")) {
                parts = line.split(";");
            } else {
                parts = line.split(",");
            }
            if (parts.size() == 4) {
                QString name = parts[0];
                QString day = parts[1];
                int sets = parts[2].toInt();
                int reps = parts[3].toInt();
                v.push_back(Exercise(name, day, sets, reps));
            }
        }
        file.close();
    }
}

RepositoryJson::RepositoryJson(QString path) : Repository(path) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        for (int i = 0; i < array.size(); ++i) {
            QJsonValue value = array[i];
            QJsonObject obj = value.toObject();
            QString name = obj["name"].toString();
            QString day = obj["day"].toString();
            int sets = obj["sets"].toInt();
            int reps = obj["reps"].toInt();
            v.push_back(Exercise(name, day, sets, reps));
        }
        file.close();
    }
}
