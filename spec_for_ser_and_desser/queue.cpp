
#include "/home/kln735/4test_lab/src/queue.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    QUEUE<string> start;
    start.push("pig");
    start.push("cat");
    start.push("dog");
    start.push("parrot");
    start.push("cow");
    start.push("banana");
    start.push("elephant");
    
    start.serialization("serializequ.bin");

    QUEUE<string> end;

    end.deserialization("serializequ.bin");
    end.print();

    return 0;
}