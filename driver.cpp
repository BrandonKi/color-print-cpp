#include "pLog.h"

using namespace pLog;


int main(int argc, char* argv[]){

    init_pLog();

    println(fmt("test", UNDERLINE, BOLD, RED) + " " + fmt("test", BLUE));

    print("test", BOLD, RED);

}