#include "AddExerciseDialog.h"
#include <QMessageBox>

AddExerciseDialog::AddExerciseDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Add New Exercise");
    setModal(true);
    resize(300, 200);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    formLayout = new QFormLayout();

    nameEdit = new QLineEdit(this);

    dayComboBox = new QComboBox(this);
    dayComboBox->addItem("Monday");
    dayComboBox->addItem("Tuesday");
    dayComboBox->addItem("Wednesday");
    dayComboBox->addItem("Thursday");
    dayComboBox->addItem("Friday");
    dayComboBox->addItem("Saturday");
    dayComboBox->addItem("Sunday");

    setsSpinBox = new QSpinBox(this);
    repsSpinBox = new QSpinBox(this);

    setsSpinBox->setRange(1, 100);
    setsSpinBox->setValue(3);
    repsSpinBox->setRange(1, 1000);
    repsSpinBox->setValue(10);

    formLayout->addRow("Exercise Name:", nameEdit);
    formLayout->addRow("Day:", dayComboBox);
    formLayout->addRow("Sets:", setsSpinBox);
    formLayout->addRow("Reps:", repsSpinBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &AddExerciseDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
}

QString AddExerciseDialog::getName() const
{
    return nameEdit->text();
}

QString AddExerciseDialog::getDay() const
{
    return dayComboBox->currentText();
}

int AddExerciseDialog::getSets() const
{
    return setsSpinBox->value();
}

int AddExerciseDialog::getReps() const
{
    return repsSpinBox->value();
}

void AddExerciseDialog::accept()
{
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in the exercise name!");
        return;
    }
    QDialog::accept();
}

void AddExerciseDialog::setName(const QString &name)
{
    nameEdit->setText(name);
}

void AddExerciseDialog::setDay(const QString &day)
{
    int index = dayComboBox->findText(day);
    if (index != -1) {
        dayComboBox->setCurrentIndex(index);
    }
}

void AddExerciseDialog::setSets(int sets)
{
    setsSpinBox->setValue(sets);
}

void AddExerciseDialog::setReps(int reps)
{
    repsSpinBox->setValue(reps);
}
