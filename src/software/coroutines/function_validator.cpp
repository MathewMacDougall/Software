#include "software/coroutines/function_validator.h"

#include <boost/bind.hpp>

FunctionValidator::FunctionValidator(ValidationFunction validation_function,
                                     std::shared_ptr<World> world)
    : this_ptr_1(this),
      this_ptr_2(nullptr),
      validation_function_(validation_function),
      world_(world),
      validation_sequence(
          boost::bind(&FunctionValidator::executeAndCheckForSuccessWrapper, this, _1))
{
    std::cout << "FunctionValidator created with world_ptr " << world_ << std::endl;
}

void FunctionValidator::executeAndCheckForSuccessWrapper(
    ValidationCoroutine::push_type &yield)
{
    std::cout << "wrapper called with world_ptr " << world_ << std::endl;

    yield();

    std::cout << "wrapper after yield called with world_ptr " << world_ << std::endl;

    assert(world_);
    assert(validation_function_);

    // Anytime after the first function call, the validation_function will be
    // used to perform the real logic.
    validation_function_(world_, yield);
}

bool FunctionValidator::executeAndCheckForSuccess()
{
    this_ptr_2 = this;
    std::cout << "FunctionValidator had address " << this_ptr_1
              << " during construction, and address " << this_ptr_2 << " afterwards"
              << std::endl;
    // Check the coroutine status to see if it has any more work to do.
    if (validation_sequence)
    {
        std::cout << "running coroutine" << std::endl;
        // Run the coroutine. This will call the bound executeAndCheckForSuccessWrapper
        // function
        validation_sequence();
    }else {
        std::cout << "did not run coroutine" << std::endl;
    }

    // The validation_function is done if the coroutine evaluates to false, which means
    // execution has "dropped out" the bottom of the function and there is no more work to
    // do. If this is the case then the validation_function has passed successfully
    return !static_cast<bool>(validation_sequence);
}
