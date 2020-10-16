/**
 * @file plog.h
 * @author Brandon Kirincich
 * @brief single header library for printing text to the 
 * console with the specified format (color, underline, bold, etc.)
 * 
 * @example 
 * 
 * // Call init_pLog before using any functions. 
 * // This is only needed on Windows, but should be called just in case.
 * init_pLog();
 * 
 * println("test", UNDERLINE, BOLD, RED);
 * 
 * println(fmt("I'm blue", BLUE) + " " + fmt("I'm red and bold", RED, BOLD));
 * 
 * println("r,g,b values are also supported! They can be bold, underlined, etc.", rgb(255, 100, 0), BOLD);
 * 
 * println("to set background color pass a color to the bg() function.", bg(RED));
 * 
 * print("rgb can also be passed to bg", bg(rgb(255, 100, 0)));
 * 
 * @version 0.1
 * @date 2020-10-16
 * 
 * MIT License
 *
 * @copyright (c) 2020 Brandon Kirincich
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */
#include <string>
#include <iostream>
#include <cstdint>

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
 
    #else
    #define CLEAR "\033[0m"
    #define BOLD "1;"
    #define UNDERLINE "4;"
    #define BLACK "30;"
    #define RED "31;"
    #define GREEN "32;"
    #define YELLOW "33;"
    #define BLUE "34;"
    #define PINK "35;"
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
     * @brief return a string representing rgb value
     * 
     * @param r value for red (0 - 255)
     * @param g value for green (0 - 255)
     * @param b value for blue (0 - 255)
     * @return formatted string representing rgb value
     */
    std::string rgb(uint8_t r, uint8_t g, uint8_t b){
        return "38;2;" + std::to_string(+r) + ';' + std::to_string(+g) + ';' + std::to_string(+b) + ';';
    }

    /**
     * @brief return string representing a color to set background to
     * 
     * @param color color to set background to can 
     * be a predefined color macro or rgb() string
     * @return formatted string representing background color
     */
    std::string bg(std::string color){
        if(color.length() > 3)
            return "48;2;" + color.substr(5);   // if color is in rgb() format
        return std::to_string(std::stoi(color) + 10) + ';';
    }

    /**
     * @brief return string representing a color to set background to from r, g, b values
     * 
     * @param r value for red (0 - 255)
     * @param g value for green (0 - 255)
     * @param b value for blue (0 - 255)
     * @return formatted string representing background color
     */
    std::string bg(uint8_t r, uint8_t g, uint8_t b){
        return "48;2;" + std::to_string(+r) + ';' + std::to_string(+g) + ';' + std::to_string(+b) + ';';
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
        print((std::string)var1, (std::string)fstring(var2...));
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
        println((std::string)var1, (std::string)fstring(var2...));
    }
    
}