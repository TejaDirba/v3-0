#ifndef STUDENT_H
#define STUDENT_H
#include "Zmogus.h"
#include <iostream>
#ifdef USE_STD
  #include <vector>
  template<typename T> using Vec = std::vector<T>;
#else
  #include "../include/Vector.h"
  template<typename T> using Vec = Vector<T>;
#endif

class Student : public Zmogus {
private:
    Vec<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
public:
    Student();
    Student(const std::string& v, const std::string& p);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;
    ~Student() override;
    Vec<int> getNd() const;
    int getEgzaminas() const;
    double getGalutinisVid() const;
    double getGalutinisMed() const;
    void setNd(const Vec<int>& grades);
    void setEgzaminas(int e);
    void addHomeworkGrade(int grade);
    void calculateFinalGrades();
    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
#endif
