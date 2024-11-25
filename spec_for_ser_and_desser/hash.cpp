
#include "/home/kln735/4test_lab/src/hash.h"  


//xxd serialize.bin
//hexdump serialize.bin   
int main(){

    Hashtable<string, string> start(7);
    start.add("val1", "cow");
    start.add("1val", "pig");
    start.add("1key", "dog");
    start.add("key1", "cat");
    start.add("football", "head");
    start.add("swimming", "hair");
    
    start.print();

    start.serialization("serializehh.bin");

    cout << "\n";

    Hashtable<string, string> end(7);

    end.deserialization("serializehh.bin");
    end.print();

    return 0;
}