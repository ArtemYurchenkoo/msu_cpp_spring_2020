#include "ThreadPool.h"
#include <iostream>
#include <cassert>

struct A {
    int value;
};

int foo(const A& a) { return a.value; }
int main(){
    ThreadPool pool(3);

    auto task1 = pool.exec(foo, A{5});
    assert(task1.get() == 5);

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);

    for(int i = 0; i < 20; ++i){
        auto task = pool.exec([i](){ return i; });
        assert(task.get() == i);
    }
    std::cout << "Done\n";
    return 0;
}