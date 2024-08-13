// Name        : ProjectTwo.cpp
// Author      : Darrell Walker II
// Date        : 10/16/2023
// Description : This program implements a course advising system using a map data structure to store course information from a CSV file.
//               The user can view a list of all available courses, view details about a specific course, and exit the program.

// Pre-processor directives
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

namespace AdvisingSystem {

    // Define the structure for a course
    struct Course {
        string courseID;
        string courseTitle;
        vector<string> prerequisites;
    };

    // Function to load course data from the CSV file into the map
    void LoadData(map<string, Course>& courses, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            Course course;

            getline(ss, course.courseID, ',');
            getline(ss, course.courseTitle, ',');

            while (getline(ss, token, ',')) {
                course.prerequisites.push_back(token);
            }

            courses[course.courseID] = course;
        }

        file.close();
        cout << "Data loaded successfully from " << filename << endl;
    }

    // Function to print all courses in alphanumeric order
    void PrintCourseList(const map<string, Course>& courses) {
        vector<string> sortedCourseIDs;

        for (const auto& pair : courses) {
            sortedCourseIDs.push_back(pair.first);
        }

        sort(sortedCourseIDs.begin(), sortedCourseIDs.end());

        for (const auto& courseID : sortedCourseIDs) {
            cout << courseID << ": " << courses.at(courseID).courseTitle << endl;
        }
    }

    // Function to print course information and its prerequisites
    void PrintCourseInfo(const map<string, Course>& courses, const string& courseID) {
        auto it = courses.find(courseID);
        if (it != courses.end()) {
            const Course& course = it->second;
            cout << "Course ID: " << course.courseID << endl;
            cout << "Course Title: " << course.courseTitle << endl;
            cout << "Prerequisites: ";
            if (course.prerequisites.empty()) {
                cout << "None";
            }
            else {
                for (const auto& prereq : course.prerequisites) {
                    cout << prereq << " ";
                }
            }
            cout << endl;
        }
        else {
            cerr << "Error: Course ID " << courseID << " not found." << endl;
        }
    }

    // Function to display the menu and handle user choices
    void DisplayMenu(map<string, Course>& courses) {
        int choice;
        string filename;
        string courseID;

        do {
            cout << "\nMenu Options:\n";
            cout << "1. Load Data\n";
            cout << "2. Print Course List\n";
            cout << "3. Print Course Information\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter the filename: ";
                cin >> filename;
                LoadData(courses, filename);
                break;

            case 2:
                PrintCourseList(courses);
                break;

            case 3:
                cout << "Enter the course ID: ";
                cin >> courseID;
                PrintCourseInfo(courses, courseID);
                break;

            case 9:
                cout << "Exiting the program." << endl;
                break;

            default:
                cerr << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 9);
    }

} // namespace AdvisingSystem

int main() {
    map<string, AdvisingSystem::Course> courses;

    AdvisingSystem::DisplayMenu(courses);

    return 0;
}
