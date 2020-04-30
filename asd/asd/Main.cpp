#include <functional>


using Task = std::function<void>;


void func(Task task) {
	

}

int main() {

	func([=] {
		std::cout << "hello";
	});
	return 0;
}