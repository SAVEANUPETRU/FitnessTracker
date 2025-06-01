#include "TestRepo.h"
#include <cassert>
void test_repo(){
    RepositoryJson repo("C:/Users/petru/CLionProjects/FitnessTracker/ReadJSON");

    assert(repo.getAll().size() == 10);
    assert(repo.getAll()[0].getName() == "Push-ups");
    assert(repo.getAll()[0].getDay() == "Monday");
    assert(repo.getAll()[0].getSets() == 3);
    assert(repo.getAll()[0].getReps() == 15);

    Exercise* newEx = new Exercise("Bicep Curls", "Saturday", 3, 12);
    repo.add_ex(newEx);
    assert(repo.getAll().size() == 11);
    assert(repo.getAll()[10].getName() == "Bicep Curls");

    repo.modify_ex(0, "Modified Push-ups", "Sunday", 5, 20);
    assert(repo.getAll()[0].getName() == "Modified Push-ups");
    assert(repo.getAll()[0].getDay() == "Sunday");
    assert(repo.getAll()[0].getSets() == 5);
    assert(repo.getAll()[0].getReps() == 20);

    repo.remove_ex(0);
    assert(repo.getAll().size() == 10);
    assert(repo.getAll()[0].getName() == "Squats");

    delete newEx;

}
