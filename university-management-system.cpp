#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    string rollNo, name, subject, address;

    void inputStudent() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Subject: ";
        getline(cin, subject);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void displayStudent() {
        cout << "Roll No: " << rollNo << "\nName: " << name << "\nSubject: " << subject << "\nAddress: " << address << endl;
    }

    string toFileFormat() {
        return rollNo + "," + name + "," + subject + "," + address + "\n";
    }

    void fromFileFormat(string data) {
        size_t pos1 = data.find(",");
        size_t pos2 = data.find(",", pos1 + 1);
        size_t pos3 = data.find(",", pos2 + 1);

        rollNo = data.substr(0, pos1);
        name = data.substr(pos1 + 1, pos2 - pos1 - 1);
        subject = data.substr(pos2 + 1, pos3 - pos2 - 1);
        address = data.substr(pos3 + 1);
    }
};

void saveStudentToFile(Student &s) {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << s.toFileFormat();
        file.close();
        cout << "Student added successfully!\n";
    } else {
        cout << "Error saving student data!\n";
    }
}

void searchStudent(string roll) {
    ifstream file("students.txt");
    string line;
    bool found = false;
    Student s;

    if (file.is_open()) {
        while (getline(file, line)) {
            s.fromFileFormat(line);
            if (s.rollNo == roll) {
                cout << "Student Found:\n";
                s.displayStudent();
                found = true;
                break;
            }
        }
        file.close();
        if (!found) cout << "Student not found!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

void updateStudent(string roll) {
    ifstream file("students.txt");
    vector<Student> students;
    string line;
    bool found = false;
    Student s;

    if (file.is_open()) {
        while (getline(file, line)) {
            s.fromFileFormat(line);
            if (s.rollNo == roll) {
                cout << "Enter new details:\n";
                s.inputStudent();
                found = true;
            }
            students.push_back(s);
        }
        file.close();
    } else {
        cout << "Error opening file!\n";
        return;
    }

    if (!found) {
        cout << "Student not found!\n";
        return;
    }

    // Traditional for loop (C++98 Compatible)
    ofstream outFile("students.txt");
    for (size_t i = 0; i < students.size(); i++) {
        outFile << students[i].toFileFormat();
    }
    outFile.close();

    cout << "Student updated successfully!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\nUniversity Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            s.inputStudent();
            saveStudentToFile(s);
        } else if (choice == 2) {
            string roll;
            cout << "Enter Roll No to Search: ";
            cin >> roll;
            searchStudent(roll);
        } else if (choice == 3) {
            string roll;
            cout << "Enter Roll No to Update: ";
            cin >> roll;
            updateStudent(roll);
        } else if (choice == 4) {
            cout << "Exiting program...\nGood Luck!\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}

