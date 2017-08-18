// This is the implementation file for the "computingSession" class

#include <iostream>
#include <istream>
#include <string>
#include <algorithm>

#include "ComputingGrade.h"


namespace AB_GradeComputer{

float zero = 0;


// Constructor (Doesn't really need to do anything)
computingSession::computingSession(){
    /*
    g[0] will be used used for homework (IF it counts; otherwise, it'll be the next entity that counts)
    g[1] will be used used for quizzes (Same conditions as above apply)
    g[2] will be used used for exams (Same conditions as above apply)
    g[3] will be used used for the final (Same conditions as above apply)
    g[4] will be used used for misc. grades (Same conditions as above apply)
    */
}


// This is for when I request a "Y" or "N" input -- this checks any letter input, & requests a re-input if not "y" or "n"
void computingSession::checkLetterEntry(char &c) {
    while (c != 'Y' && c != 'y' && c != 'N' && c != 'n'){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Please enter only Y or N: ";
        std::cin >> c;
        std::cout << std::endl;
    }
}


// Will check for non-integer input
void computingSession::checkCinInt(std::istream &input, int &inputInt){
    while (!input.good()){
        input.clear();
        input.ignore();
        std::cout << "That's not what I asked for . . . Would you please try again?: " << std::endl;
        input >> inputInt;
    }
}


// Will check for non-float input
void computingSession::checkCinFloat(std::istream &input, float &inFloat){
    while (!input.good()){
        input.clear();
        input.ignore();
        std::cout << "That's not what I asked for . . . Would you please try again?: " << std::endl;
        input >> inFloat;
    }
}


// Checks for grades smaller than 0 or larger than 100%
void computingSession::checkGradeVal(std::istream &input, float &grade){

    checkCinFloat(input, grade);

    while (grade < 0 || grade > 100){
        std::cout << "Please only enter a value between 0 & 100 inclusive: ";
        std::cin >> grade;
        std::cout << std::endl;
        checkCinFloat(input, grade);
    }
}


// Checks for point values smaller than or equal to 0
void computingSession::checkPointVal(std::istream &input, float &pointVal){

    checkCinFloat(input, pointVal);

    while (pointVal <= 0){
        std::cout << "That point value sure as heck ain't possible! Wanna' try to re-enter it?: ";
        std::cin >> pointVal;
        std::cout << std::endl;
        checkCinFloat(input, pointVal);
    }
}


// Checks for whether an integer is <= 0
void computingSession::check4PosInt(std::istream &input, int &entityNum){

    checkCinInt(input, entityNum);

    while (entityNum <= 0){
        std::cout << "That's not possible! I have a feeling that was a mistake & you'd like to try again: ";
        std::cin >> entityNum;
        std::cout << std::endl;
        checkCinInt(input, entityNum);
    }
}


// Checks for point values larger than totalPoints
void computingSession::checkForLargerThanTotal (std::istream &input, float &pointVal){

    checkCinFloat(input, pointVal);

    if (pointVal <= 0){
        checkPointVal(input, pointVal);
    }
    else {
        while (pointVal > totalPoints){
            std::cout << "Your value is larger than the total points you entered! Please re-enter that value: ";
            std::cin >> pointVal;
            std::cout << std::endl;
            checkCinFloat(input, pointVal);
        }
    }
}


// Checks for whether a given integer input is 1 or 2
void computingSession::checkSetupNum(std::istream &input, int &setupNum){
    while (setupNum != 1 && setupNum != 2){
        input.clear();
        input.ignore();
        std::cout << "No, seriously, please only enter \"1\" or \"2\": ";
        input >> setupNum;
    }
}


// Will be called in order to set/reset the points that homework counts
void computingSession::setEntityPointVal(char a){
    float pointVal;

    for (int i = 0; i < 5; i++){
        entityPointVals.push_back(0);
    }

    if (a == 'h'){
        std::cout << "Please enter the number of points that homework counts for: ";
        std::cin >> pointVal;
        checkPointVal(std::cin, pointVal);
        checkForLargerThanTotal(std::cin, pointVal);
        entityPointVals[0] = pointVal;
    }
    else if (a == 'q'){
        std::cout << "Please enter the number of points that quizzes count for: ";
        std::cin >> pointVal;
        checkPointVal(std::cin, pointVal);
        checkForLargerThanTotal(std::cin, pointVal);
        entityPointVals[1] = pointVal;
    }
    else if (a == 'e'){
        std::cout << "Please enter the number of points that exams counts for: ";
        std::cin >> pointVal;
        checkPointVal(std::cin, pointVal);
        checkForLargerThanTotal(std::cin, pointVal);
        entityPointVals[2] = pointVal;
    }
    else if (a == 'f'){
        std::cout << "Please enter the number of points that the final counts for: ";
        std::cin >> pointVal;
        checkPointVal(std::cin, pointVal);
        checkForLargerThanTotal(std::cin, pointVal);
        entityPointVals[3] = pointVal;
    }
    else if (a == 'm'){
        std::cout << "Please enter how many points that these grades count for: ";
        std::cin >> pointVal;
        checkPointVal(std::cin, pointVal);
        checkForLargerThanTotal(std::cin, pointVal);
        entityPointVals[4] = pointVal;
    }

}


// ---------- PRIMARY FUNCTION ----------


// The primary function of this entire program. This determines what entities to use or not, based on the user's input
void computingSession::compute(){

    // Determining the grading setup of the class

    std::cout << "Is your class based on a total number of points attainable, w/ individual entities [i.e. homework, quizzes, etc.] being worth a certain number of points out of the total?";
    std::cout << std::endl << "Or is it based on a total attainable percentage of 100%, w/ individual entities being worth a certain percentage thereof?";
    std::cout << std::endl << "Please enter \"1\" for the 1st option, or \"2\" for the 2nd one: ";
    std::cin >> classSetup;

    checkSetupNum(std::cin, classSetup);

    // Finished testing input

    std::cout << std::endl;

    // Inquire into how many possible points, as well as the grade thresholds
    float tempPointVal;
    if (classSetup == 1){
        std::cout << "How many possible points are attainable in this class?: ";
        std::cin >> totalPoints;

        checkPointVal(std::cin, totalPoints);

        std::cout << "What is the minimum total number of points necessary for an A?: ";
        std::cin >> tempPointVal;
        checkForLargerThanTotal(std::cin, tempPointVal);
        gradeThresholds.push_back(tempPointVal);

        std::cout << "Minimum total number of points necessary to obtain a B?: ";
        std::cin >> tempPointVal;
        checkForLargerThanTotal(std::cin, tempPointVal);
        while (tempPointVal >= gradeThresholds[0]){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Nah, try that again: ";
            std::cin >> tempPointVal;
            checkForLargerThanTotal(std::cin, tempPointVal);
        }
        gradeThresholds.push_back(tempPointVal);

        std::cout << "What about for a C?: ";
        std::cin >> tempPointVal;
        checkForLargerThanTotal(std::cin, tempPointVal);
        while (tempPointVal >= gradeThresholds[1]){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Try a smaller number: ";
            std::cin >> tempPointVal;
            checkForLargerThanTotal(std::cin, tempPointVal);
        }
        gradeThresholds.push_back(tempPointVal);

        std::cout << "Finally, enter the minimum point total needed for a D: ";
        std::cin >> tempPointVal;
        checkForLargerThanTotal(std::cin, tempPointVal);
        while (tempPointVal >= gradeThresholds[2]){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Too high, re-enter that: ";
            std::cin >> tempPointVal;
            checkForLargerThanTotal(std::cin, tempPointVal);
        }
        gradeThresholds.push_back(tempPointVal);
    }
    else {
        char stdThresholds;

        std::cout << "A common standard for professors to use is that 90% or more gets you an A, between 80% & 90% gets you a B, etc." << std::endl;
        std::cout << "If your class uses this standard, please just enter \"Y\"; otherwise, enter any other character: ";
        std::cin >> stdThresholds;

        while (!std::cin.good()){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "I thought you knew what a character was... Nevermind, please just enter a letter, to keep it simple: ";
            std::cin >> stdThresholds;
        }

        if (stdThresholds == 'Y' || stdThresholds == 'y'){
            gradeThresholds.push_back(90); // A
            gradeThresholds.push_back(80); // B
            gradeThresholds.push_back(70); // C
            gradeThresholds.push_back(60); // D
        }
        else {
            std::cout << "Please enter the minimum overall percentage necessary to obtain an A: ";
            std::cin >> tempPointVal;
            checkGradeVal(std::cin, tempPointVal);
            gradeThresholds.push_back(tempPointVal);

            std::cout << "Now enter the minimum necessary percentage necessary to get a B: ";
            std::cin >> tempPointVal;
            checkGradeVal(std::cin, tempPointVal);
            while (tempPointVal >= gradeThresholds[0]){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Nah, that's too high. Re-enter that: ";
                std::cin >> tempPointVal;
                checkGradeVal(std::cin, tempPointVal);
            }
            gradeThresholds.push_back(tempPointVal);


            std::cout << "What's the least you'll need for a C?: ";
            std::cin >> tempPointVal;
            checkGradeVal(std::cin, tempPointVal);
            while (tempPointVal >= gradeThresholds[1]){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Nah, that's too high. Re-enter that: ";
                std::cin >> tempPointVal;
                checkGradeVal(std::cin, tempPointVal);
            }
            gradeThresholds.push_back(tempPointVal);

            std::cout << "Finally, put in the minimum you need to get to get a D: ";
            std::cin >> tempPointVal;
            checkGradeVal(std::cin, tempPointVal);
            while (tempPointVal >= gradeThresholds[2]){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "How about...No? Try again: ";
                std::cin >> tempPointVal;
                checkGradeVal(std::cin, tempPointVal);
            }
            gradeThresholds.push_back(tempPointVal);
        }

    }



    // Compute: Homework

    std::cout << "Does homework count towards your final grade? If so, enter \"Y\"; otherwise, enter \"N\": ";
    std::cin >> doesItCount[0];

    checkLetterEntry(doesItCount[0]);

    if (doesItCount[0] == 'Y' || doesItCount[0] == 'y')
        homeworkEntity();



    // Compute: Quizzes

    std::cout << "Alright, so do quizzes count towards your final grade? If so, enter \"Y\"; otherwise, enter \"N\": ";
    std::cin >> doesItCount[1];

    checkLetterEntry(doesItCount[1]);

    if (doesItCount[1] == 'Y' || doesItCount[1] == 'y')
        quizEntity();



    // Compute: Exams

    std::cout << "Did you have any exams that counted towards your final grade? If so, enter \"Y\"; otherwise, enter \"N\": ";
    std::cin >> doesItCount[2];

    checkLetterEntry(doesItCount[2]);

    if (doesItCount[2] == 'Y' || doesItCount[2] == 'y')
        examEntity();



    // Compute: Final Exam
    std::cout << "Is there a final exam? Please enter \"Y\" or \"N\" (regardless of whether you've taken it yet): ";
    std::cin >> doesItCount[3];

    checkLetterEntry(doesItCount[3]);

    if (doesItCount[3] == 'Y' || doesItCount[3] == 'y')
        finalEntity();



    // Compute: Misc. Entities
    std::cout << "Is there anything else that counts towards your final grade? Please enter \"Y\" or \"N\": ";
    std::cin >> doesItCount[4];

    checkLetterEntry(doesItCount[4]);

    if (doesItCount[4] == 'Y' || doesItCount[4] == 'y')
        miscEntity();

    /*
    float finGrade;

    finGrade = g[0].getGradeFN() + g[1].getGradeFN() + g[2].getGradeFN() + g[3].getGradeFN() + g[4].getGradeFN();
    */

    // Output results via this function:
    resultsDisplay();


} // End of "compute()"


// ---------- END OF PRIMARY FUNCTION ----------






// Used by the homework, quiz, exams, & bonus grades' functions to obtain grades manually from user
void computingSession::obtainGradesManually(float &enteredGrade, gradeEntity &gp){
    for (int i = 1; i < gp.get_gradeNum(); ++i){
        std::cout << "Grade " << i + 1 << " of " << gp.get_gradeNum() << ": ";
        std::cin >> enteredGrade;

        if (classSetup == 1)
            checkPointVal(std::cin, enteredGrade);
        else
            checkGradeVal(std::cin, enteredGrade);

        gp.addGrade(enteredGrade);
    }
}



// Will be called by "compute()" to get the homework grades & weight from the user
void computingSession::homeworkEntity(){

    gradeEntity homework;

    int tempNum;

    std::cout << "Awesome! Let's start inputting your homework grades!" << std::endl;
    std::cout << "First, would you please enter how many homework grades you've got to enter?: ";
    std::cin >> tempNum;
    check4PosInt(std::cin, tempNum);
    std::cout << std::endl;

    homework.set_gradeNum(tempNum);

    float tempGrade;

    /*
    char painlessWay;

    std::cout << "Would you like to enter your homework grades through a .txt or .dat file? Please enter \"Y\" or \"N\": ";
    std::cin >> painlessWay;

    checkLetterEntry(painlessWay);
    */

    std::cout << "Alright, then, please enter each grade individually, starting w/ the 1st 1: ";
    std::cin >> tempGrade;

    if (classSetup == 1)
        checkPointVal(std::cin, tempGrade);
    else
        checkGradeVal(std::cin, tempGrade);

    homework.addGrade(tempGrade);

    obtainGradesManually(tempGrade, homework);

    if (classSetup == 1){

        setEntityPointVal('h');
        float pointWeight = entityPointVals[0]/totalPoints;
        homework.setWeight(pointWeight);

    } // End of "if (classSetup == 1)..."
    else {

        float homeworkWeight;

        std::cout << "What is the weight of the homeworks? Please enter as a percentage value up to 2 decimal places: ";
        std::cin >> homeworkWeight;

        checkGradeVal(std::cin, homeworkWeight);

        homework.setWeight(homeworkWeight);

    } // End of "else" statement

    g.push_back(homework);

    g[0].calcEntityValue();

}


// Will be called by "compute()" to get the quiz grades & weight from the user
void computingSession::quizEntity(){

    gradeEntity quizzes;

    int tempNum;

    std::cout << "Alrighty then, would you please enter how many quiz grades you've got to enter?: ";
    std::cin >> tempNum;
    checkCinInt(std::cin, tempNum);
    std::cout << std::endl;

    quizzes.set_gradeNum(tempNum);

    float tempGrade;

    std::cout << "Great! Now please enter each grade, starting w/ the 1st 1: ";
    std::cin >> tempGrade;

    if (classSetup == 1)
        checkPointVal(std::cin, tempGrade);
    else
        checkGradeVal(std::cin, tempGrade);

    quizzes.addGrade(tempGrade);


    obtainGradesManually(tempGrade, quizzes);


    if (classSetup == 1){
        setEntityPointVal('q');
        float pointWeight = entityPointVals[1]/totalPoints;
        quizzes.setWeight(pointWeight);
    }
    else {

        float quizzesWeight;

        std::cout << "What is the weight of the quizzes? Please enter as a percentage value up to 2 decimal places: ";
        std::cin >> quizzesWeight;

        checkGradeVal(std::cin, quizzesWeight);

        quizzes.setWeight(quizzesWeight);
    }

    g.push_back(quizzes);

    g[1].calcEntityValue();

}


// Will be called by "compute()" to get the exam grades & weight from the user
void computingSession::examEntity(){

    gradeEntity exams;

    int tempNum;

    std::cout << "Enter how many exams you had: ";
    std::cin >> tempNum;

    while (tempNum < 0 && tempNum > 10){
        std::cout << "That number of exams isn't possible! Please re-enter that number: ";
        std::cin >> tempNum;
        std::cout << std::endl;
    }

    std::cout << std::endl;

    exams.set_gradeNum(tempNum);

    float tempGrade;

    std::cout << "Great! Now please enter each grade, starting w/ the 1st 1: ";
    std::cin >> tempGrade;

    if (classSetup == 1)
        checkPointVal(std::cin, tempGrade);
    else
        checkGradeVal(std::cin, tempGrade);

    exams.addGrade(tempGrade);


    obtainGradesManually(tempGrade, exams);


    if (classSetup == 1){
        setEntityPointVal('e');
        float pointWeight = entityPointVals[2]/totalPoints;
        exams.setWeight(pointWeight);
    }
    else {

        float examsWeight;

        std::cout << "What is the weight of the exams? Please enter as a percentage value up to 2 decimal places: ";
        std::cin >> examsWeight;

        checkGradeVal(std::cin, examsWeight);

        exams.setWeight(examsWeight);
    }


    g.push_back(exams);

    g[2].calcEntityValue();

}



// Will be called by "compute()" to get the final exam's value & weight from the user
void computingSession::finalEntity(){

    gradeEntity finalExam;

    char finalTaken;

    std::cout << "Have you taken the final yet? Please enter \"Y\" or \"N\": ";
    std::cin >> finalTaken;

    checkLetterEntry(finalTaken);

    float tempGrade;

    if (finalTaken == 'Y' || finalTaken =='y'){

        std::cout << "What'd you get on the final?: ";
        std::cin >> tempGrade;

        if (classSetup == 1)
            checkPointVal(std::cin, tempGrade);
        else
            checkGradeVal(std::cin, tempGrade);

        finalExam.addGrade(tempGrade);
    }
    else{
        finalExam.addGrade(zero);
    }


    // If the class is based on a total number of points earned, then:
    if (classSetup == 1){
        setEntityPointVal('f');
        float pointWeight = entityPointVals[3]/totalPoints;
        finalExam.setWeight(pointWeight);
    }
    // Otherwise:
    else{
        float finalWeight;

        std::cout << "What is the weight of the final? Please enter as a percentage value up to 2 decimal values: ";
        std::cin >> finalWeight;

        checkForLargerThanTotal(std::cin, finalWeight);

        finalExam.setWeight(finalWeight);

    }


    g.push_back(finalExam);

    g[3].calcEntityValue();

}
// End of "finalEntity()"


// Will be used by compute() to obtain any additional grades that count towards the final grade
void computingSession::miscEntity(){


    gradeEntity misc;

    int tempNum;

    std::cout << "Alrighty then, how many additional grades are there?: ";
    std::cin >> tempNum;
    checkCinInt(std::cin, tempNum);
    std::cout << std::endl;

    misc.set_gradeNum(tempNum);

    float tempGrade;

    std::cout << "Great! Now please enter each grade, starting w/ the 1st 1: ";
    std::cin >> tempGrade;

    if (classSetup == 1)
        checkGradeVal(std::cin, tempGrade);
    else
        checkPointVal(std::cin, tempGrade);

    misc.addGrade(tempGrade);


    obtainGradesManually(tempGrade, misc);


    if (classSetup == 1){
        setEntityPointVal('m');
        float pointWeight = entityPointVals[4]/totalPoints;
        misc.setWeight(pointWeight);
    }
    else {

        float miscWeight;

        std::cout << "What is the weight of these grades? Please enter as a percentage value up to 2 decimal places: ";
        std::cin >> miscWeight;

        checkGradeVal(std::cin, miscWeight);

        misc.setWeight(miscWeight);
    }

    g.push_back(misc);

    g[4].calcEntityValue();

}


// This is used in compute() to prompt the user for their desired results
void computingSession::resultsDisplay(){

    if (classSetup == 1){
        std::cout << "Since your class is based on a point total, results will be shown in point totals." << std::endl << std::endl;
    }
    else{
        std::cout << "Since your class is based on percentages, results will be shown in percentages." << std::endl << std::endl;
    }


    // Results Output Selection

    int outSelect;

    std::cout << "What results would you like to see? Please select an option from the list below by entering the corresponding number:" << std::endl << std::endl;
    std::cout << "[1] Just the homework average (or total of points earned through homework)" << std::endl;
    std::cout << "[2] Just the quizzes average (or total of points earned through quizzes)" << std::endl;
    std::cout << "[3] Just the exams average (or total of points earned through exams)" << std::endl;
    std::cout << "[4] Just the bonus grades average (or total points earned through bonus)" << std::endl;
    std::cout << "[5] The homework, quizzes, exams, & bonus assignments averages (or point totals associated w/ them)" << std::endl;
    std::cout << "[6] Your final grade in the class (includes final & all grades entered, assuming you've taken the final)" << std::endl;
    std::cout << std::endl << "Assuming you have NOT taken the final: " << std::endl;
    std::cout << "[7] Your class grade at this point if you COMPLETELY flunked the final (i.e. total points earned from homework, quizzes, & exams w/ a 0% on the final exam)" << std::endl;
    std::cout << "[8] The percentage/points you'll need to get on the final to get an A, B, or C (will display all 3)" << std::endl;
    std::cout << "[9] The whole shebang (a full & extensive report on your current grade in the class [whether or not you've taken the final])" << std::endl;

    std::cout << "Just enter what you'd like to see: ";
    std::cin >> outSelect;

    // Check to make sure user isn't incompetent
    while (!std::cin.good()){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "That's not really a number, so try again: ";
        std::cin >> outSelect;
    }

    // Test outSelect for erroneous input
    while (outSelect != 1 && outSelect != 2 && outSelect != 3 && outSelect != 4 && outSelect != 5 && outSelect != 6 && outSelect != 7 && outSelect != 8 && outSelect != 9 && outSelect != 10){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Please only input an integer between 1 & 10 inclusive: ";
        std::cin >> outSelect;
        // Check input again just to be sure
        while (!std::cin.good()){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "That's not really a number, so try again: ";
            std::cin >> outSelect;
        }
    }

    // Checks to make sure you've actually taken final if you choose option requiring final to have been taken
    if (outSelect == 6){
        int zeroInt = int(zero);
        if (g[3].getGrade(zeroInt) == 0){
            while (outSelect == 6){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "You haven't taken the final. Try a different option!: ";
                std::cin >> outSelect;

                while (outSelect != 1 && outSelect != 2 && outSelect != 3 && outSelect != 4 && outSelect != 5 && outSelect != 6 && outSelect != 7 && outSelect != 8 && outSelect != 9 && outSelect != 10){
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Please only input an integer between 1 & 10 inclusive: ";
                    std::cin >> outSelect;
                    // Check input again just to be sure
                    while (!std::cin.good()){
                        std::cin.clear();
                        std::cin.ignore();
                        std::cout << "That's not really a number, so try again: ";
                        std::cin >> outSelect;
                    }
                }
            }
        }
    }
    // Done testing output


    if (outSelect == 1 || outSelect == 2 || outSelect == 3 || outSelect == 4 || outSelect == 5){
        averageOutput(outSelect);
    }
    else if (outSelect == 6){
        if (classSetup == 1){
            float pointTotal = sumPoints(g[0]) + sumPoints(g[1]) + sumPoints(g[2]) + sumPoints(g[3]) + sumPoints(g[4]);
            std::cout << "Your point total in the course is: " << pointTotal << "/" << totalPoints << std::endl;
            if (pointTotal >= gradeThresholds.at(0))
                std::cout << "You have an A in the course!" << std::endl;
            else if (pointTotal >= gradeThresholds.at(1) && pointTotal < gradeThresholds.at(0))
                std::cout << "You have a B in the course!" << std::endl;
            else if (pointTotal >= gradeThresholds.at(2) && pointTotal < gradeThresholds.at(1))
                std::cout << "This is a C." << std::endl;
            else if (pointTotal >= gradeThresholds.at(3) && pointTotal < gradeThresholds.at(2))
                std::cout << "You have a D in the course..." << std::endl;
            else
                std::cout << "You, uhh, have an F..." << std::endl;
        }
        else {
            float finGrade = g[0].getGradeFN() + g[1].getGradeFN() + g[2].getGradeFN() + g[3].getGradeFN() + g[4].getGradeFN();
            std::cout << "Your point total in the course is: " << finGrade << "%" << std::endl;
            if (finGrade >= gradeThresholds.at(0))
                std::cout << "You have an A in the course!" << std::endl;
            else if (finGrade >= gradeThresholds.at(1) && finGrade < gradeThresholds.at(0))
                std::cout << "You have a B in the course!" << std::endl;
            else if (finGrade >= gradeThresholds.at(2) && finGrade < gradeThresholds.at(1))
                std::cout << "This is a C." << std::endl;
            else if (finGrade >= gradeThresholds.at(3) && finGrade < gradeThresholds.at(2))
                std::cout << "You have a D in the course..." << std::endl;
            else
                std::cout << "You, uhh, have an F..." << std::endl;
        }
    }
    else if (outSelect == 7){
        if (classSetup == 1){
            float currentPoints = sumPoints(g[0]) + sumPoints(g[1]) + sumPoints(g[2]) + sumPoints(g[3]) + sumPoints(g[4]);
            std::cout << "Your current point total is: " << currentPoints << "/" << totalPoints << std::endl;
        }
        else {
            float currentGrade = g[0].getGradeFN() + g[1].getGradeFN() + g[2].getGradeFN() + g[3].getGradeFN() + g[4].getGradeFN();
            std::cout << "Your current course grade (assuming you completely fail the final) is: " << currentGrade << "%" << std::endl;
        }
    }
    else if (outSelect == 8){

        if (classSetup == 1){
            float currentPoints = sumPoints(g[0]) + sumPoints(g[1]) + sumPoints(g[2]) + sumPoints(g[3]) + sumPoints(g[4]);
            std::cout << "Your current point total is: " << currentPoints << "/" << totalPoints << std::endl;

            if (currentPoints >= gradeThresholds.at(0)){
                std::cout << "You already have an A! You actually do not NEED to take the final!" << std::endl;
            }
            else{
                float pointsNeeded;

                std::vector<std::string> letterGrades;

                for (int i = 0; i < 5; ++i){

                    std::string textInput;
                    if (i == 0)
                        textInput = "If you want an A, you'll need to get at least: ";
                    else if (i == 1)
                        textInput = "If you want a B, you'll need to get at least: ";
                    else if (i == 2)
                        textInput = "If you want a C, you'll need to get at least: ";
                    else if (i == 3)
                        textInput = " points, or ";
                    else if (i == 4)
                        textInput = "% on the final";

                    letterGrades.push_back(textInput);

                }


                // If "currentPoints" indicates that the user has a D or lower:
                if (currentPoints < gradeThresholds.at(2)){
                    for (int i = 0; i < 3; i++){
                        pointsNeeded = gradeThresholds.at(i) - currentPoints;
                        std::cout << letterGrades[i] << pointsNeeded << letterGrades[3] << 100*pointsNeeded/entityPointVals[3] << letterGrades[4] << std::endl;
                    }
                }
                // If "currentPoints" indicates that the user has a C:
                else if (currentPoints >= gradeThresholds.at(2) && currentPoints < gradeThresholds.at(1)){
                    for (int i = 0; i < 2; i++){
                        pointsNeeded = gradeThresholds.at(i) - currentPoints;
                        std::cout << letterGrades[i] << pointsNeeded << letterGrades[3] << 100*pointsNeeded/entityPointVals[3] << letterGrades[4] << std::endl;
                    }
                }
                // If "currentPoints" indicates that the user has a B:
                else if (currentPoints >= gradeThresholds.at(1) && currentPoints < gradeThresholds.at(0)){
                    pointsNeeded = gradeThresholds.at(0) - currentPoints;
                    std::cout << letterGrades[0] << pointsNeeded << letterGrades[3] << 100*pointsNeeded/entityPointVals[3] << letterGrades[4] << std::endl;
                }
            }
        }
        else {
            float currentGrade = g[0].getGradeFN() + g[1].getGradeFN() + g[2].getGradeFN() + g[3].getGradeFN() + g[4].getGradeFN();

            std::cout << "Your current point total is: " << currentGrade << "/" << totalPoints << std::endl;
        }
    } // End of "if (outSelect == 8)"

    else if (outSelect == 9){

    }

}


// Is used by "averageOutput(int chooseEntity)" to sum the points of a given gradeEntity
float computingSession::sumPoints(gradeEntity &gp){
    float pointSum = 0;

    for (int i = 0; i < gp.gradesVectorLength(); i++) {
        pointSum = gp.getGrade(i) + pointSum;
    }

    return ceil((pointSum*100) - 0.49)/100;
}


// Is used by resultsDisplay() for determining what results to display
void computingSession::averageOutput(int chooseEntity){

    std::vector<std::string> entityOutputLabel; // This stores words that are used in result output (helps keep code shorter)
    entityOutputLabel.push_back("homework");
    entityOutputLabel.push_back("quizzes");
    entityOutputLabel.push_back("exams");
    entityOutputLabel.push_back("bonus assignments");

    if (classSetup == 1){
        if (chooseEntity == 1 || chooseEntity == 2 || chooseEntity == 3 || chooseEntity == 4){
            std::cout << "The total points you have accumulated for " << entityOutputLabel.at(chooseEntity - 1) << " is: " << sumPoints(g[chooseEntity - 1]) << "/" << entityPointVals[chooseEntity - 1] << std::endl;
        }
        else{
            for (int i = 0; i < 3; i++){
                std::cout << "The total points you have accumulated for " << entityOutputLabel.at(i) << " is: " << sumPoints(g[i]) << "/" << entityPointVals[i] << std::endl;
            }
        }
    }
    else{
        if (chooseEntity == 1 || chooseEntity == 2 || chooseEntity == 3){
            std::cout << "Your " << entityOutputLabel.at(chooseEntity - 1) << " average is: " << g[chooseEntity - 1].average() << "%" << std::endl;
        }
        else if (chooseEntity == 4){
            std::cout << "Your " << entityOutputLabel.at(3) << " average is: " << g[4].average() << "%" << std::endl;
        }
        else{
            for (int i = 0; i < 3; i++){
                std::cout << "Your " << entityOutputLabel.at(i) << " average is: " << g[i].average() << "%" << std::endl;
            }
            std::cout << "Your " << entityOutputLabel.at(3) << " average is: " << g[4].average() << "%" << std::endl;
        }
    }

}


} // End of namespace definition
