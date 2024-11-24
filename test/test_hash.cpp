#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "hash.h" 

template <typename T>
class HashTest : public ::testing::Test {
protected:
    Hashtable<int, int> hash_fir{10};  
    Hashtable<string, string> hash_sec{5};  
};

typedef HashTest<int> hash_int;
typedef HashTest<string> hash_str;

TEST_F(hash_int, ALL_OPERATION_FOR_INT) {

    hash_fir.add(123, 456);  
    hash_fir.add(321, 654);  
    hash_fir.add(321, 427654);  


    hash_fir.print();

    EXPECT_EQ(hash_fir.get(123), 456);
    EXPECT_EQ(hash_fir.get(321), 427654);

    hash_fir.add(7654, 15000);
    EXPECT_EQ(hash_fir.get(7654), 15000);

    hash_fir.remove(123);
    hash_fir.remove(321);
    hash_fir.remove(7654);

    EXPECT_THROW(hash_fir.get(123), runtime_error); 
    EXPECT_THROW(hash_fir.get(321), runtime_error); 
    EXPECT_THROW(hash_fir.get(7654), runtime_error); 

}                                                

TEST_F(hash_str, ALL_OPERATION_FOR_STR) {

    hash_sec.add("key1", "value1");  
    hash_sec.add("key2", "value2"); 
    hash_sec.add("1key", "value3");  
    hash_sec.add("2key", "value4"); 
    hash_sec.add("123", "value5"); 
    hash_sec.add("321", "value6"); 

    hash_sec.print();

    EXPECT_EQ(hash_sec.get("key1"), "value1");
    EXPECT_EQ(hash_sec.get("key2"), "value2");

    hash_sec.add("key1", "new_value1");
    EXPECT_EQ(hash_sec.get("key1"), "new_value1");

    hash_sec.remove("key1");    
    hash_sec.remove("321");

    EXPECT_THROW(hash_sec.get("key1"), runtime_error);  
    EXPECT_THROW(hash_sec.get("321"), runtime_error);  

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}