#include "software/coroutines/function_validator.h"

#include <gtest/gtest.h>

#include <boost/coroutine2/all.hpp>

#include "software/coroutines/validation_function.h"
#include "software/test_util/test_util.h"

/**
 * NOTES
 * * Passes when storing a list of pointers to FunctionValidators, fails when using
 *   objects directly
 */
TEST(FunctionValidatorTest, coroutine_error_with_single_variable_on_stack_passes) {
    auto world_ptr = std::make_shared<World>(::Test::TestUtil::createBlankTestingWorld());
    world_ptr->mutableBall() = Ball(Point(-1, 0), Vector(0, 0), Timestamp::fromSeconds(0));

    ValidationFunction validation_function = [](std::shared_ptr<World> world,
                                                ValidationCoroutine::push_type& yield) {
        while (world->ball().position().x() < 0)
        {
            yield();
        }
    };
    std::vector<ValidationFunction> validation_functions = {validation_function};

    FunctionValidator function_validator(validation_functions.at(0), world_ptr);

    function_validator.executeAndCheckForSuccess();

    FunctionValidator other_function_validator = std::move(function_validator);
//    std::cout << "STACK " << &function_validator << " , " << &other_function_validator << std::endl;
    other_function_validator.executeAndCheckForSuccess();
    function_validator.executeAndCheckForSuccess();
}


TEST(FunctionValidatorTest, coroutine_error_with_vectors) {
    auto world_ptr = std::make_shared<World>(::Test::TestUtil::createBlankTestingWorld());
    world_ptr->mutableBall() = Ball(Point(-1, 0), Vector(0, 0), Timestamp::fromSeconds(0));

    ValidationFunction validation_function = [](std::shared_ptr<World> world,
                                                ValidationCoroutine::push_type& yield) {
        while (world->ball().position().x() < 0)
        {
            yield();
        }
    };
    std::vector<ValidationFunction> validation_functions = {validation_function};

    std::vector<FunctionValidator> function_validators;
    for (ValidationFunction vf : validation_functions)
    {
        // DOES MEMORY GET MOVED BEFORE OR AFTER THE INITIALIZATION LIST?
        function_validators.emplace_back(FunctionValidator(validation_function, world_ptr));
    }

    // Both of these methods of calling the validators fail
    function_validators.at(0).executeAndCheckForSuccess();
//    std::all_of(
//            function_validators.begin(), function_validators.end(),
//            [](FunctionValidator &fv) { return fv.executeAndCheckForSuccess(); });
}

TEST(FunctionValidatorTest, coroutine_error_with_vectors_of_pointers_passes) {
    auto world_ptr = std::make_shared<World>(::Test::TestUtil::createBlankTestingWorld());
    world_ptr->mutableBall() = Ball(Point(-1, 0), Vector(0, 0), Timestamp::fromSeconds(0));

    ValidationFunction validation_function = [](std::shared_ptr<World> world,
                                                ValidationCoroutine::push_type& yield) {
        while (world->ball().position().x() < 0)
        {
            yield();
        }
    };
    std::vector<ValidationFunction> validation_functions = {validation_function};

    std::vector<std::shared_ptr<FunctionValidator>> function_validators;
    for (ValidationFunction vf : validation_functions)
    {
        // DOES MEMORY GET MOVED BEFORE OR AFTER THE INITIALIZATION LIST?
        function_validators.emplace_back(std::make_shared<FunctionValidator>(validation_function, world_ptr));
    }

    function_validators.at(0)->executeAndCheckForSuccess();
}

TEST(FunctionValidatorTest, coroutine_error_with_pointer_moved_to_stack_fails) {
    auto world_ptr = std::make_shared<World>(::Test::TestUtil::createBlankTestingWorld());
    world_ptr->mutableBall() = Ball(Point(-1, 0), Vector(0, 0), Timestamp::fromSeconds(0));

    ValidationFunction validation_function = [](std::shared_ptr<World> world,
                                                ValidationCoroutine::push_type& yield) {
        while (world->ball().position().x() < 0)
        {
            yield();
        }
    };
    std::vector<ValidationFunction> validation_functions = {validation_function};

    std::vector<std::unique_ptr<FunctionValidator>> function_validators;
    for (ValidationFunction vf : validation_functions)
    {
        // DOES MEMORY GET MOVED BEFORE OR AFTER THE INITIALIZATION LIST?
        function_validators.emplace_back(std::make_unique<FunctionValidator>(validation_function, world_ptr));
    }

    // Move the FunctionValidator from the heap to the stack
    FunctionValidator function_validator_on_stack = std::move(*(function_validators.at(0)));

    function_validator_on_stack.executeAndCheckForSuccess();
}

TEST(FunctionValidatorTest, coroutine_error_with_variables_moved_between_heaps) {
    auto world_ptr = std::make_shared<World>(::Test::TestUtil::createBlankTestingWorld());
    world_ptr->mutableBall() = Ball(Point(-1, 0), Vector(0, 0), Timestamp::fromSeconds(0));

    ValidationFunction validation_function = [](std::shared_ptr<World> world,
                                                ValidationCoroutine::push_type& yield) {
        while (world->ball().position().x() < 0)
        {
            yield();
        }
    };
    std::vector<ValidationFunction> validation_functions = {validation_function};

//    std::vector<std::unique_ptr<FunctionValidator>> function_validators;
//    for (ValidationFunction vf : validation_functions)
//    {
//        // DOES MEMORY GET MOVED BEFORE OR AFTER THE INITIALIZATION LIST?
//        function_validators.emplace_back(std::make_unique<FunctionValidator>(validation_function, world_ptr));
//    }

    // Move the FunctionValidator from the heap to the stack
    std::unique_ptr<FunctionValidator> function_validator_on_heap = std::make_unique<FunctionValidator>(validation_functions.at(0), world_ptr);
    std::unique_ptr<FunctionValidator> function_validator_on_heap2 = std::make_unique<FunctionValidator>(validation_functions.at(0), world_ptr);

    function_validator_on_heap->executeAndCheckForSuccess();
    std::cout << "HEAP: " << function_validator_on_heap << ", " << function_validator_on_heap2 << std::endl;

    *function_validator_on_heap = std::move(*function_validator_on_heap2);
    std::cout << "HEAP: " << function_validator_on_heap << ", " << function_validator_on_heap2 << std::endl;

    function_validator_on_heap->executeAndCheckForSuccess();
}
