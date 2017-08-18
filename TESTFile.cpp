#include <iostream>
#include "GradeComputer.h"
#include "ComputingGrade.h"

#include "catch.hpp"

using namespace AB_GradeComputer;


// TEST CASE 1: Test constructor & "get" functions

TEST_CASE("Should create a valid new empty \"grades\" constructor: ", "[gradeEntity]"){

    gradeEntity test;

    REQUIRE(test.getWeight() == 0);
    REQUIRE(test.getGradeFN() == 0);
    REQUIRE(test.get_gradeNum() == 0);
}


// TEST CASE 2: Test addGrade function

TEST_CASE("Should properly add the specified grades to the grades vector", "[gradeEntity]"){

    gradeEntity test;
    int i[] = {0, 1, 2, 3};

    float addG[] = {5, 10, 1, 15};

    for (int i = 0; i < 4; i++){
        test.addGrade(addG[i]);
    }

    for (int g = 0; g < 4; g++){
        REQUIRE(test.getGrade(i[g]) == addG[g]);
    }
}


// TEST CASE 3: Test sorting function

TEST_CASE("Should properly sort the grades", "[gradeEntity]"){

    gradeEntity test;
    int i[] = {0, 1, 2, 3, 4};

    float addG[] = {5, 10, 1, 15, 9};
    float sortedG[] = {1, 5, 9, 10, 15};

    for (int i = 0; i < 5; i++){
        test.addGrade(addG[i]);
    }

    test.sortGrades();

    for (int g = 0; g < 5; g++){
        REQUIRE(test.getGrade(i[g]) == sortedG[g]);
    }
}


// TEST CASE 4: Test removeGrade function

TEST_CASE("Should properly remove the specified number of grades", "[gradeEntity]"){

    gradeEntity test;
    int zero = 0;

    float addG[] = {5, 10, 1, 15, 9};

    for (int i = 0; i < 5; i++){
        test.addGrade(addG[i]);
    }

    test.sortGrades();

    int removeIT = 2;

    test.removeGrades(removeIT);

    REQUIRE(test.getGrade(zero) == 9);
}


// TEST CASE 5: Testing average function
TEST_CASE("Should properly calculate the average of all grades contained in the grades vector", "[gradeEntity]"){

    gradeEntity test;
    int zero = 0;

    float addG[] = {5.5, 10.1, 1.6, 15.66, 9};

    for (int i = 0; i < 5; i++){
        test.addGrade(addG[i]);
    }

    REQUIRE(test.average() == 8.37);
}


