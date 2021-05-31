/// @file moveAndForward.cpp

#include <iostream>
#include <string>
#include <memory>

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

class A
{
    public:
        A (int &n) { std::cout << "lvalue overload n=" << n << std::endl;} // copy ctor rvalue
        A (int && n) {std::cout << "rvalue overload n=" << n << std::endl;} // move ctor
};

// https://en.cppreference.com/w/cpp/utility/forward
class B
{
    public:
        template<class T1, class T2, class T3>
        B(T1 && t1, T2 && t2, T3 && t3) :
            _a1{std::forward<T1>(t1)},
            _a2{std::forward<T2>(t2)},
            _a3{std::forward<T3>(t3)}
        {
        }
    private:
    std::string _a2;
    A _a1, _a3;
};

template<class T, class U>
std::unique_ptr<T> make_unique1(U && u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique2(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}


int main()
{
    // moving objects
    const std::string const_str = "const str";
    std::string str = "str";
    String a(std::move(const_str)); //copy ctor of string -> don't declare objects const if you want to be able to move from them
    const String b(std::move(str)); // move ctor
    Annotation ano(std::move(b)); //

    auto p1 = make_unique1<A>(2); // rvalue;
    int i = 1;
    auto p2 = make_unique1<A>(i); // lvalue;
    A tmp(std::forward<int>(i)); // rvalue
    A tmp2(std::move(i)); // rvalue
    A tmp3(i); // lvalue
    std::cout << "B" << std::endl;
    auto p3 = make_unique2<B>(1,"hi",2);
}