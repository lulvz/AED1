//
// Created by lulas on 10/15/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "./uc_turma.h"
#include "./class_schedule.h"
#include "./student.h"
#include "./schedule_manag.h"

#include "utility/csv_reader.h"

#include "utility/bst.h"
#include "student.h"

#define CLASS_UC_FILE "../schedule/classes_per_uc.csv"
#define CLASS_SCHEDULE_FILE "../schedule/classes.csv"
#define STUDENT_FILE "../schedule/students_classes.csv"

#define CLASS_LIMIT_STUDENTS 30

using namespace std;

int main() {
    
    // create schedule manager
    ScheduleManag sm(CLASS_UC_FILE, CLASS_SCHEDULE_FILE, STUDENT_FILE);

    // read files
    sm.readFiles();

    Student student = Student("202020302", "Carolina");
    
    //get the set of students
    set<Student> s = sm.getStudentsSet();

    // print s
    for (auto it = s.begin(); it != s.end(); it++) {
        cout << *it << endl;
    }

    // find carolina in the set
    auto it = s.find(student);
    if (it != s.end()) {
        cout << "Carolina found" << endl;
    } else {
        cout << "Carolina not found" << endl;
    }

    // get the vector of ucts of carolina
    vector<UCTurma> ucts = sm.getStudentsSet().find(student)->classes;

    // print ucts
    for (auto it = ucts.begin(); it != ucts.end(); it++) {
        cout << it->uc << " " << it->turma << endl;
    }
    
    return 0;
}