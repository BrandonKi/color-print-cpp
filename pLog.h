#include <string>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif


namespace pLog{

    #define CLEAR "\033[0m"
    #define RED "30m"

    /**
     * @brief Initializes pLog. This is mostly for windows platforms but should be called anyway.
     * 
     * @return a bool representing whether or not pLog could be initialized 
     */
    inline bool init_pLog(){
        #ifdef _WIN32
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut == INVALID_HANDLE_VALUE)
                return false;
            DWORD dwMode = 0;
            if (!GetConsoleMode(hOut, &dwMode))
                return false;
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(hOut, dwMode))
                return false;
            return true;
        #endif
        return true;
    }

    inline void print(const std::string& str){
        std::cout << str;
    }

    inline void print(const std::string&& str){
        std::cout << str;
    }

    inline void println(const std::string& str){
        std::cout << str << '\n';
    }

    inline void println(const std::string&& str){
        std::cout << str << '\n';
    }

    inline std::string F_BLACK(std::string& str){
        return std::move("\033[1;30m" + str + "\033[0m");
    }

    inline std::string F_DULL_BLACK(std::string& str){
        return std::move("\033[30m" + str + "\033[0m");
    }

    inline std::string F_RED(std::string&& str){
        return std::move("\033[1;31m" + str + "\033[0m");
    }

    inline std::string F_DULL_RED(std::string& str){
        return std::move("\033[31m" + str + "\033[0m");
    }

    inline std::string F_GREEN(std::string& str){
        return std::move("\033[1;32m" + str + "\033[0m");
    }

    inline std::string F_DULL_GREEN(std::string& str){
        return std::move("\033[32m" + str + "\033[0m");
    }

    inline std::string F_YELLOW(std::string& str){
        return std::move("\033[1;33m" + str + "\033[0m");
    }

    inline std::string F_DULL_YELLOW(std::string& str){
        return std::move("\033[33m" + str + "\033[0m");
    }

    inline std::string F_BLUE(std::string& str){
        return std::move("\033[1;34m" + str + "\033[0m");
    }

    inline std::string F_DULL_BLUE(std::string& str){
        return std::move("\033[34m" + str + "\033[0m");
    }

    inline std::string F_PINK(std::string& str){
        return std::move("\033[1;35m" + str + "\033[0m");
    }
}