#include "GradeComputer.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace AB_GradeComputer{



// CONSTRUCTORS


gradeEntity::gradeEntity(){

    gradeWeight = 0;
    grade4Now = 0;
    gradeNum = 0;
}



// "GETTERS"


// Fetches grade value at a specified position in the vector
float gradeEntity::getGrade (int &g) const{
    return grades.at(g);
}


// Fetches value of "gradeWeight"
float gradeEntity::getWeight() const{
    return gradeWeight;
}


// Fetches value of "grade4Now"
float gradeEntity::getGradeFN() const{
    return grade4Now;
}


// Fetches value of "gradeNum"
int gradeEntity::get_gradeNum() const{
    return gradeNum;
}


// Returns length of the grades vector
int gradeEntity::gradesVectorLength() const{
    return grades.size();
}



// METHODS


// Sets gradeNum to a specified value
void gradeEntity::set_gradeNum(int num){
    gradeNum = num;
}


// Adds another grade to the end of the grades vector
void gradeEntity::addGrade(float &grade){
    grades.push_back(grade);
}


// Sorts entire vector of grades
void gradeEntity::sortGrades(){
    sort(grades.begin(), grades.end());
}


// Removes the specified number of grades starting w/ the smallest (to be used ONLY after sorting function above!)
void gradeEntity::removeGrades (int &num){

    for (int i = num; i > 0; i--){
        grades.erase(grades.begin());
    }
}


// Sets value for gradeWeight
void gradeEntity::setWeight(float &weight){
    gradeWeight = weight;
}


// Computes average of grades vector
float gradeEntity::average() const{

    float averageScore = 0;

    for (int i = 0; i < gradesVectorLength(); i++) {
        averageScore = getGrade(i) + averageScore;
    }

    averageScore = averageScore/gradesVectorLength();

return ceil((averageScore*100) - 0.49)/100;
}


// Sets "grade4Now" to the ultimate value of the grade entity (this "entityValue" can then be added to other "entityValues" to produce the final grade)
void gradeEntity::calcEntityValue(){
    float gradeVal = (gradeWeight/100)*average();

    grade4Now = ceil((gradeVal*100) - 0.49)/100;
}



} // End of namespace definition
