#include <vector>
#include <algorithm>

#ifndef GRADECOMPUTER_H
#define GRADECOMPUTER_H

namespace AB_GradeComputer{

    class gradeEntity{

    private:
        std::vector<float> grades; // Will store all grade values
        int gradeNum; // Will store number of homework grades
        float gradeWeight; // Will store the value of the grade entity's weight
        float grade4Now; // This will ultimately be equal to the average of the grades multiplied by the grade's weight

    public:

        // Constructors:
        gradeEntity(); // Creates valid new "grade entity"

        // "Getters":
        float getGrade (int &g) const; // Returns grade value stored in the vector @ a specified position
        float getWeight() const; // Returns value of the grade entity's weight
        float getGradeFN() const; // Returns the grade4Now value (explained above)
        int get_gradeNum() const; // Returns the number of homeworks the user entered (if greater than 0)
        int gradesVectorLength() const; // Returns the size of the grades vector

        // Modifiers:
        void set_gradeNum(int num);
        void addGrade(float &grade); // Adds a grade value to the grades vector
        void sortGrades(); // Sorts the entire grades vector
        void removeGrades(int &num); // Removes the desired number of grades from the grades vector starting w/ the smallest (ONLY RUN AFTER SORTING)
        void setWeight(float &weight); // Sets value of gradeWeight
        float average() const; // Will return average of grades vector
        void calcEntityValue(); // Will set "grade4Now" to weight*average (which can then be added to other "entityValues" to get the final grade)
    };

}

#endif // GRADECOMPUTER_H
