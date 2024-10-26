#include <string>

namespace cpp_typer {

inline std::string to_option_name (const auto& named_tuple_field_name, bool positional) {
    if (positional) {
        return std::string(named_tuple_field_name);
    }
    return "--" + std::string(named_tuple_field_name);
}

} // namespace cpp_typer