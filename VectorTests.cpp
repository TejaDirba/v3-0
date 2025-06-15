#include <gtest/gtest.h>
#include "../include/Vector.h"

TEST(VectorBasics, PushPopAt) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(),2);
    EXPECT_EQ(v[0],1);
    EXPECT_EQ(v.at(1),2);
    v.pop_back();
    EXPECT_EQ(v.size(),1);
    EXPECT_EQ(v.back(),1);
}

TEST(VectorCapacity, Reserve) {
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(),100);
    EXPECT_EQ(v.size(),0);
}

TEST(VectorCopyMove, Assign) {
    Vector<int> a = {1,2,3};
    Vector<int> b(a);
    EXPECT_EQ(b.size(),3);
    Vector<int> c(std::move(b));
    EXPECT_EQ(c.size(),3);
}

int main(int argc,char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
