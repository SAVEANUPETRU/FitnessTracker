#ifndef ADDEXERCISEDIALOG_H
#define ADDEXERCISEDIALOG_H
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class AddExerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExerciseDialog(QWidget *parent = nullptr);

    QString getName() const;
    QString getDay() const;
    int getSets() const;
    int getReps() const;
    void setName(const QString &name);
    void setDay(const QString &day);
    void setSets(int sets);
    void setReps(int reps);

private slots:
    void accept() override;

private:
    QFormLayout *formLayout;
    QLineEdit *nameEdit;
    QComboBox *dayComboBox;
    QSpinBox *setsSpinBox;
    QSpinBox *repsSpinBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
