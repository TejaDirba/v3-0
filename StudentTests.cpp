#include <gtest/gtest.h>
#include "../src/Student.h"

TEST(StudentTests, CopyMoveIO) {
    Student a("Jonas","Jonaitis");
    a.setNd({9,8,7}); a.setEgzaminas(10);
    a.calculateFinalGrades();
    Student b(a);
    EXPECT_EQ(b.getVardas(),"Jonas");
    Student c(std::move(b));
    EXPECT_EQ(c.getPavarde(),"Jonaitis");
    Student d;
    d = a;
    EXPECT_EQ(d.getEgzaminas(),10);
    Student e;
    e = std::move(d);
    EXPECT_GT(e.getGalutinisVid(),0);

    std::stringstream ss;
    ss << c;
    Student f;
    ss >> f;
    EXPECT_EQ(f.getVardas(),c.getVardas());
}

int main(int argc,char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
