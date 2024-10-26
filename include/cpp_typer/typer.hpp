#include "rfl/to_view.hpp"
#include <cstdlib>
#include <rfl.hpp>
#include <rfl/fields.hpp>
#include <stdexcept>
#include <type_traits>
#include <CLI11.hpp>
#include <iostream>

#include "cpp_typer/utils/option_name_utils.hpp"

#define CPP_TYPER_SUCCESSFUL_PARSE_RETURN_CODE -1

namespace cpp_typer {

template<typename ArgType, typename AnnotationType = std::string>
class Annotated {
public:
    // the actual value of the annotated instance
    ArgType value;

    // the annotation of this instance, will be displayed as help msg
    AnnotationType annotation;

    // whether this instance should be positional argument for cli
    bool positional = false;

    operator auto() { return value; } // implicitly convert to ArgType
};

template<typename Type>
struct is_annotated_impl : std::false_type {};

template<typename ArgType, typename AnnotationType>
struct is_annotated_impl<Annotated<ArgType, AnnotationType>> : std::true_type {};

template<typename T>
constexpr bool is_annotated = is_annotated_impl<std::decay_t<T>>::value;

template<typename T>
class Typer {
public:
    static T parse_cli(int argc, char** argv) {
        auto app = CLI::App{};
        auto args = T{};

        const auto view = rfl::to_view(args);

        view.apply([&](auto& f) {
            auto& val = *f.value();
            
            // anotated type are handle differently
            if constexpr (is_annotated<decltype(val)>) {
                app.add_option(
                    to_option_name(f.name(), val.positional),
                    val.value,
                    std::string(val.annotation)
                );
                return;
            }

            app.add_option(to_option_name(f.name(), false), val);
        });


        // because CLI11_PARSE macro will try to return an int as return value
        // so we can't place it inside parse_cli (which returns T{})
        // we need to use this work around
        auto _parse = [&](){
            try {
                CLI11_PARSE(app, argc, argv);
            } catch (std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
            return CPP_TYPER_SUCCESSFUL_PARSE_RETURN_CODE;
        };

        auto parser_ret = _parse();
        if (parser_ret >= 0) { // for error (>0) and help message (0) to prevent further execution
            exit(parser_ret);
        }
        return args;
    }
};

} // namespace cpp_typer