
#include "/home/kln735/4test_lab/src/stack.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    Stack<string> start;
    start.push("orange");
    start.push("strawberry");
    start.push("peach");
    start.push("pear");
    start.push("apple");
    start.push("banana");
    start.push("coconut");
    
    start.serialization("serializest.bin");

    Stack<string> end;

    end.deserialization("serializest.bin");
    end.print();

    return 0;
}