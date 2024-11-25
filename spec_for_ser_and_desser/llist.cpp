
#include "/home/kln735/4test_lab/src/llist.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    LinkedList<string> start;
    start.addtail("potato");
    start.addhead("tomato");
    start.addhead("carrot");
    start.addtail("letter");
    start.addtail("cucumber");
    start.addhead("limon");
    start.addtail("pepper");
    start.serialization("serializell.bin");

    LinkedList<string> end;

    end.deserialization("serializell.bin");
    end.print();

    return 0;
}