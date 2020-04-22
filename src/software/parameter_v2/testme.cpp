#include <iostream>

#include "software/util/make_enum_macro/make_enum_macro.h"

MAKE_ENUM(MyEnum, Var1, Var2, Var3)

namespace BAR
{
    MAKE_ENUM(Enum2, NamespacedVar, NamespacedVar2)
}



int main(int argc, char **argv)
{
    std::cout << "printing enums" << std::endl;

    std::cout << toString(MyEnum::Var1) << std::endl;
    std::cout << toString(MyEnum::Var2) << std::endl;
    std::cout << toString(MyEnum::Var3) << std::endl;
    std::cout << "enum count: " << sizeMyEnum() << std::endl;

    std::cout << toString(BAR::Enum2::NamespacedVar) << std::endl;
    std::cout << "enum count: " << BAR::sizeEnum2() << std::endl;

    for (auto f : allValuesMyEnum())
    {
        std::cout << f << std::endl;
    }



    std::cout << "done" << std::endl;
}
