
#include "/home/kln735/4test_lab/src/array.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    Myvector<string> start;
    start.MPUSH("Vlad");
    start.MPUSH("Igor");
    start.MPUSH("Anton");
    start.MPUSH("Sergey");
    start.MPUSH("Petr");
    start.MPUSH("Stepan");
    start.MPUSH("Artem");

    start.serialization("serialize.bin");

    Myvector<string> end;

    end.deserialization("serialize.bin");
    end.print();

    return 0;
}