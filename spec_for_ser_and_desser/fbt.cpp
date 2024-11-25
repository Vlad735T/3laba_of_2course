
#include "/home/kln735/4test_lab/src/fbt.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    FBT start(10);
    start.Add(20);
    start.Add(25);
    start.Add(30);
    start.Add(35);
    start.Add(40);
    start.Add(45);
    start.Add(50);


    start.serialization("serializeftree.bin");

    FBT end(50);

    end.deserialization("serializeftree.bin");
    end.PrintTree();

    return 0;
}