#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class Subject {
private:
    std::string name;
    int code;
    int credit;

public:
    Subject(string name, int code, int credit) : name(name), code(code), credit(credit) {}
    Subject() : code(0), credit(0) {}

    string getName() const {
        return name;
    }

    int getCode() const {
        return code;
    }

    int getCredit() const {
        return credit;
    }
};

class ManagerGrade {
private:
    float gradeList[2][10];
    float average = 0;
    int cantGrade = 0;

public:
    ManagerGrade() {
        // managerGrade is created
    }

    void insertGrade(float subjectId, float grade) {
        gradeList[0][cantGrade] = subjectId;
        gradeList[1][cantGrade] = grade;
        cantGrade++;
    }

    void setGrade(int index, float grade) {
        gradeList[1][index] = grade;
    }

    const float* getGradeList() const {
        return &gradeList[0][0];
    }

    int getCantGrade() const {
        return cantGrade;
    }

    void GradeMatrix() const {
        cout << "Class Code  " << "Grade" << endl;
        for (int i = 0; i < cantGrade; i++) {
            for (int j = 0; j < 2; j++) {
                cout << "  " << gradeList[j][i] << "      ";
            }
            cout << endl;
        }
    }

    float getAverage() {
        for (int i = 0; i < cantGrade; i++) {
            average += gradeList[1][i];
        }
        return average / cantGrade;
    }

    int findSubjectIndex(int classCode) const {
        for (int i = 0; i < cantGrade; i++) {
            if (gradeList[0][i] == classCode) {
                return i;
            }
        }
        return -1;
    }
};

class Student {
private:
    vector<Subject*> subjects;
public:
    void enrollSubject(Subject *subject) {
        subjects.push_back(subject);
    }

    bool isSubjectEnrolled(int subjectCode) const {
        for (const auto& subject : subjects) {
            if (subject->getCode() == subjectCode) {
                return true;
            }
        }
        return false;
    }

    void modifyOrInsertGrade(ManagerGrade &managerGrade, int subjectCode, float grade) {
        if (isSubjectEnrolled(subjectCode)) {
            int index = managerGrade.findSubjectIndex(subjectCode);
            if (index != -1) {
                // Modify the grade if the subject is already in the matrix
                managerGrade.setGrade(index, grade);
            } else {
                // If the subject is not present, add it along with the grade
                managerGrade.insertGrade(subjectCode, grade);
            }
        } else {
            cout << "Subject not enrolled. Cannot set grade." << endl;
        }
    }

    void displayGradesMatrix(ManagerGrade &managerGrade) const {
        managerGrade.GradeMatrix();
    }
};



int main (){

    ManagerGrade manager;
    Student student;


    Subject math("Math", 101, 3);
    Subject physics("Physics", 201, 4);
    Subject english("English", 301, 3);

    student.enrollSubject(&math);
    student.enrollSubject(&physics);
    student.enrollSubject(&english);

    student.modifyOrInsertGrade(manager,101, 90.5);
    student.modifyOrInsertGrade(manager, 201, 85.0);
    student.modifyOrInsertGrade(manager, 301, 92.3);
    student.modifyOrInsertGrade(manager, 201, 95.0);
    student.modifyOrInsertGrade(manager, 201, 15.0);
    student.modifyOrInsertGrade(manager, 401, 15.0);
    student.modifyOrInsertGrade(manager, 301, 92.3);


    student.displayGradesMatrix(manager);

    return 0;
}