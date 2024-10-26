#include <cpp_typer/typer.hpp>
#include <string>

struct A{
    std::string name = "a";
    std::string value = "6";
    int age;
    float weight;
    cpp_typer::Annotated<std::string> msg = {
        "hi", "Print a msg to terminal"
    };
    cpp_typer::Annotated<int> version = {
        101,
        "Version of this program",
        .positional = true
    };
};

int main(int argc, char** argv) {
    auto args = cpp_typer::Typer<A>::parse_cli(argc, argv);
    std::cout << "main\n";
    std::cout << "args.name: " << args.name << '\n';
    std::cout << "args.value: " << args.value << '\n';
    std::cout << "args.age: " << args.age << '\n';
    std::cout << "args.weight: " << args.weight << '\n';
    std::cout << "args.msg: " << args.msg.value << '\n';
    return 0;
}