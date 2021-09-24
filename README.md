# color-print-cpp
cross-platform single header library to print colors to the console!

define PREFIX_PLOG before including pLog.h to add a PL_ prefix to constants such as RED, BLUE, etc.

```cpp
#include "pLog.h"

using namespace pLog;

int main(int argc, char* argv[]){
    if(!pLog_err)
        println("Colors not supported :(");
    
    println(12.5, RED, BOLD);
    println(16, UNDERLINE, BOLD, RED);
    println(fmt("I'm blue", BLUE) + " " + fmt("I'm cyan and bold", BRIGHT_CYAN, BOLD));
    println("r,g,b values are also supported! They can be bold, underlined, etc.", rgb(255, 100, 0), BOLD);
    println("to set background color pass a color to the bg() function.", bg(RED));
    print("rgb can also be passed to bg", bg(rgb(255, 100, 0)));    
}
```
