#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "Service.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addExercise();
    void editExercise();
    void removeExercise();
    void undoAction();
    void redoAction();
    void filterExercises();
    void clearFilter();

private:
    void setupUI();
    void loadExercises();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    QLabel *titleLabel;
    QTableWidget *exerciseTable;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *undoButton;
    QPushButton *redoButton;

    QHBoxLayout *filterLayout;
    QLabel *filterLabel;
    QPushButton *filterButton;
    QPushButton *clearFilterButton;
    QLabel *filterResultLabel;
    QTableWidget *filterResultTable;

    Service *service;
};

#endif // MAINWINDOW_H
