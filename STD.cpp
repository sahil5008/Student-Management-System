#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
private:
    int id;
    char name[50];
    int age;
    char course[50];

public:
    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        cin.getline(course, 50);
    }

    void display() const {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nAge: " << age
             << "\nCourse: " << course << endl;
    }

    int getID() const {
        return id;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

// Display All Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Update Student
void updateStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            cout << "Enter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Delete Student
void deleteStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found.\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}