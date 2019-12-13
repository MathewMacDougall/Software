#include <iostream>
#include <boost/bind.hpp>
#include <boost/coroutine2/all.hpp>

using Coroutine = boost::coroutines2::coroutine<void>;



class MyCoroutine
{
public:
    MyCoroutine(std::shared_ptr<std::string> s) : s_(s), foo(false), coroutine_sequence(boost::bind(&MyCoroutine::coroutineFunctionWrapper, this, _1))
    {
    }

    void executeCoroutine() {
        std::cout << std::boolalpha << "Foo (outside coroutine) = " << foo << std::endl;
        std::cout << "s_ (outside coroutine) = " << s_ << std::endl;
        std::cout << "s_ (outside coroutine) = " << *s_ << std::endl;
        coroutine_sequence();
    }

    void setFoo(bool new_value) {
        foo = new_value;
    }

private:
    void coroutineFunctionWrapper(Coroutine::push_type &yield) {
        // Ignore the first call made during binding
        yield();

        coroutineFunction(yield);
    }

    void coroutineFunction(Coroutine::push_type &yield) {
        while (true)
        {
            std::cout << std::boolalpha << "Foo (inside coroutine) = " << foo << std::endl;
            std::cout << "s_ (outside coroutine) = " << s_ << std::endl;
            std::cout << "s_ (outside coroutine) = " << *s_ << std::endl;
            yield();
        }
    }

    Coroutine::pull_type coroutine_sequence;
    bool foo;
    std::shared_ptr<std::string> s_;
};

int main(int argc, char **argv)
{
    auto str = std::make_shared<std::string>("foobar");
    MyCoroutine m(str);
    m.executeCoroutine();
    m.setFoo(true);
    *str = "barfooz";
    m.executeCoroutine();


    return 0;
}
