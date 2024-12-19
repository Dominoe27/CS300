#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// Define the Course class
class Course {
public:
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() {}

    Course(string number, string name) {
        courseNumber = number;
        title = name;
    }
};

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load courses from a file
void loadCourses(string filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        ++lineCount;
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 2) {
            cerr << "Error: Malformed line " << lineCount << ": " << line << endl;
            continue;
        }

        Course course(tokens[0], tokens[1]);
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        courses[course.courseNumber] = course;
    }
    file.close();

    if (courses.empty()) {
        cerr << "Error: No courses were loaded. Please check the file format and content." << endl;
    }
    else {
        cout << "Courses loaded successfully. Total courses: " << courses.size() << endl;
    }
}

// Function to print the course list in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No courses available to display. Please load the data first." << endl;
        return;
    }

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl;
    }
    cout << endl;
}

// Function to print details for a specific course
void printCourse(const map<string, Course>& courses, string courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.title << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    else {
        cout << "No prerequisites." << endl;
    }
}

// Main function
int main() {
    map<string, Course> courses;
    int choice;

    cout << "Welcome to the course planner." << endl;

    do {
        cout << "\n1. Load Data Structure.\n2. Print Course List.\n3. Print Course.\n9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string filename = "CS 300 ABCU_Advising_Program_Input.csv";
            loadCourses(filename, courses);
            break;
        }
        case 2:
            printCourseList(courses);
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
            printCourse(courses, courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}
