#include "pLog.h"

using namespace pLog;


int main(int argc, char* argv[]){

    init_pLog();

    print("test", fstring(UNDERLINE, BOLD, RED));

    println();

    print(wrap("test", RED) + " " + wrap("test2", fstring(RED, BOLD)));
    
}