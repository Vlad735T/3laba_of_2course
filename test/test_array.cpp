#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "array.h"  

// Шаблонный тестовый класс для Myvector
template <typename T>
class MyvectorTest : public ::testing::Test {
protected:
    Myvector<T> vec_int;  // Экземпляр вектора
    Myvector<T> vec_str;  
    Myvector<int> vec_copy;
};

// Специализация шаблона для int
typedef MyvectorTest<int> test_vector_int;
typedef MyvectorTest<string> test_vector_str;

TEST_F(test_vector_int, MPUSH) {
    vec_int.MPUSH(1);  
    vec_int.MPUSH(2); 
    vec_int.MPUSH(3);  
    vec_int.MPUSH(4);  
    vec_int.MPUSH(4);  

    int var = vec_int.MGET(4) - vec_int.MGET(1);
    int var_LE = vec_int.MGET(4) - vec_int.MGET(3);
    int var_proizved_fir = pow(vec_int.MGET(2), 3) - vec_int.MGET(3);
    int var_proizved_sec = vec_int.MGET(0) * 23;

    EXPECT_EQ(vec_int.size(), 5);  
    EXPECT_EQ(var, 2); 
    EXPECT_NE(vec_int.MGET(0), 15);
    EXPECT_GE(var_proizved_fir, var_proizved_sec);
    EXPECT_LE(var_LE, 4);
}

TEST_F(test_vector_str, MPUSH){
    vec_str.MPUSH("Vlad");
    vec_str.MPUSH("Dasha");
    vec_str.MPUSH("Anton");
    vec_str.MPUSH("Roma");
    vec_str.MPUSH("Igor");
    vec_str.MPUSH("Vlad");


    EXPECT_EQ(vec_str.MGET(0), vec_str.MGET(5));
    EXPECT_NE(vec_str.MGET(1), vec_str.MGET(2));
    EXPECT_THAT(vec_str.MGET(3),  ::testing::EndsWith("ma"));
    EXPECT_THAT(vec_str.MGET(1),  ::testing::StartsWith("Da"));
    EXPECT_THAT(vec_str.MGET(4),  ::testing::Not("Pavel"));
    EXPECT_THAT(vec_str.MGET(2),  ::testing::HasSubstr("nto"));
}



TEST_F(test_vector_int, MPUSH_IND){

    vec_int.MPUSH(2, 0);  
    vec_int.MPUSH(4, 1);  
    vec_int.MPUSH(8, 0);  
    vec_int.MPUSH(16, 0);  
    vec_int.MPUSH(32, 2);  

    vec_int.print();
    
    int fir_val = vec_int.MGET(1);
    int sec_val = vec_int.MGET(4);
    int third_val = vec_int.MGET(0) * 7;

    EXPECT_EQ(vec_int.MGET(3), 2);  
    EXPECT_GE(fir_val, sec_val);
    EXPECT_LT(vec_int.MGET(0), vec_int.MGET(2));
    EXPECT_GT(third_val, 111);
}




TEST_F(test_vector_str, MPUSH_IND){
    vec_str.MPUSH("computer", 0);
    vec_str.MPUSH("mouse", 0);
    vec_str.MPUSH("cake", 1);
    vec_str.MPUSH("head",2);
    vec_str.MPUSH("pig", 3);
    vec_str.MPUSH("peper", 4);

    string merger_fir_sec = vec_str.MGET(0) + vec_str.MGET(1);
    string merger_thir_four = vec_str.MGET(2) + " " + vec_str.MGET(3);

    EXPECT_THAT(merger_fir_sec,  ::testing::HasSubstr("useca"));
    EXPECT_THAT(vec_str.MGET(4),  ::testing::Not("epes"));
    EXPECT_THAT(merger_thir_four, ::testing::Not(::testing::MatchesRegex("^pig")));
    EXPECT_THAT(merger_thir_four, ::testing::Not(::testing::MatchesRegex("computer$")));
}

TEST_F(test_vector_int, MDEL) {
    
    vec_int.MPUSH(10);
    vec_int.MPUSH(20);
    vec_int.MPUSH(30);

    Myvector<int>vec = vec_int;

    EXPECT_EQ(vec.size(), 3);         
    EXPECT_EQ(vec[0], 10);            
    EXPECT_EQ(vec[1], 20);             
    EXPECT_EQ(vec[2], 30);          

    vec.MDEL(1);

    EXPECT_EQ(vec.size(), 2);          
    EXPECT_EQ(vec[0], 10);            
    EXPECT_EQ(vec[1], 30);           

    vec.MDEL(0);

    EXPECT_EQ(vec.size(), 1);        
    EXPECT_EQ(vec[0], 30);            

    EXPECT_THROW(vec.MDEL(-1), out_of_range);

    EXPECT_THROW(vec.MDEL(10), out_of_range);
}



TEST_F(test_vector_int, MGET_WITH_MSET) {
    vec_int.MPUSH(11);  
    vec_int.MPUSH(13, 0);  
    vec_int.MPUSH(15);  
    vec_int.MPUSH(17, 1);  
    vec_int.MPUSH(19, 3);  
    vec_int.MPUSH(21, 5);  
    vec_int.MPUSH(23, 2);  
    vec_int.MPUSH(13);  

    int fir_val = vec_int.MGET(2) + vec_int.MGET(1); // 40
    int sec_val = vec_int.MGET(4) + vec_int.MGET(3); // 30
    int third_val = vec_int.MGET(0) +  vec_int.MGET(5);
    
    [[maybe_unused]] int fourth_val = vec_int.MGET(0) + vec_int.MGET(5);  // Оставить переменную без предупреждения

    vec_int.MSET(1, 0);  
    vec_int.MSET(2, 1);  
    vec_int.MSET(3, 2);  
    int fifth_val = 2 * ( vec_int.MGET(0) +  vec_int.MGET(1)+  vec_int.MGET(2) );

    EXPECT_EQ(fir_val, 40);  
    EXPECT_NE(vec_int.MGET(1), vec_int.MGET(7));  
    EXPECT_GE(fir_val, third_val);  
    EXPECT_LT(sec_val, fir_val);  
    EXPECT_EQ(fifth_val, vec_int.MGET(3) + 1);  
}



TEST_F(test_vector_int, OTHER_ACTIVITY) {

    EXPECT_EQ(vec_int.size(), 0);
    EXPECT_EQ(vec_int.memory_use(), 1);

    vec_int.MPUSH(1);
    vec_int.MPUSH(2);
    vec_int.MPUSH(3);

    EXPECT_EQ(vec_int.size(), 3);
    EXPECT_EQ(vec_int.memory_use(), 4);  

    EXPECT_EQ(*vec_int.begin(), 1);
    EXPECT_EQ(*(vec_int.end() - 1), 3);

    vec_copy = vec_int;

    EXPECT_EQ(vec_copy.size(), vec_int.size());
    EXPECT_EQ(vec_copy.memory_use(), vec_int.memory_use());

    int index = 0;
    for (auto it = vec_int.begin(); it != vec_int.end(); ++it) {
        EXPECT_EQ(*it, vec_copy[index++]);
    }

    vec_int.resize(10);
    EXPECT_EQ(vec_int.size(), 3);  
    EXPECT_EQ(vec_int.memory_use(), 10);  

    vec_int.resize(2);
    EXPECT_EQ(vec_int.size(), 2);  
    EXPECT_EQ(vec_int.memory_use(), 2);  

    EXPECT_EQ(*vec_int.begin(), 1);
    EXPECT_EQ(*(vec_int.end() - 1), 2);

    EXPECT_EQ(vec_int.memory_use(), 2);

    EXPECT_EQ(vec_int.size(), 2);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
    return RUN_ALL_TESTS();  // Запуск всех тестов
}
