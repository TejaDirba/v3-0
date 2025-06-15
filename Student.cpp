#include "Student.h"
#include <numeric>
#include <algorithm>
#include <stdexcept>

Zmogus::Zmogus(const std::string& v, const std::string& p)
    : vardas(v), pavarde(p) {}
std::string Zmogus::getVardas() const { return vardas; }
std::string Zmogus::getPavarde() const { return pavarde; }
void Zmogus::setVardas(const std::string& v) { if(v.empty()) throw std::invalid_argument(""); vardas=v; }
void Zmogus::setPavarde(const std::string& p) { if(p.empty()) throw std::invalid_argument(""); pavarde=p; }

Student::Student() : Zmogus("",""), nd(), egzaminas(0), galutinisVid(0), galutinisMed(0) {}
Student::Student(const std::string& v, const std::string& p)
    : Zmogus(v,p), nd(), egzaminas(0), galutinisVid(0), galutinisMed(0) {}
Student::Student(const Student& o) : Zmogus(o), nd(o.nd), egzaminas(o.egzaminas), galutinisVid(o.galutinisVid), galutinisMed(o.galutinisMed) {}
Student::Student(Student&& o) noexcept : Zmogus(std::move(o)), nd(std::move(o.nd)), egzaminas(o.egzaminas), galutinisVid(o.galutinisVid), galutinisMed(o.galutinisMed) { o.egzaminas=0; o.galutinisVid=o.galutinisMed=0; }
Student& Student::operator=(const Student& o) { if(this!=&o){ setVardas(o.getVardas()); setPavarde(o.getPavarde()); nd=o.nd;egzaminas=o.egzaminas;galutinisVid=o.galutinisVid;galutinisMed=o.galutinisMed;} return *this; }
Student& Student::operator=(Student&& o) noexcept { if(this!=&o){ setVardas(std::move(o.vardas)); setPavarde(std::move(o.pavarde)); nd=std::move(o.nd);egzaminas=o.egzaminas;galutinisVid=o.galutinisVid;galutinisMed=o.galutinisMed; o.egzaminas=0; o.galutinisVid=o.galutinisMed=0;} return *this; }
Student::~Student() = default;

Vec<int> Student::getNd() const { return nd; }
int Student::getEgzaminas() const { return egzaminas; }
double Student::getGalutinisVid() const { return galutinisVid; }
double Student::getGalutinisMed() const { return galutinisMed; }

void Student::setNd(const Vec<int>& g) { nd=g; }
void Student::setEgzaminas(int e) { egzaminas=e; }
void Student::addHomeworkGrade(int grade) { nd.push_back(grade); }
void Student::calculateFinalGrades() {
    double sum=std::accumulate(nd.begin(),nd.end(),0.0);
    galutinisVid=0.4*(sum/nd.size())+0.6*egzaminas;
    auto tmp=nd; std::sort(tmp.begin(),tmp.end());
    size_t n=tmp.size();
    double med=(n%2?tmp[n/2]:(tmp[n/2-1]+tmp[n/2])/2.0);
    galutinisMed=0.4*med+0.6*egzaminas;
}

std::istream& operator>>(std::istream& is, Student& s){ std::string v,p; is>>v>>p; s.setVardas(v);s.setPavarde(p); return is; }
std::ostream& operator<<(std::ostream& os, const Student& s){ os<<s.getPavarde()<<" "<<s.getVardas()<<" "<<s.getGalutinisVid()<<" "<<s.getGalutinisMed(); return os; }
