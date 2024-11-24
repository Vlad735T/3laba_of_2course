#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fbt.h" 

TEST(FBT_test, Constructor) {
    FBT tree(1);
    
    EXPECT_EQ(tree.findPlace(1)->key, 1);
}


TEST(FBT_test, AddNode) {
    FBT tree(1); 
    tree.Add(2);
    tree.Add(3);

    EXPECT_EQ(tree.findPlace(2)->key, 2);
    EXPECT_EQ(tree.findPlace(3)->key, 3);
}

TEST(FBT_test, isFull) {
    FBT tree(1);
    tree.Add(2);
    tree.Add(3);


    EXPECT_TRUE(tree.isFull());
}

TEST(FBT_test, notFull) {
    FBT tree(1);
    tree.Add(2);
    tree.Add(3);
    tree.Add(4);

    EXPECT_FALSE(tree.isFull());
}

TEST(FBT_test, findNode) {
    FBT tree(1);
    tree.Add(2);
    tree.Add(3);

    EXPECT_EQ(tree.findPlace(1)->key, 1);
    EXPECT_EQ(tree.findPlace(2)->key, 2);
    EXPECT_EQ(tree.findPlace(3)->key, 3);

    EXPECT_THROW(tree.findPlace(4), runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}