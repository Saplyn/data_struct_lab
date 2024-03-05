#pragma once

// at Least Usable Shell ;)
// don't judge me plz i put together this and it's working anyway

#include <iostream>

#include "list.h"
#include "vec.h"

namespace lyn {

//~ Data Model

struct Stu {
    std::string id;
    std::string name;
    double grade;
};

std::ostream& operator<< (std::ostream& s, const Stu& stu) {
    return s << "Student (\""
             << stu.id << "\", \""
             << stu.name << "\", "
             << stu.grade << ")";
}

//~ Main Implementation

enum ImplArg {
    ImplVec,
    ImplList
};

template<ImplArg impl>
int impl_fn();

template<>
int impl_fn<ImplArg::ImplVec>() {
    lyn::Vec<Stu> vec;

    std::string cmd;
    std::string arg;
    while (true) {
        std::cout << "\nlush> ";
        std::getline(std::cin, cmd);
        cmd = cmd.substr(0, cmd.find('\n'));
        if (cmd.empty()) {
            continue;
        }

        if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd == "add") {
            Stu stu;
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.id = arg;
            std::cout << "Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.name = arg;
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.grade = std::stod(arg);
            vec.push_back(stu);
        } else if (cmd == "del" || cmd == "del-id") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            vec.remove_all([arg](const Stu& stu) -> bool { return stu.id == arg; });
        } else if (cmd == "set") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::Vec<Stu*> res = vec.find_all_loc([arg](const Stu& stu) -> bool { return stu.id == arg; });
            for (Stu* stu : res) {
                std::cout << stu << std::endl;
                std::cout << "New ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->id = arg;
                std::cout << "New Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->name = arg;
                std::cout << "New Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->grade = std::stod(arg);
            }
        } else if (cmd == "ls") {
            for (const Stu& stu : vec) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find" || cmd == "find-id") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::Vec<Stu> res = vec.find_all([arg](const Stu& stu) -> bool { return stu.id == arg; });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-name") {
            std::cout << "Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::Vec<Stu> res = vec.find_all([arg](const Stu& stu) -> bool { return stu.name == arg; });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-grade" || cmd == "find-grade-over") {
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::Vec<Stu> res = vec.find_all([arg](const Stu& stu) -> bool { return stu.grade >= std::stod(arg); });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-grade-below") {
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::Vec<Stu> res = vec.find_all([arg](const Stu& stu) -> bool { return stu.grade < std::stod(arg); });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else {
            std::cout << "Unkown command." << std::endl;
            std::cout << "add              add a student..." << std::endl;
            std::cout << "del              delete a student by ID..." << std::endl;
            std::cout << "del-id           delete a student by ID..." << std::endl;
            std::cout << "set              set a student..." << std::endl;
            std::cout << "ls               list all students" << std::endl;
            std::cout << "find             find a student by ID..." << std::endl;
            std::cout << "find-id          find a student by ID..." << std::endl;
            std::cout << "find-name        find a student by name..." << std::endl;
            std::cout << "find-grade       find a student with grade over..." << std::endl;
            std::cout << "find-grade-over  find a student with grade over..." << std::endl;
            std::cout << "find-grade-below find a student with grade below..." << std::endl;
        }
    }

    return 0;
}

template<>
int impl_fn<ImplArg::ImplList>() {
    lyn::List<Stu> list;

    std::string cmd;
    std::string arg;
    while (true) {
        std::cout << "\nlush> ";
        std::getline(std::cin, cmd);
        cmd = cmd.substr(0, cmd.find('\n'));
        if (cmd.empty()) {
            continue;
        }

        if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd == "add") {
            Stu stu;
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.id = arg;
            std::cout << "Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.name = arg;
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu.grade = std::stod(arg);
            list.push_front(stu);
        } else if (cmd == "del" || cmd == "del-id") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            list.remove_all([arg](const Stu& stu) -> bool { return stu.id == arg; });
        } else if (cmd == "set") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::List<Stu*> res = list.find_all_loc([arg](const Stu& stu) -> bool { return stu.id == arg; });
            for (Stu* stu : res) {
                std::cout << stu << std::endl;
                std::cout << "New ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->id = arg;
                std::cout << "New Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->name = arg;
                std::cout << "New Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n')); stu->grade = std::stod(arg);
            }
        } else if (cmd == "ls") {
            for (const Stu& stu : list) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find" || cmd == "find-id") {
            std::cout << "ID: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::List<Stu> res = list.find_all([arg](const Stu& stu) -> bool { return stu.id == arg; });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-name") {
            std::cout << "Name: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::List<Stu> res = list.find_all([arg](const Stu& stu) -> bool { return stu.name == arg; });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-grade" || cmd == "find-grade-over") {
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::List<Stu> res = list.find_all([arg](const Stu& stu) -> bool { return stu.grade >= std::stod(arg); });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else if (cmd == "find-grade-below") {
            std::cout << "Grade: "; std::getline(std::cin, arg); arg = arg.substr(0, arg.find('\n'));
            lyn::List<Stu> res = list.find_all([arg](const Stu& stu) -> bool { return stu.grade < std::stod(arg); });
            for (const Stu& stu : res) {
                std::cout << stu << std::endl;
            }
        } else {
            std::cout << "Unkown command." << std::endl;
            std::cout << "add              add a student..." << std::endl;
            std::cout << "del              delete a student by ID..." << std::endl;
            std::cout << "del-id           delete a student by ID..." << std::endl;
            std::cout << "set              set a student..." << std::endl;
            std::cout << "ls               list all students" << std::endl;
            std::cout << "find             find a student by ID..." << std::endl;
            std::cout << "find-id          find a student by ID..." << std::endl;
            std::cout << "find-name        find a student by name..." << std::endl;
            std::cout << "find-grade       find a student with grade over..." << std::endl;
            std::cout << "find-grade-over  find a student with grade over..." << std::endl;
            std::cout << "find-grade-below find a student with grade below..." << std::endl;
        }
    }

    return 0;
}

}

/*

*/
