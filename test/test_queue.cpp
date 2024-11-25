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

TEST_F(queue_int, INT_QUEUE_SEQUENCE_OPERATIONS) {
    EXPECT_TRUE(queue_fir.is_empty());  

    queue_fir.push(10);
    queue_fir.push(20);
    queue_fir.push(30);

    EXPECT_EQ(queue_fir.size(), 3);
    EXPECT_EQ(queue_fir.front(), 10);

    queue_fir.pop();
    EXPECT_EQ(queue_fir.front(), 20);
    EXPECT_EQ(queue_fir.size(), 2);

    queue_fir.pop();
    EXPECT_EQ(queue_fir.front(), 30);
    EXPECT_EQ(queue_fir.size(), 1);

    queue_fir.pop();
    EXPECT_TRUE(queue_fir.is_empty());

    // Проверка исключений
    EXPECT_THROW(queue_fir.pop(), runtime_error);
    EXPECT_THROW(queue_fir.front(), runtime_error);
}


TEST_F(queue_str, STRING_QUEUE_SEQUENCE_OPERATIONS) {
    EXPECT_TRUE(queue_sec.is_empty());  

    // Добавляем строки в очередь
    queue_sec.push("hello");
    queue_sec.push("world");
    queue_sec.push("test");

    EXPECT_EQ(queue_sec.size(), 3);
    EXPECT_EQ(queue_sec.front(), "hello");

    // Удаляем элементы и проверяем
    queue_sec.pop();
    EXPECT_EQ(queue_sec.front(), "world");
    EXPECT_EQ(queue_sec.size(), 2);

    queue_sec.pop();
    EXPECT_EQ(queue_sec.front(), "test");
    EXPECT_EQ(queue_sec.size(), 1);

    queue_sec.pop();
    EXPECT_TRUE(queue_sec.is_empty());

    EXPECT_THROW(queue_sec.pop(), runtime_error);
    EXPECT_THROW(queue_sec.front(), runtime_error);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}