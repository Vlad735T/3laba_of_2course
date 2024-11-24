#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "stack.h" 

template <typename T>
class StackTest : public ::testing::Test {
protected:
    Stack<string> list_fir;  
    Stack<int> list_sec;  
};

typedef StackTest<int> stack_int;
typedef StackTest<string> stack_str;

TEST_F(stack_int, PUSH_WITH_OTHER_OPERATION) { 
    list_sec.push(4213);
    list_sec.push(568);
    list_sec.push(4569);
    list_sec.push(2457);
    list_sec.push(679);
    list_sec.push(134);
    list_sec.push(468);
    list_sec.push(4213);
    list_sec.push(67505);
    list_sec.push(436724);
    list_sec.push(4357);

    list_sec.print();
    
    EXPECT_EQ(list_sec.size(), 11);
    EXPECT_EQ(list_sec.top(), 4357);

    list_sec.pop();
    list_sec.pop();
    list_sec.pop();
    list_sec.pop();

    EXPECT_EQ(list_sec.size(), 7);
    EXPECT_EQ(list_sec.top(), 468);
}                                                     

TEST_F(stack_str, POP_WITH_OTHER_OPERATION) {
    list_fir.push("mixer");
    list_fir.push("clock");
    list_fir.push("toaster");
    list_fir.push("blender");
    list_fir.push("flashlight");
    list_fir.push("dishwasher");
    list_fir.push("microwave");
    list_fir.push("TV");

    EXPECT_EQ(list_fir.size(), 8);
    EXPECT_STREQ(list_fir.top().c_str(), "TV");

    list_fir.pop();

    EXPECT_EQ(list_fir.size(), 7);
    EXPECT_STREQ(list_fir.top().c_str(), "microwave");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}