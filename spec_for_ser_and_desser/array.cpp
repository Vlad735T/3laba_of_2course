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

    start.serialization("serializear.bin");

    Myvector<string> end;

    end.deserialization("serializear.bin");
    end.print();

    return 0;
}