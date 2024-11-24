#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "flist.h"  

template <typename T>
class ForwardListTest : public ::testing::Test {
protected:
    ForwardList<string> fir_flist;  
    ForwardList<string> sec_flist;  

};

typedef ForwardListTest<int> flist;


TEST_F(flist, ADD_WITH_SEARCH){

    fir_flist.is_empty();

    fir_flist.addhead("door");
    fir_flist.addtail("window");
    fir_flist.addhead("chair");
    fir_flist.addhead("bed");
    fir_flist.addtail("table");
    fir_flist.addtail("door");

    fir_flist.print();
    
    sec_flist.addtail("door");


    bool found_fir = fir_flist.search("door");
    bool found_sec = sec_flist.search("door");
    string summ_str = fir_flist.get(0) + fir_flist.get(1) + fir_flist.get(2) +fir_flist.get(3) + fir_flist.get(4) + fir_flist.get(5);


    EXPECT_EQ(found_fir, found_sec); 
    EXPECT_GT(fir_flist.get(1), fir_flist.get(0)); 
    EXPECT_THAT(summ_str, ::testing::HasSubstr("oorwind"));  
    EXPECT_THAT(summ_str, ::testing::Not("catpigdog"));  
    EXPECT_THAT(summ_str, ::testing::StrCaseEq("BEDchAiRDOOrWINdowtabLeDoor")); // не учитывает регистр
}

TEST_F(flist, DEL_WITH_REMOVE){

    fir_flist.addhead("pig");
    fir_flist.addtail("parrot");
    fir_flist.addhead("cow");
    fir_flist.addhead("chicken");
    fir_flist.addtail("horse");
    fir_flist.addhead("goat");


    sec_flist.is_empty();

    sec_flist.addtail("dog");
    sec_flist.addhead("cat");
    sec_flist.addhead("parrot");
    sec_flist.addhead("hamster");

    fir_flist.delhead();
    fir_flist.delhead();
    sec_flist.deltail();
    sec_flist.deltail();

    EXPECT_EQ(sec_flist.get(0), "hamster"); 

    sec_flist.remove("hamster");
    fir_flist.remove("horse");
    fir_flist.remove("pig");

    EXPECT_THAT(fir_flist.get(0), ::testing::Not(::testing::StrCaseEq("parrot"))); 
    EXPECT_LT(fir_flist.get(0), sec_flist.get(0)); 

    sec_flist.delhead();
    fir_flist.deltail();
    fir_flist.deltail();

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
}
