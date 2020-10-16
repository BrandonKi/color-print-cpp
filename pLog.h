#include <string>
#include <iostream>
#include <cstdarg>

#ifdef _WIN32
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif


namespace pLog{

    static const std::string _pLog_EMPTY_STRING_CONST_ = "";
    static const std::string _pLog_preamble_ = "\033[";

    #define CLEAR "\033[0m"
    #define BOLD "1;"
    #define UNDERLINE "4;"
    #define BLACK "30;"
    #define RED "31;"
    #define BLUE "32;"

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

    std::string fstring() 
    { 
        return std::string("");
    }

    template <typename T, typename... Types> 
    std::string fstring(T var1, Types... var2) 
    {     
        return std::string(var1) + fstring(var2...) ; 
    }

    template <typename T, typename... Types> 
    std::string fmt(T str, Types... var2){
        std::string color = fstring(var2...);
        return _pLog_preamble_ + color.substr(0,color.length()-1) + 'm' + str + CLEAR;
    }
    
    template <typename T, typename... Types> 
    void print(T var1, Types... var2) 
    { 
        print(var1, fstring(var2...));
    } 

    inline void print(const std::string& str){
        std::cout << str;
    }

    inline void print(const std::string&& str){
        std::cout << str;
    }

    inline void print(const std::string& str, const std::string& color){
        if(color == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << color.substr(0,color.length()-1) << 'm' << str << CLEAR;
        }
    }

    inline void print(const std::string&& str, const std::string& color){
        if(color == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << color.substr(0,color.length()-1) << 'm' << str << CLEAR;
        }
    }

    inline void println(const std::string& str = ""){
        std::cout << str << '\n';
    }

    inline void println(const std::string&& str){
        std::cout << str << '\n';
    }

    inline void println(const std::string& str, const std::string& color){
        if(color == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << color.substr(0,color.length()-1) << 'm' << str << CLEAR;
        }
    }

    inline void println(const std::string&& str, const std::string& color){
        if(color == _pLog_EMPTY_STRING_CONST_)
            std::cout << str << '\n';
        else{
            std::cout << _pLog_preamble_ << color.substr(0,color.length()-1) << 'm' << str << CLEAR << '\n';
        }
    }





    
    inline std::string black(std::string& str){
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