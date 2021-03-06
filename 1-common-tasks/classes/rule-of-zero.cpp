// The rule of zero

#include <memory>

class foo
{
	private:
		int x = 10;
		std::shared_ptr<int> p = std::make_shared<int>(5);
};

class bar
{
	public:
		std::unique_ptr<int> p = std::make_unique<int>(5);
};

// Utilise the value semantics of existing types to avoid having to
// implement custom copy and move operations.
// 
// The *rule of zero* states that we can avoid writing any custom
// copy/move constructors, assignment operators, or destructors by
// using existing types that support the appropriate copy/move
// semantics.
// 
// The class `foo` on [5-10], for example, does not perform any
// manual memory management, yet correctly supports copies and
// moves without any memory leaks. The defaulted copy/move
// constructors and assignment operators will simply copy or move
// each member. For the member `x` ([9]), this will copy the value.
// For `p`, which is a [`std::shared_ptr`](cpp/memory/shared_ptr),
// the resource will be shared between copies.
// 
// The class `bar` on [12-16] is not copyable by default because it
// has a [`std::unique_ptr`](cpp/memory/unique_ptr) member which
// itself is not copyable. However, it correctly supports move
// operations, which will transfer ownership of the dynamically
// allocated resource.

int main()
{
	foo f1;
	foo f2 = f1;

	bar b1;
	bar b2 = std::move(b2);
}
