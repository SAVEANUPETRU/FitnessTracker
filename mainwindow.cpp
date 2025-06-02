#include "MainWindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include "AddExerciseDialog.h"
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QComboBox>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    service = new Service(2); // 1 pentru CSV
    setupUI();
    loadExercises();
}

MainWindow::~MainWindow()
{
    delete service;
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("Fitness Tracker", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    exerciseTable = new QTableWidget(this);
    exerciseTable->setColumnCount(4);
    QStringList headers = {"Exercise", "Day", "Sets", "Reps"};
    exerciseTable->setHorizontalHeaderLabels(headers);
    exerciseTable->horizontalHeader()->setStretchLastSection(true);

    buttonLayout = new QHBoxLayout();

    addButton = new QPushButton("Add Exercise", this);
    editButton = new QPushButton("Edit Exercise", this);
    removeButton = new QPushButton("Remove Exercise", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);

    filterLayout = new QHBoxLayout();
    filterLabel = new QLabel("Filters:", this);
    filterButton = new QPushButton("Filter Exercises", this);
    clearFilterButton = new QPushButton("Clear Filter", this);

    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterButton);
    filterLayout->addWidget(clearFilterButton);
    filterLayout->addStretch();

    filterResultLabel = new QLabel("", this);
    filterResultLabel->setStyleSheet("font-weight: bold; color: blue;");
    filterResultLabel->hide();

    filterResultTable = new QTableWidget(this);
    filterResultTable->setColumnCount(4);
    filterResultTable->setHorizontalHeaderLabels(headers);
    filterResultTable->horizontalHeader()->setStretchLastSection(true);
    filterResultTable->hide();

    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterExercises);
    connect(clearFilterButton, &QPushButton::clicked, this, &MainWindow::clearFilter);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(exerciseTable);
    mainLayout->addLayout(buttonLayout);

    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(filterResultLabel);
    mainLayout->addWidget(filterResultTable);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addExercise);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editExercise);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeExercise);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::undoAction);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::redoAction);

    resize(800, 800);
    setWindowTitle("Fitness Tracker");
}

void MainWindow::loadExercises()
{
    auto exercises = service->get_all();
    exerciseTable->setRowCount(exercises.size());

    for (int i = 0; i < exercises.size(); ++i) {
        exerciseTable->setItem(i, 0, new QTableWidgetItem(exercises[i].getName()));
        exerciseTable->setItem(i, 1, new QTableWidgetItem(exercises[i].getDay()));
        exerciseTable->setItem(i, 2, new QTableWidgetItem(QString::number(exercises[i].getSets())));
        exerciseTable->setItem(i, 3, new QTableWidgetItem(QString::number(exercises[i].getReps())));
    }
}

void MainWindow::addExercise()
{
    AddExerciseDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        service->add(dialog.getName(), dialog.getDay(),
                     dialog.getSets(), dialog.getReps());
        loadExercises();
    }
}

void MainWindow::editExercise()
{
    int currentRow = exerciseTable->currentRow();
    if (currentRow >= 0) {
        auto exercises = service->get_all();
        if (currentRow < exercises.size()) {
            AddExerciseDialog dialog(this);
            dialog.setWindowTitle("Edit Exercise");

            dialog.setName(exercises[currentRow].getName());
            dialog.setDay(exercises[currentRow].getDay());
            dialog.setSets(exercises[currentRow].getSets());
            dialog.setReps(exercises[currentRow].getReps());

            if (dialog.exec() == QDialog::Accepted) {
                service->modify_ex(currentRow, dialog.getName(), dialog.getDay(),
                                   dialog.getSets(), dialog.getReps());
                loadExercises();
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select an exercise to edit!");
    }
}

void MainWindow::removeExercise()
{
    int currentRow = exerciseTable->currentRow();
    if (currentRow >= 0) {
        service->remove_ex(currentRow);
        loadExercises();
    } else {
        QMessageBox::warning(this, "Warning", "Please select an exercise to remove!");
    }
}

void MainWindow::undoAction()
{
    service->undo();
    loadExercises();
}

void MainWindow::redoAction()
{
    service->redo();
    loadExercises();
}

void MainWindow::filterExercises()
{
    QDialog filterDialog(this);
    filterDialog.setWindowTitle("Filter Exercises");
    filterDialog.setModal(true);

    QFormLayout *formLayout = new QFormLayout(&filterDialog);

    QComboBox *dayComboBox = new QComboBox(&filterDialog);
    dayComboBox->addItem("Any Day", "");
    dayComboBox->addItem("Monday","Monday");
    dayComboBox->addItem("Tuesday","Tuesday");
    dayComboBox->addItem("Wednesday","Wednesday");
    dayComboBox->addItem("Thursday","Thursday");
    dayComboBox->addItem("Friday","Friday");
    dayComboBox->addItem("Saturday","Saturday");
    dayComboBox->addItem("Sunday","Sunday");
    formLayout->addRow("Day:", dayComboBox);

    QSpinBox *minRepsSpinBox = new QSpinBox(&filterDialog);
    minRepsSpinBox->setRange(0, 10000);
    minRepsSpinBox->setValue(0);
    minRepsSpinBox->setSpecialValueText("No minimum");
    formLayout->addRow("Minimum total reps:", minRepsSpinBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &filterDialog);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &filterDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &filterDialog, &QDialog::reject);

    if (filterDialog.exec() == QDialog::Accepted) {
        QString day = dayComboBox->currentData().toString();
        int minReps = minRepsSpinBox->value();

        QString filterDay = day;
        int filterReps = minReps;
        auto filtered = service->filter_combined(filterDay, filterReps);

        QString resultMessage;
        if (filtered.empty()) {
            resultMessage = "No exercises found";
            if (!filterDay.isEmpty() && filterReps > 0) {
                resultMessage += " for " + dayComboBox->currentText() + " with total reps >= " + QString::number(filterReps);
            } else if (!filterDay.isEmpty()) {
                resultMessage += " for " + dayComboBox->currentText();
            } else if (filterReps > 0) {
                resultMessage += " with total reps >= " + QString::number(filterReps);
            }
        } else {
            resultMessage = "Found " + QString::number(filtered.size()) + " exercise(s)";
            if (!filterDay.isEmpty() && filterReps > 0) {
                resultMessage += " for " + dayComboBox->currentText() + " with total reps >= " + QString::number(filterReps);
            } else if (!filterDay.isEmpty()) {
                resultMessage += " for " + dayComboBox->currentText();
            } else if (filterReps > 0) {
                resultMessage += " with total reps >= " + QString::number(filterReps);
            }
        }

        filterResultLabel->setText(resultMessage);
        filterResultTable->setRowCount(filtered.size());
        for (int i = 0; i < filtered.size(); ++i) {
            filterResultTable->setItem(i, 0, new QTableWidgetItem(filtered[i].getName()));
            filterResultTable->setItem(i, 1, new QTableWidgetItem(filtered[i].getDay()));
            filterResultTable->setItem(i, 2, new QTableWidgetItem(QString::number(filtered[i].getSets())));
            filterResultTable->setItem(i, 3, new QTableWidgetItem(QString::number(filtered[i].getReps())));
        }

        filterResultLabel->show();
        filterResultTable->show();
    }
}

void MainWindow::clearFilter()
{
    filterResultLabel->hide();
    filterResultTable->hide();
}
