/// @file moveAndForward.cpp

#include <iostream>
#include <string>

class String
{
    public:
        String(const std::string &rhs) : m_str(rhs) {std::cout << "copy ctor of String" << std::endl;}
        String(std::string && rhs) : m_str(rhs) {std::cout << "move ctor of String" << std::endl;}

    private:
        std::string m_str;
};

class Annotation
{
    public:
        Annotation(const String text) : m_text(std::move(text)) {std::cout << "ctor of Annotation" << std::endl;}
    private:
        String m_text;
};



int main()
{
    // moving objects
    const std::string const_str = "const str";
    std::string str = "str";
    String a(std::move(const_str)); //copy ctor of string -> don't declare objects const if you want to be able to move from them
    const String b(std::move(str)); // move ctor
    Annotation ano(std::move(b)); //
}