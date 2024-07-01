#include <bits/stdc++.h>
#include <conio.h>
#include <fstream>

using namespace std;

// Base class Person
class Person {
protected:
    string name;
    int id;
    string password;

public:
    Person(string n = "", int i = 0, string p = "") : name(n), id(i), password(p) {}

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    bool verifyPassword(const string& pass) const {
        return password == pass;
    }

    virtual void displayInfo() const = 0; // Pure virtual function for displaying info
};

// Derived class Student
class Student : public Person {
private:
    int age;

public:
    Student(string n = "", int a = 0, int i = 0, string p = "") : Person(n, i, p), age(a) {}

    int getAge() const {
        return age;
    }

    void displayInfo() const override {
        cout << "Student Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }

    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
};

// Overload stream operators for Student
ostream& operator<<(ostream& os, const Student& s) {
    os << s.name << " " << s.age << " " << s.id << " " << s.password;
    return os;
}

istream& operator>>(istream& is, Student& s) {
    is >> s.name >> s.age >> s.id >> s.password;
    return is;
}

// Derived class Faculty
class Faculty : public Person {
private:
    string department;

public:
    Faculty(string n = "", string d = "", int i = 0, string p = "") : Person(n, i, p), department(d) {}

    string getDepartment() const {
        return department;
    }

    void displayInfo() const override {
        cout << "Faculty Name: " << name << ", Department: " << department << ", ID: " << id << endl;
    }

    friend ostream& operator<<(ostream& os, const Faculty& f);
    friend istream& operator>>(istream& is, Faculty& f);
};

// Overload stream operators for Faculty
ostream& operator<<(ostream& os, const Faculty& f) {
    os << f.name << " " << f.department << " " << f.id << " " << f.password;
    return os;
}

istream& operator>>(istream& is, Faculty& f) {
    is >> f.name >> f.department >> f.id >> f.password;
    return is;
}

// Course class managed by BST
class Course {
public:
    string title;
    int code;
    int credits;
    Course* left;
    Course* right;

    Course(string t = "", int c = 0, int cr = 0) : title(t), code(c), credits(cr), left(nullptr), right(nullptr) {}

    void displayInfo() const {
        cout << "Course Title: " << title << ", Code: " << code << ", Credits: " << credits << endl;
    }

    friend ostream& operator<<(ostream& os, const Course& c);
    friend istream& operator>>(istream& is, Course& c);
};

// Overload stream operators for Course
ostream& operator<<(ostream& os, const Course& c) {
    os << c.title << " " << c.code << " " << c.credits;
    return os;
}

istream& operator>>(istream& is, Course& c) {
    is >> c.title >> c.code >> c.credits;
    return is;
}

// Binary Search Tree for Course Management
class CourseBST {
private:
    Course* root;

    void insert(Course*& node, const string& title, int code, int credits) {
        if (!node) {
            node = new Course(title, code, credits);
        } else if (code < node->code) {
            insert(node->left, title, code, credits);
        } else {
            insert(node->right, title, code, credits);
        }
    }

    void inorder(Course* node) const {
        if (node) {
            inorder(node->left);
            node->displayInfo();
            inorder(node->right);
        }
    }

    Course* search(Course* node, int code) const {
        if (!node || node->code == code) {
            return node;
        }
        if (code < node->code) {
            return search(node->left, code);
        }
        return search(node->right, code);
    }

    void destroyTree(Course* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void saveInOrder(Course* node, ofstream& file) const {
        if (node) {
            saveInOrder(node->left, file);
            file << *node << endl;
            saveInOrder(node->right, file);
        }
    }

public:
    CourseBST() : root(nullptr) {}

    ~CourseBST() {
        destroyTree(root);
    }

    void insert(const string& title, int code, int credits) {
        insert(root, title, code, credits);
    }

    void inorder() const {
        inorder(root);
    }

    Course* search(int code) const {
        return search(root, code);
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            saveInOrder(root, file);
            file.close();
        } else {
            cout << "Unable to open file for saving courses." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string title;
            int code, credits;
            while (file >> title >> code >> credits) {
                insert(title, code, credits);
            }
            file.close();
        } else {
            cout << "Unable to open file for loading courses." << endl;
        }
    }
};

// Enrollment class
class Enrollment {
private:
    int studentId;
    int courseCode;

public:
    Enrollment(int sid = 0, int cc = 0) : studentId(sid), courseCode(cc) {}

    int getStudentId() const {
        return studentId;
    }

    int getCourseCode() const {
        return courseCode;
    }

    void displayInfo() const {
        cout << "Student ID: " << studentId << ", Course Code: " << courseCode << endl;
    }

    friend ostream& operator<<(ostream& os, const Enrollment& e);
    friend istream& operator>>(istream& is, Enrollment& e);
};

// Overload stream operators for Enrollment
ostream& operator<<(ostream& os, const Enrollment& e) {
    os << e.studentId << " " << e.courseCode;
    return os;
}

istream& operator>>(istream& is, Enrollment& e) {
    is >> e.studentId >> e.courseCode;
    return is;
}

// Global variables for storing data
vector<Student> students;
vector<Faculty> faculties;
CourseBST courseTree;
vector<Enrollment> enrollments;

// Function prototypes
string inputPassword();
void startMenu();
void adminLogin();
void studentLogin();
void facultyLogin();
void adminMenu();
void studentMenu();
void facultyMenu();
void addStudent();
void addCourse();
void addFaculty();
void enrollStudent();
void viewStudents();
void viewCourses();
void viewEnrollments();
void viewFaculties();
void saveData();
void loadData();

// Password input function
string inputPassword() {
    char pass[31];
    string passStr = "";
    int i = 0;
    while (true) {
        char ch = getch();
        if (ch == 8) { // Backspace
            if (i != 0) {
                pass[i] = '\0';
                i--;
            }
        } else if (i == 29 || ch == '\r') { // Enter
            pass[i] = '\0';
            break;
        } else if (ch >= 32 && ch <= 126) {
            pass[i] = ch;
            i++;
        }
    }
    for (int j = 0; pass[j] != '\0'; j++) {
        passStr.push_back(pass[j]);
    }
    return passStr;
}

// Admin login function
void adminLogin() {
    string adminPass;
    cout << "Enter Admin Password: ";
    adminPass = inputPassword();

    if (adminPass == "admin123") {
        adminMenu();
    } else {
        cout << "Admin login failed. Incorrect password.\n";
    }
}

// Student login function
void studentLogin() {
    int studentId;
    string studentPass;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Student Password: ";
    studentPass = inputPassword();

    for (const auto& student : students) {
        if (student.getId() == studentId && student.verifyPassword(studentPass)) {
            studentMenu();
            return;
        }
    }
    cout << "Student login failed. Incorrect ID or password.\n";
}

// Faculty login function
void facultyLogin() {
    int facultyId;
    string facultyPass;
    cout << "Enter Faculty ID: ";
    cin >> facultyId;
    cout << "Enter Faculty Password: ";
    facultyPass = inputPassword();

    for (const auto& faculty : faculties) {
        if (faculty.getId() == facultyId && faculty.verifyPassword(facultyPass)) {
            facultyMenu();
            return;
        }
    }
    cout << "Faculty login failed. Incorrect ID or password.\n";
}

// Admin menu function
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Add Faculty\n";
        cout << "3. Add Course\n";
        cout << "4. View Students\n";
        cout << "5. View Faculties\n";
        cout << "6. View Courses\n";
        cout << "7. View Enrollments\n";
        cout << "8. Save Data\n";
        cout << "9. Load Data\n";
        cout << "10. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: addFaculty(); break;
            case 3: addCourse(); break;
            case 4: viewStudents(); break;
            case 5: viewFaculties(); break;
            case 6: viewCourses(); break;
            case 7: viewEnrollments(); break;
            case 8: saveData(); break;
            case 9: loadData(); break;
            case 10: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);
}

// Student menu function
void studentMenu() {
    int choice;
    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View Courses\n";
        cout << "2. Enroll in Course\n";
        cout << "3. View Enrollments\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewCourses(); break;
            case 2: enrollStudent(); break;
            case 3: viewEnrollments(); break;
            case 4: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Faculty menu function
void facultyMenu() {
    int choice;
    do {
        cout << "\n--- Faculty Menu ---\n";
        cout << "1. View Courses\n";
        cout << "2. View Enrollments\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewCourses(); break;
            case 2: viewEnrollments(); break;
            case 3: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Function to add a new student
void addStudent() {
    string name, password;
    int age, id;

    cout << "Enter Student Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    password = inputPassword();

    students.emplace_back(name, age, id, password);
    cout << "Student added successfully.\n";
}

// Function to add a new faculty
void addFaculty() {
    string name, department, password;
    int id;

    cout << "Enter Faculty Name: ";
    cin >> name;
    cout << "Enter Department: ";
    cin >> department;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    password = inputPassword();

    faculties.emplace_back(name, department, id, password);
    cout << "Faculty added successfully.\n";
}

// Function to add a new course
void addCourse() {
    string title;
    int code, credits;

    cout << "Enter Course Title: ";
    cin >> title;
    cout << "Enter Course Code: ";
    cin >> code;
    cout << "Enter Credits: ";
    cin >> credits;

    courseTree.insert(title, code, credits);
    cout << "Course added successfully.\n";
}

// Function to enroll a student in a course
void enrollStudent() {
    int studentId, courseCode;

    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Course Code: ";
    cin >> courseCode;

    enrollments.emplace_back(studentId, courseCode);
    cout << "Student enrolled successfully.\n";
}

// Function to view all students
void viewStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }
    for (const auto& student : students) {
        student.displayInfo();
    }
}

// Function to view all faculties
void viewFaculties() {
    if (faculties.empty()) {
        cout << "No faculties found.\n";
        return;
    }
    for (const auto& faculty : faculties) {
        faculty.displayInfo();
    }
}

// Function to view all courses
void viewCourses() {
    courseTree.inorder();
}

// Function to view all enrollments
void viewEnrollments() {
    if (enrollments.empty()) {
        cout << "No enrollments found.\n";
        return;
    }
    for (const auto& enrollment : enrollments) {
        enrollment.displayInfo();
    }
}

// Function to save data to files
void saveData() {
    ofstream studentFile("students.txt");
    for (const auto& student : students) {
        studentFile << student << endl;
    }
    studentFile.close();

    ofstream facultyFile("faculties.txt");
    for (const auto& faculty : faculties) {
        facultyFile << faculty << endl;
    }
    facultyFile.close();

    courseTree.saveToFile("courses.txt");

    ofstream enrollmentFile("enrollments.txt");
    for (const auto& enrollment : enrollments) {
        enrollmentFile << enrollment << endl;
    }
    enrollmentFile.close();

    cout << "Data saved successfully.\n";
}

// Function to load data from files
void loadData() {
    ifstream studentFile("students.txt");
    if (studentFile.is_open()) {
        Student s;
        while (studentFile >> s) {
            students.push_back(s);
        }
        studentFile.close();
    }

    ifstream facultyFile("faculties.txt");
    if (facultyFile.is_open()) {
        Faculty f;
        while (facultyFile >> f) {
            faculties.push_back(f);
        }
        facultyFile.close();
    }

    courseTree.loadFromFile("courses.txt");

    ifstream enrollmentFile("enrollments.txt");
    if (enrollmentFile.is_open()) {
        Enrollment e;
        while (enrollmentFile >> e) {
            enrollments.push_back(e);
        }
        enrollmentFile.close();
    }

    cout << "Data loaded successfully.\n";
}

// Start menu function
void startMenu() {
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Faculty Login\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: studentLogin(); break;
            case 3: facultyLogin(); break;
            case 4: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

int main() {
    // Load data from files on startup
    loadData();

    // Start the main menu
    startMenu();

    // Save data to files on exit
    saveData();

    return 0;
}
