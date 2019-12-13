#include "software/simulated_tests/validation/function_validator.h"

#include <boost/bind.hpp>

FunctionValidator::FunctionValidator(ValidationFunction validation_function,
                                     std::shared_ptr<World> world)
        :  validation_function_(validation_function),
           world_(world),

        // We need to provide the world and validation_function in the coroutine function
        // binding so that the wrapper function has access to the correct variable context,
        // otherwise the World inside the coroutine will not update properly when the
        // pointer is updated, and the wrong validation_function may be run.
           validation_sequence(
//          boost::bind(&FunctionValidator::executeAndCheckForSuccessWrapper, this, _1,
//                      world, validation_function))
                   boost::bind(&FunctionValidator::executeAndCheckForSuccessWrapper, this, _1))
{
    std::cout << "FunctionValidator created with " << world_ << std::endl;
}

//void FunctionValidator::executeAndCheckForSuccessWrapper(
//    ValidationCoroutine::push_type &yield, std::shared_ptr<World> world,
//    ValidationFunction validation_function)
void FunctionValidator::executeAndCheckForSuccessWrapper(
        ValidationCoroutine::push_type &yield)
{
    std::cout << "wrapper called with " << world_ << std::endl;
    // Yield the very first time the function is called, so that the validation_function
    // is not run until this coroutine / wrapper function is called again by
    // executeAndCheckForSuccess
    yield();

    std::cout << "wrapper after yield called with " << world_ << std::endl;

    assert(world_);
    assert(validation_function_);

    // Anytime after the first function call, the validation_function will be
    // used to perform the real logic.
    validation_function_(world_, yield);
}

bool FunctionValidator::executeAndCheckForSuccess()
{
    // Check the coroutine status to see if it has any more work to do.
    if (validation_sequence)
    {
        // Run the coroutine. This will call the bound executeAndCheckForSuccessWrapper
        // function
        validation_sequence();
    }

    // The validation_function is done if the coroutine evaluates to false, which means
    // execution has "dropped out" the bottom of the function and there is no more work to
    // do. If this is the case then the validation_function has passed successfully
    return !static_cast<bool>(validation_sequence);
}
