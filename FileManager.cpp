#include "FileManager.h"
#include <fstream>
#include <iostream>

Vec<Student> FileManager::readStudentsFromFile(const std::string& fn){
    Vec<Student> out;
    std::ifstream f(fn);
    Student s;
    while(f>>s){ s.calculateFinalGrades(); out.push_back(std::move(s)); }
    return out;
}

void FileManager::writeResultsToFile(const Vec<Student>& v,const std::string& fn){
    std::ofstream o(fn);
    for(auto& s:v) o<<s<<"
";
}

void FileManager::splitAndWrite(const Vec<Student>& v,const std::string& base){
    Vec<Student> pass,fail;
    for(auto& s:v)
        if(s.getGalutinisVid()<5) fail.push_back(s);
        else pass.push_back(s);
    writeResultsToFile(fail, base + "_fail.txt");
    writeResultsToFile(pass, base + "_pass.txt");
}
