/**
 *  callable.cpp
 *
 *  A wrapper to handle a callback coming from
 *  within PHP
 *
 *  @author Martijn Otto <martijn.otto@copernica.com>
 *  @copyright 2016 Copernica B.V.
 */
#include "includes.h"

/**
 *  Start namespace
 */
namespace Php {

/**
 *  Retrieve pointer to the object
 *
 *  @param  this_ptr    Pointer to the object we need the C++ instance for
 *  @return Pointer (as void because this cannot be templated!)
 */
Base *ZendCallable::instance(struct _zval_struct *this_ptr)
{
    // we need the tsrm_ls variable
    TSRMLS_FETCH();

    // find the object implementation and retrieve the base object
    return ObjectImpl::find(this_ptr TSRMLS_CC)->object();
}

/**
 *  Check whether we have received valid parameters
 *
 *  If this function returns false a warning will have been
 *  generated and the return value has been set to NULL.
 *
 *  @param  return_value    The return value to set on failure
 */
bool ZendCallable::valid(int provided, struct _zval_struct *return_value)
{
    // we need the tsrm_ls variable
    TSRMLS_FETCH();

    // how many parameters do we need as a bare minimum?
    int required = EG(current_execute_data)->function_state.function->common.required_num_args;

    // if we have the required minimum number of arguments there is no problem
    if (provided >= required) return true;

    // retrieve the function name to display the error
    auto *name = get_active_function_name(TSRMLS_C);

    // we do not have enough input parameters, show a warning about this
    Php::warning << name << "() expects at least " << required << " parameter(s), " << provided << " given" << std::flush;

    // set the return value to NULL
    RETVAL_NULL();

    // we are not in a valid state
    return false;
}

/**
 *  Retrieve the input parameters for the function
 *
 *  @param  provided        The number of arguments provided
 *  @param  this_ptr        The 'this' pointer for the object we are working on
 *  @return The input parameters
 */
Parameters ZendCallable::parameters(int provided, struct _zval_struct *this_ptr)
{
    // retrieve the TSRMLS structure
    TSRMLS_FETCH();

    // parse and return the parameters
    return ParametersImpl{ this_ptr, provided TSRMLS_CC };
}

/**
 *  Handle exceptions
 *
 *  @param  exception   The exception to handle
 */
void ZendCallable::handle(Exception &exception)
{
    // we need the tsrm_ls variable
    TSRMLS_FETCH();

    // pass it on to the exception handler
    process(exception TSRMLS_CC);
}

/**
 *  Yield (return) the given value
 *
 *  @param  return_value    The return_value to set
 *  @param  value           The value to return to PHP
 */
void ZendCallable::yield(struct _zval_struct *return_value, std::nullptr_t value)
{
    // set the return value to null
    RETVAL_NULL();
}

/**
 *  Yield (return) the given value
 *
 *  @param  return_value    The return_value to set
 *  @param  value           The value to return to PHP
 */
void ZendCallable::yield(struct _zval_struct *return_value, Php::Value &&value)
{
    // copy the value over to the return value
    RETVAL_ZVAL(value._val, 1, 0);
}

/**
 *  End namespace
 */
}
