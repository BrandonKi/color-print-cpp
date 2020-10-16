#include "pLog.h"

using namespace pLog;


int main(int argc, char* argv[]){

    init_pLog();

    print(fmt("test", UNDERLINE, BOLD, RED) + " " + fmt("test", BLUE));

    println();

    print("test", BOLD, RED);

}