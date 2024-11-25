
#include "/home/kln735/4test_lab/src/flist.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    ForwardList<string> start;
    start.addtail("Vlad");
    start.addhead("Igor");
    start.addhead("Anton");
    start.addtail("Sergey");
    start.addtail("Petr");
    start.addhead("Stepan");
    start.addtail("Artem");
    start.serialization("serializefl.bin");

    ForwardList<string> end;

    end.deserialization("serializefl.bin");
    end.print();

    return 0;
}