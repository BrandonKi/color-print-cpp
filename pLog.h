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

    #ifdef PREFIX_MACROS
    #define PL_CLEAR "\033[0m"
    #define PL_BOLD "1;"
    #define PL_UNDERLINE "4;"
    #define PL_BLACK "30;"
    #define PL_RED "31;"
    #define PL_BLUE "32;"
    #else
    #define CLEAR "\033[0m"
    #define BOLD "1;"
    #define UNDERLINE "4;"
    #define BLACK "30;"
    #define RED "31;"
    #define BLUE "32;"
    #endif

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

    /**
     * @brief base case function for unpacking var args
     * 
     * @return an empty string
     */
    std::string fstring(){ 
        return std::string("");
    }

    /**
     * @brief helper function for unpacking var args
     * this function takes all var args which are assumed to be valid ansii args 
     * and combines them into a single string 
     * 
     * @param var1 first arg in var args
     * @param var2 var args
     * @return all args combined into a single string 
     */
    template <typename T, typename... Types> 
    std::string fstring(T var1, Types... var2){     
        return std::string(var1) + fstring(var2...) ; 
    }

    /**
     * @brief function called to correctly format a string with all args given
     * for ex. fmt("test", UNDERLINE, RED, ...)
     * 
     * @param str base string to add ansii escape args onto
     * @param var2 any amount of ansii escape args
     * @return base string with ansii escape args added onto it
     */
    template <typename T, typename... Types> 
    std::string fmt(T str, Types... var2){
        std::string color = fstring(var2...);
        return _pLog_preamble_ + color.substr(0,color.length()-1) + 'm' + str + CLEAR;
    }
    

    /**
     * @brief print string to the console
     * 
     * @param str string to print
     */
    inline void print(const std::string& str){
        std::cout << str;
    }

    /**
     * @brief print string to console
     * 
     * @param str string to print
     */
    inline void print(const std::string&& str){
        std::cout << str;
    }


    /**
     * @brief print string to the console with specified format as a string
     * 
     * @param str string to print
     * @param fmt format to use
     */
    inline void print(const std::string& str, const std::string& fmt){
        if(fmt == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << fmt.substr(0, fmt.length()-1) << 'm' << str << CLEAR;
        }
    }

    /**
     * @brief print string to the console with specified format as a string
     * 
     * @param str string to print
     * @param fmt format to use
     */
    inline void print(const std::string&& str, const std::string& fmt){
        if(fmt == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << fmt.substr(0, fmt.length()-1) << 'm' << str << CLEAR;
        }
    }

    /**
     * @brief wrapper of print() that unpacks var args and formats them automatically
     * 
     * @param var1 base string
     * @param var2 list of ansii escape args
     */
    template <typename T, typename... Types> 
    void print(T var1, Types... var2){
        std::string str = var1;
        std::string f_string = fstring(var2...);
        // std::cout << str << " " << f_string;
        print(str, f_string);
    }

    /**
     * @brief print a string to the console with a newline at the end
     * 
     * @param str string to print
     */
    inline void println(const std::string& str = ""){
        std::cout << str << '\n';
    }

    /**
     * @brief print a string to the console with a newline at the end
     * 
     * @param str string to print
     */
    inline void println(const std::string&& str){
        std::cout << str << '\n';
    }

    /**
     * @brief print a string with the specified format 
     * to the console with a newline at the end
     * 
     * @param str string to print
     */
    inline void println(const std::string& str, const std::string& fmt){
        if(fmt == _pLog_EMPTY_STRING_CONST_)
            std::cout << str;
        else{
            std::cout << _pLog_preamble_ << fmt.substr(0, fmt.length()-1) << 'm' << str << CLEAR;
        }
    }

    /**
     * @brief print a string with the specified format 
     * to the console with a newline at the end
     * 
     * @param str string to print
     */
    inline void println(const std::string&& str, const std::string& fmt){
        if(fmt == _pLog_EMPTY_STRING_CONST_)
            std::cout << str << '\n';
        else{
            std::cout << _pLog_preamble_ << fmt.substr(0, fmt.length()-1) << 'm' << str << CLEAR << '\n';
        }
    }

    /**
     * @brief wrapper of println() that unpacks var args and formats them automatically
     * 
     * @param var1 base string
     * @param var2 list of ansii escape args
     */
    template <typename T, typename... Types> 
    void println(T var1, Types... var2) 
    { 
        println(var1, fstring(var2...));
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