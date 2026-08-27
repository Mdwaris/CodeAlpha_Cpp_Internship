#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Course
{
    string name;
    double grade;
    double credit;
};

vector<Course> createCourses(int numberOfCourses)
{
    vector<Course> courses(numberOfCourses);
    return courses;
}

void takeInput(vector<Course>& courses)
{
    for (int i = 0; i < courses.size(); i++)
    {
        cout << "\nEnter details for Course " << i + 1 << ":\n";

        cout << "Course name: ";
        cin >> courses[i].name;

        cout << "Grade point: ";
        cin >> courses[i].grade;

        cout << "Credit hours: ";
        cin >> courses[i].credit;
    }
}
double calculateTotalCreadits(vector<Course>& courses){
    double totalCreadits = 0;
    for(int i = 0; i < courses.size(); i++)
    {
        totalCreadits += courses[i] . credit;

    }
    return totalCreadits;
}

double calculateGradePoints(const vector<Course>& courses)
{
    double totalPoints = 0;

    for (int i = 0; i < courses.size(); i++)
    {
        totalPoints += courses[i].grade * courses[i].credit;
    }

    return totalPoints;
}

double calculateCGPA(double totalPoints, double totalCredits)
{
    if (totalCredits == 0)
    {
        return 0;
    }

    return totalPoints / totalCredits;
}

void showResult(const vector<Course>& courses, double cgpa)
{
    cout << "\n========== Course Details ==========\n";

    for (int i = 0; i < courses.size(); i++)
    {
        cout << "Course: " << courses[i].name
             << " | Grade: " << courses[i].grade
             << " | Credits: " << courses[i].credit << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nFinal CGPA: " << cgpa << endl;
}

int main()
{
    int numberOfCourses;

    cout << "===== CGPA Calculator =====\n";
    cout << "Enter number of courses: ";
    cin >> numberOfCourses;

    vector<Course> courses = createCourses(numberOfCourses);


    takeInput(courses);

    double totalCredits = calculateTotalCreadits(courses);
    double totalPoints =  calculateGradePoints(courses);

    double cgpa = calculateCGPA(totalPoints, totalCredits);
    cout << "GPA: " << cgpa << endl;

    showResult(courses, cgpa);

    return 0;
}