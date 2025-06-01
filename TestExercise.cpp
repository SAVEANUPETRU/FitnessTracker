#include "TestExercise.h"
#include <cassert>
void testExerciseConstructorAndGetters() {
    Exercise e("Push-ups", "Monday", 3, 15);
    assert(e.getName() == "Push-ups");
    assert(e.getDay() == "Monday");
    assert(e.getSets() == 3);
    assert(e.getReps() == 15);
}

void testExerciseSetters() {
    Exercise e("Push-ups", "Monday", 3, 15);
    e.setName("Squats");
    e.setDay("Wednesday");
    e.setSets(4);
    e.setReps(20);

    assert(e.getName() == "Squats");
    assert(e.getDay() == "Wednesday");
    assert(e.getSets() == 4);
    assert(e.getReps() == 20);
}
void testExercise(){
    testExerciseConstructorAndGetters();
    testExerciseSetters();
}
