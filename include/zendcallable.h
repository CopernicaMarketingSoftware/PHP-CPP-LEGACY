/**
 *  zendcallable.h
 *
 *  A wrapper to handle a callback coming from
 *  within PHP
 *
 *  @author Martijn Otto <martijn.otto@copernica.com>
 *  @copyright 2016 Copernica B.V.
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Forward declarations
 */
struct _zval_struct;

/**
 *  Start namespace
 */
namespace Php {

/**
 *  Callback wrapper class
 */
class PHPCPP_EXPORT ZendCallable
{
private:
    /**
     *  Retrieve pointer to the base of the object implementation
     *
     *  @param  this_ptr    Pointer to the object we need the C++ instance for
     *  @return Pointer to base
     */
    static Base *instance(struct _zval_struct *this_ptr);

    /**
     *  Check whether we have received valid parameters
     *
     *  If this function returns false a warning will have been
     *  generated and the return value has been set to NULL.
     *
     *  @param  provided        The number of arguments provided
     *  @param  return_value    The return value to set on failure
     */
    static bool valid(int provided, struct _zval_struct *return_value);

    /**
     *  Retrieve the input parameters for the function
     *
     *  @param  provided        The number of arguments provided
     *  @param  this_ptr        The 'this' pointer for the object we are working on
     *  @return The input parameters
     */
    static Parameters parameters(int provided, struct _zval_struct *this_ptr);

    /**
     *  Handle exceptions
     *
     *  @param  exception   The exception to handle
     */
    static void handle(Throwable &exception);

    /**
     *  Yield (return) the given value
     *
     *  @param  return_value    The return_value to set
     *  @param  value           The value to return to PHP
     */
    static void yield(struct _zval_struct *return_value, std::nullptr_t value);
    static void yield(struct _zval_struct *return_value, Php::Value &&value);
public:
    /**
     *  Execute the callback
     *
     *  @param  ht                  Number of parameters passed by the user
     *  @param  return_value        Store the return value here
     *  @param  return_value_ptr    Another pointer to the return value
     *  @param  this_ptr            Pointer to "this" (the object the method is called on)
     *  @param  return_value_used   1 if the return value is used, 0 if not
     */
    template <typename T, void (T::*callback)()>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            (static_cast<T*>(instance(this_ptr))->*callback)();

            // there is no return value, so we just return null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    Data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, void (T::*callback)() const>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            (static_cast<T*>(instance(this_ptr))->*callback)();

            // there is no return value, so we just return null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    Data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, Value (T::*callback)()>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            auto result = (static_cast<T*>(instance(this_ptr))->*callback)();

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    Data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, Value (T::*callback)() const>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            auto result = (static_cast<T*>(instance(this_ptr))->*callback)();

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, void(T::*callback)(Parameters &parameters)>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            (static_cast<T*>(instance(this_ptr))->*callback)(params);

            // there is no return value, so we just reutrn null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, void(T::*callback)(Parameters &parameters) const>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            (static_cast<T*>(instance(this_ptr))->*callback)(params);

            // there is no return value, so we just return null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, Value (T::*callback)(Parameters &parameters)>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            auto result = (static_cast<T*>(instance(this_ptr))->*callback)(params);

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <typename T, Value (T::*callback)(Parameters &parameters) const>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // cast the base to the correct object and invoke the member
            auto result = (static_cast<T*>(instance(this_ptr))->*callback)(params);

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <void(*callback)()>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // execute the callback
            callback();

            // there is no return value, so we just return null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <Value(*callback)()>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // catch exceptions thrown by the C++ methods
        try
        {
            // execute the callback
            auto result = callback();

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <void(*callback)(Parameters &parameters)>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // execute the callback
            callback(params);

            // there is no return value, so we just return null
            yield(return_value, nullptr);
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }

    /**
     *  Execute the callback
     *
     *  @param  execute_data    data about the PHP call stack
     *  @param  return_value    The value we are returning to PHP
     */
    template <Value(*callback)(Parameters &parameters)>
    static void invoke(int ht, struct _zval_struct *return_value, struct _zval_struct **return_value_ptr, struct _zval_struct *this_ptr, int return_value_used)
    {
        // check parameter count
        if (!valid(ht, return_value)) return;

        // retrieve the parameters
        auto params = parameters(ht, this_ptr);

        // catch exceptions thrown by the C++ methods
        try
        {
            // execute the callback
            auto result = callback(params);

            // store the return value in the return_value
            yield(return_value, std::move(result));
        }
        catch (Throwable &exception)
        {
            // handle the exception
            handle(exception);
        }
    }
};

/**
 *  End namespace
 */
}
