#include <string>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

#ifndef DISABLE_GLOBAL_FN
    inline static void print(const std::string& str){
        std::cout << str;
    }

    inline static void print(const std::string&& str){
        std::cout << str;
    }

    inline static void println(const std::string& str){
        std::cout << str << '\n';
    }

    inline static void println(const std::string&& str){
        std::cout << str << '\n';
    }
#endif

class pretty_log{

    private:
        pretty_log();

    public:

        #ifdef DISABLE_GLOBAL_FN
            inline static void print(std::string& str){
                std::cout << str;
            }

            inline static void println(std::string& str){
                std::cout << str << '\n';
            }
        #endif

        inline static std::string F_BLACK(std::string& str){
            return std::move("\033[1;30m" + str + "\033[0m");
        }

        inline static std::string F_DULL_BLACK(std::string& str){
            return std::move("\033[30m" + str + "\033[0m");
        }

        inline static std::string F_RED(std::string& str){
            return std::move("\033[1;31m" + str + "\033[0m");
        }

        inline static std::string F_DULL_RED(std::string& str){
            return std::move("\033[31m" + str + "\033[0m");
        }

        inline static std::string F_GREEN(std::string& str){
            return std::move("\033[1;32m" + str + "\033[0m");
        }

        inline static std::string F_DULL_GREEN(std::string& str){
            return std::move("\033[32m" + str + "\033[0m");
        }

        inline static std::string F_YELLOW(std::string& str){
            return std::move("\033[1;33m" + str + "\033[0m");
        }

        inline static std::string F_DULL_YELLOW(std::string& str){
            return std::move("\033[33m" + str + "\033[0m");
        }

        inline static std::string F_BLUE(std::string& str){
            return std::move("\033[1;34m" + str + "\033[0m");
        }

        inline static std::string F_DULL_BLUE(std::string& str){
            return std::move("\033[34m" + str + "\033[0m");
        }

        inline static std::string F_PINK(std::string& str){
            return std::move("\033[1;35m" + str + "\033[0m");
        }
};