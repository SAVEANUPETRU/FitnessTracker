#include "Service.h"
#include <iostream>
Service::Service(int i) {
    if (i == 1) {
        repo = std::make_unique <RepositoryCsv>("C:/Users/petru/CLionProjects/FitnessTracker/ReadCSV");
        path = 1;
    } else {
        repo = std::make_unique<RepositoryJson>("C:/Users/petru/CLionProjects/FitnessTracker/ReadJSON");
        path = 2;
    }
}

void Service::add(QString name, QString day, int sets, int reps) {
    Exercise* ex = new Exercise(name, day, sets, reps);
    repo->add_ex(ex);
    Action action(1, repo->getAll().size() - 1, *ex);
    s.push(action);
    delete ex;
    redoStack.clear();
}

void Service::remove_ex(int i) {
    if (i >= 0 && i < repo->getAll().size()) {
        Exercise removedEx = repo->getAll()[i];
        repo->remove_ex(i);
        Action action(2, i, removedEx);
        s.push(action);
        redoStack.clear();
    }
}

void Service::modify_ex(int i, QString name, QString day, int sets, int reps) {
    if (i >= 0 && i < repo->getAll().size()) {
        Exercise oldEx = repo->getAll()[i];
        repo->modify_ex(i, name, day, sets, reps);
        Action action(3, i, oldEx);
        s.push(action);
        redoStack.clear();
    }
}

void Service::undo() {
    if (!s.empty()) {
        Action lastAction = s.top();
        s.pop();

        if (lastAction.get_option() == 1) {
            int lastIndex = repo->getAll().size() - 1;
            Exercise ex = repo->getAll()[lastIndex];
            repo->remove_ex(lastIndex);
            redoStack.push(Action(1, -1, ex));
        }
        else if (lastAction.get_option() == 2) {
            Exercise* ex = new Exercise(lastAction.get_ex());
            repo->add_ex(ex);
            redoStack.push(Action(2, repo->getAll().size() - 1, *ex));
            delete ex;
        }
        else if (lastAction.get_option() == 3) {
            Exercise current = repo->getAll()[lastAction.get_poz()];
            Exercise oldEx = lastAction.get_ex();
            repo->modify_ex(lastAction.get_poz(), oldEx.getName(), oldEx.getDay(),
                            oldEx.getSets(), oldEx.getReps());
            redoStack.push(Action(3, lastAction.get_poz(), current));
        }
    }
}

void Service::redo() {
    if (!redoStack.empty()) {
        Action action = redoStack.top();
        redoStack.pop();

        if (action.get_option() == 1) {
            Exercise* ex = new Exercise(action.get_ex());
            repo->add_ex(ex);
            s.push(Action(1, repo->getAll().size() - 1, *ex));
            delete ex;
        }
        else if (action.get_option() == 2) {
            int removeIndex = repo->getAll().size() - 1;
            Exercise ex = repo->getAll()[removeIndex];
            repo->remove_ex(removeIndex);
            s.push(Action(2, removeIndex, ex));
        }
        else if (action.get_option() == 3) {
            Exercise oldEx = repo->getAll()[action.get_poz()];
            Exercise newEx = action.get_ex();
            repo->modify_ex(action.get_poz(), newEx.getName(), newEx.getDay(),
                            newEx.getSets(), newEx.getReps());
            s.push(Action(3, action.get_poz(), oldEx));
        }
    }
}
vector<Exercise> Service::filter_combined(QString &day,int reps) {
    vector<Exercise> filtered;
    vector<Exercise> all = repo->getAll();
    for (Exercise& ex : all) {
        bool dayMatches = (day.isEmpty() || ex.getDay() == day);
        bool repsMatches = (reps == 0 || ex.getReps() * ex.getSets() >= reps);
        if(dayMatches == true &&  repsMatches == true)
            filtered.push_back(ex);
    }
    return filtered;
}

vector<Exercise> Service::get_all(){
    return repo->getAll();
}
Service::~Service(){
    if (path == 1)
        repo->save("C:/Users/petru/CLionProjects/FitnessTracker/ReadCSV");
    else
        repo->save("C:/Users/petru/CLionProjects/FitnessTracker/ReadJSON");
}
