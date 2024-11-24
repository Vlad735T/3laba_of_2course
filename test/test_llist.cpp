#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "llist.h" 
#include "array.h" 

template <typename T>
class LinkedListTest : public ::testing::Test {
protected:
    LinkedList<string> list_1;  
    LinkedList<string> list_2;  
};

typedef LinkedListTest<int> ListTest;

TEST_F(ListTest, ADD_AND_SEARCH) { 
    Myvector<string> items = {"apple", "banana", "orange", "peach", "pear", "apple"};

    for (int i = 0; i < items.size(); ++i) {
        string item = items[i];
        transform(item.begin(), item.end(), item.begin(), ::toupper); // Преобразуем в верхний регистр
        if (i % 2 == 0) {
            list_1.addtail(item);
        } else {
            list_1.addhead(item);
        }
    }

    list_1.print();
    
    list_2.addtail("carrot");

    bool found_in_list_1 = false;
    bool found_in_list_2 = false;

    try {
        list_1.search("PEACH"); // Поиск с учётом регистра
        found_in_list_1 = true;
    } catch (const exception&) {
        found_in_list_1 = false;
    }

    try {
        list_2.search("carrot"); // Поиск с учётом регистра
        found_in_list_2 = true;
    } catch (const exception&) {
        found_in_list_2 = false;
    }

    EXPECT_EQ(found_in_list_1, found_in_list_2);

    string concatenated_str;
    for (int i = 0; i < items.size(); ++i) {
        concatenated_str += list_1.get(i);
        if (i < items.size() - 1) {
            concatenated_str += " ";
        }
    }

    EXPECT_THAT(concatenated_str, ::testing::HasSubstr("APPLE"));
    EXPECT_THAT(concatenated_str, ::testing::Not(::testing::HasSubstr("ORANGEPS")));
}                                                     


TEST_F(ListTest, DEL_WITH_REM) {

    list_1.is_empty();
    list_2.is_empty();

    list_1.addhead("gold");
    list_1.addtail("silver");
    list_1.addhead("iron");
    list_1.addhead("copper");
    list_1.addtail("platinum");
    list_1.addhead("aluminum");

    EXPECT_EQ(list_1.size(), 6); 

    list_2.addtail("nickel");
    list_2.addhead("zinc");
    list_2.addhead("tin");
    list_2.addhead("lead");

    list_1.delhead(); 
    list_1.delhead(); 
    list_2.deltail(); 
    list_2.deltail();

    EXPECT_EQ(list_2.get(0), "lead"); 

    list_2.remove("lead");
    list_1.remove("platinum");
    list_1.remove("gold");

    EXPECT_THAT(list_1.get(0), ::testing::Not(::testing::StrCaseEq("silver")));  
    EXPECT_LT(list_1.get(0), list_2.get(0)); 

    list_2.delhead();
    list_1.deltail();
    list_1.deltail();


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}
