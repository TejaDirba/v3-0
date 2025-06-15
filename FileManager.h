#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "Student.h"
#include <string>
#include <list>

class FileManager {
public:
    static Vec<Student> readStudentsFromFile(const std::string& fn);
    static void writeResultsToFile(const Vec<Student>& v,const std::string& fn);
    static void splitAndWrite(const Vec<Student>& v,const std::string& base);
};
#endif
