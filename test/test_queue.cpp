#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "queue.h" 
#include <random>

template <typename T>
class QUEUETest : public ::testing::Test {
protected:
    QUEUE<string> queue_sec;  
    QUEUE<int> queue_fir;  
};

typedef QUEUETest<int> queue_int;
typedef QUEUETest<string> queue_str;

TEST_F(queue_int, PUSH_WITH_RANDOM_OPERATIONS) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10000); 

    EXPECT_TRUE(queue_fir.is_empty());  

    for (int i = 0; i < 10; ++i) {
        int random_value = dist(gen);  
        queue_fir.push((random_value));
    }

    EXPECT_FALSE(queue_fir.is_empty());  

    EXPECT_EQ(queue_fir.size(), 10);  
    EXPECT_GE(queue_fir.front(), 10);  


    for (size_t i = 0; i < 10; ++i) {
        queue_fir.pop();
        queue_fir.print();
    }

    queue_fir.print();

    EXPECT_TRUE(queue_fir.is_empty());

    EXPECT_EQ(queue_fir.size(), 0);
}                                                

TEST_F(queue_str, PUSH_WITH_RANDOM_OPERATIONS) {

    EXPECT_TRUE(queue_sec.is_empty());  

    string words[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon"};
    for (const string& word : words) {
        queue_sec.push(word);
    }

    queue_sec.print();
    
    EXPECT_FALSE(queue_sec.is_empty());  
    EXPECT_EQ(queue_sec.size(), 10);  

    for (size_t i = 0; i < 10; ++i) {
        queue_sec.pop();
    }


    EXPECT_TRUE(queue_sec.is_empty());
    EXPECT_EQ(queue_sec.size(), 0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}