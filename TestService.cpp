#include "TestService.h"

void test_service() {
    Service service(1);
    int initialSize = service.get_all().size();

    service.add("Test Exercise", "Monday", 3, 15);
    auto all = service.get_all();
    assert(all.size() == initialSize + 1);
    assert(all.back().getName() == "Test Exercise");
    assert(all.back().getDay() == "Monday");
    QString fortest = "Monday";
    auto mondayFiltered = service.filter_combined(fortest, 50);
    assert(mondayFiltered.size() == 1);
    assert(mondayFiltered[0].getName() == "Squats");
    fortest = "Tuesday";
    auto tuesdayFiltered = service.filter_combined(fortest, 20);
    assert(tuesdayFiltered.size() == 2);

    int testExIndex = all.size() - 1;

    service.modify_ex(testExIndex, "Modified Exercise", "Tuesday", 4, 20);
    Exercise ex_mod = service.get_all()[testExIndex];
    assert(ex_mod.getName() == "Modified Exercise");
    assert(ex_mod.getDay() == "Tuesday");

    auto tuesdayFilteredAfterMod = service.filter_combined(fortest, 70);
    assert(tuesdayFilteredAfterMod.size() == 1);
    assert(tuesdayFilteredAfterMod[0].getName() == "Modified Exercise");

    service.undo();
    Exercise ex_undo = service.get_all()[testExIndex];
    assert(ex_undo.getName() == "Test Exercise");
    assert(ex_undo.getDay() == "Monday");
    fortest = "Monday";
    auto mondayFilteredAfterUndo = service.filter_combined(fortest, 50);
    assert(mondayFilteredAfterUndo.size() == 1);
    assert(mondayFilteredAfterUndo[0].getName() == "Squats");

    service.redo();
    Exercise ex_redo = service.get_all()[testExIndex];
    assert(ex_redo.getName() == "Modified Exercise");
    assert(ex_redo.getDay() == "Tuesday");

    service.remove_ex(testExIndex);
    assert(service.get_all().size() == initialSize);
    fortest = "Tuesday";
    auto tuesdayFilteredAfterRemove = service.filter_combined(fortest, 20);
    assert(tuesdayFilteredAfterRemove.size() == 2);

    service.undo();
    assert(service.get_all().size() == initialSize + 1);
    auto allAfterUndo = service.get_all();
    bool foundModifiedExercise = false;
    for (auto& ex : allAfterUndo) {
        if (ex.getName() == "Modified Exercise" && ex.getDay() == "Tuesday") {
            foundModifiedExercise = true;
            break;
        }
    }
    assert(foundModifiedExercise);
    fortest = "Wednesday";
    auto wednesdayFiltered = service.filter_combined(fortest, 30);
    assert(wednesdayFiltered.size() == 1);
    assert(wednesdayFiltered[0].getName() == "Bench Press");
    fortest = "Thursday";
    auto thursdayFiltered = service.filter_combined(fortest, 100);
    assert(thursdayFiltered.size() == 1);
    assert(thursdayFiltered[0].getName() == "Plank");
    fortest = "Friday";
    auto fridayFiltered = service.filter_combined(fortest, 80);
    assert(fridayFiltered.size() == 2);
    fortest = "Saturday";
    auto saturdayFiltered = service.filter_combined(fortest, 10);
    assert(saturdayFiltered.size() == 0);
    fortest = "Thursday";
    auto highThresholdFiltered = service.filter_combined(fortest, 200);
    assert(highThresholdFiltered.size() == 0);

    service.redo();
    assert(service.get_all().size() == initialSize);
    service.undo();
    assert(service.get_all().size() == initialSize + 1);
    service.undo();
    assert(service.get_all().size() == initialSize + 1);
    auto allAfterUndoModify = service.get_all();
    bool foundTestExercise = false;
    for (auto& ex : allAfterUndoModify) {
        if (ex.getName() == "Test Exercise" && ex.getDay() == "Monday") {
            foundTestExercise = true;
            break;
        }
    }
    assert(foundTestExercise);

    service.redo();
    assert(service.get_all().size() == initialSize + 1);
    auto finalAll = service.get_all();
    bool foundEitherExercise = false;
    for (auto& ex : finalAll) {
        if ((ex.getName() == "Test Exercise" && ex.getDay() == "Monday") ||
            (ex.getName() == "Modified Exercise" && ex.getDay() == "Tuesday")) {
            foundEitherExercise = true;
            break;
        }
    }
    assert(foundEitherExercise);
}

