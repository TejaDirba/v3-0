# Studentų Pažymių Sistema v3.0

## Naujos v3.0 užduotys
1. Tarp `Vector<T>` ir `std::vector<T>` perjungimas naudojant kompilatoriaus flagą `-DUSE_STD`
2. `Vector<T>` turi padengti ne mažiau kaip 80% `std::vector` funkcionalumo (žr. pavyzdžius)
3. GoogleTest vienetinių testų rinkinys `Vector` ir esamiems klasėms
4. Atlikti greičio matavimus: užpildyti 10 000→100 000 000 elementų, matuoti laiką (μs) ir perskirstymų skaičių
5. Vietoj `std::vector<Student>` naudoti `Vector<Student>` ir patikrinti programos veikimą
6. Doxygen dokumentacija visiems header’iams
7. Windows diegimo paketo (`Setup.exe`) šablonas kataloge `installer/`

## 80% funkcijų pavyzdžiai
Vector<int> v1;            // konstruktorius
v1.push_back(42);          // pridėjimas
v1.reserve(100);           // vietos rezervavimas
int x = v1[0];             // operatorius[]
v1.pop_back();             // šalinimas iš galo
for(auto& e : v1) { }      // iteratorių naudojimas

make             # sukompiliuoja pagr. programą
make bench       # vykdo spartinį testą su std::vector
make test-std    # vienetiniai testai su std::vector
make test-vec    # vienetiniai testai su Vector<T>

doxygen docs/Doxyfile
# atidaryti html/index.html arba sugeneruotą PDF docs/latex kataloge

Diegimo scenarijus installer/ kataloge sugeneruoja Setup.exe:
# pvz. makensis installer/script.nsi
