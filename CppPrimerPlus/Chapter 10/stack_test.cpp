#include "stack.h"
#include <cassert>

int main() {
    Stack s;
    const int N = 5;
    for (int i = 1; i <= N; ++i) {
        assert(s.push(i));
    }
    Item popped;
    for (int i = N; i >= 1; --i) {
        assert(s.pop(popped));
        assert(popped == static_cast<Item>(i));
    }
    assert(s.isempty());
    return 0;
}
