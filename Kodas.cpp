#include "FileManager.h"
#include <iostream>
#include <chrono>

#ifdef USE_STD
  #include <vector>
  template<typename T> using Vec = std::vector<T>;
#else
  #include "../include/Vector.h"
  template<typename T> using Vec = Vector<T>;
#endif

using Clock = std::chrono::high_resolution_clock;

void printMenu(){
    std::cout<<"
=== STUDENT SYSTEM  ===
"
             <<"1) Interactive"
             <<"2) Batch"
             <<"3) Generuoti testus"
             <<"4) Baigti"
             <<"Pasirinkimas: ";
}

int ask(int lo,int hi){
    int x;
    while(!(std::cin>>x) || x<lo||x>hi){
        std::cin.clear(); std::cin.ignore(1e6,'
');
        std::cout<<"Neinka, bandykite is naujp: ";
    }
    return x;
}

std::string askFile(){
    std::cout<<"Failo pavadinimas: "; std::string s; std::cin>>s; return s;
}

template<typename C>
void runInteractive(int strat,const std::string& fn){
    C cont = FileManager::readStudentsFromFile(fn);
    auto t1 = Clock::now();
    std::sort(cont.begin(), cont.end(),[](auto&a,auto&b){return a.getVardas()<b.getVardas();});
    std::cout<<"Sort: "<<std::chrono::duration_cast<std::chrono::microseconds>(Clock::now()-t1).count()<<" us
";
    if(strat==1) FileManager::splitAndWrite(cont, fn);
    else         FileManager::writeResultsToFile(cont, fn + "_out.txt");
}

void runBatch(){
    for(auto fn: {"test_1000.txt","test_10000.txt","test_100000.txt"}){
        try{ runInteractive<Vec<Student>>(1, fn); }
        catch(...) { std::cout<<"Error "<<fn<<"
"; }
    }
}

int main(){
    while(true){ printMenu(); switch(ask(1,4)){
        case 1:{ int strat=ask(1,2); runInteractive<Vec<Student>>(strat, askFile()); break; }
        case 2: runBatch(); break;
        case 3: FileManager::generateTestFiles(); break;
        case 4: return 0;
    }}
}
