    #include <iostream>
    #include <list>

    template <class T>
    struct C
    {
        T t_;

        template <class U,
                  class = typename std::enable_if
                        <
                            !std::is_lvalue_reference<U>::value
                        >::type>
            C(U&& u) : t_(std::forward<T>(std::move(u).get())) {}
    };

    class A
    {
        int data_;
    public:
        explicit A(int data = 1)
            : data_(data) {}
        ~A() {data_ = -1;}

        void test() const
        {
            if (data_ < 0)
                std::cout << "A is destructed\n";
            else
                std::cout << "A = " << data_ << '\n';
        }
    };

    class Awrap
    {
        const A& a_;
    public:
        explicit Awrap(const A& a) : a_(a) {}
        const A& get() const {return a_;}
    };

    template <class C>
    void test(C c)
    {
        c.t_.test();
    }

    int main()
    {
        std::list<C<const A&> > list;
        A a(3);
        C<const A&> c((Awrap(a)));
        list.push_back(c);
        test(c);
        test(list.front());
    }

