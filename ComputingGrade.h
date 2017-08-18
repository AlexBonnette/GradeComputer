#ifndef COMPUTINGGRADE_H
#define COMPUTINGGRADE_H

#include "GradeComputer.h"

#include <vector>

namespace AB_GradeComputer{


    class computingSession{

    private:
        int classSetup;
        std::vector<float> entityPointVals; // Stores the point values associated w/ homework, quizzes, exams, final, & additional grades
        std::vector<float> gradeThresholds; // Stores the percentage/point total threshold for a grade of A, B, C, D, & F, respectively
        float totalPoints;

        std::vector<gradeEntity> g; // Vector of "gradeEntity"s
        char doesItCount[5];
        /*
        doesItCount[0] is used for homework
        doesItCount[1] is used for quizzes
        doesItCount[2] is used for exams
        doesItCount[3] is used for the final
        doesItCount[4] is used for anything else
        */

        // ----- Methods (private) -----

        // "Checkers"
        void checkLetterEntry(char &c); // This function is used to check doesItCount for proper input
        void checkCinInt(std::istream &input, int &inputInt);
        void checkCinFloat(std::istream &input, float &inFloat);
        void checkGradeVal(std::istream &input, float &grade); // Given an entered grade, will check to ascertain a reasonable input value
        void checkPointVal(std::istream &input, float &pointVal); // Given an entered point value, will check if it's smaller than or equal to 0
        void check4PosInt(std::istream &input, int &entityNum); // Checks to make sure an entered integer isn't <= 0
        void checkForLargerThanTotal(std::istream &input, float &pointVal); // Given an entered point value, will check if the point value is larger than the entered total
        void checkSetupNum(std::istream &input, int &setupNum); // Checks input integer for being 1 or 2; asks for re-entry if not


        // Others
        void setEntityPointVal(char a); // A function used to prompt the user for the point val associated w/ an entity (indicated by the character that is input into the function)
        void obtainGradesManually(float &enteredGrade, gradeEntity &gp); // A function used to obtain grades from the user via manual input (assumes the 1st 1 has already been entered)
        float sumPoints(gradeEntity &gp); // A function used in "averageOutput(int chooseEntity)" to output the proper sum or average
        void averageOutput(int chooseEntity); // A function used in resultsDisplay() to determine what to output
        void out


    public:
        // Constructor
        computingSession();

        // Methods
        void compute(); // This is the primary function for computing their final/current course grade.

        void homeworkEntity(); // This is called by the "compute()" function to ask the user for the desired input for homework grades
        void quizEntity(); // This is called by the "compute()" function to ask the user for the desired input for quiz grades
        void examEntity(); // This is called by the "compute()" function to ask the user for the desired input for exams grades
        void finalEntity(); // This is called by the "compute()" function to ask the user for the desired input for final grades
        void miscEntity(); // This is called by the "compute()" function to ask the user for the desired input for misc grades
        void resultsDisplay(); // This is called by "compute()" at the very end to prompt the user for what results they'd like to see

    };

} // End of namespace definition

#endif // COMPUTINGGRADE_H
