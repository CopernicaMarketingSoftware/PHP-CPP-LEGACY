/**
 *  Error.h
 *
 *  In PHP7 errors are thrown as Error objects, while in PHP5 errors immediately 
 *  cause a fatal crash. Because the PHP-CPP-LEGACY class only supports PHP5, 
 *  the Error class in this file is thus never thrown from PHP space to C++ space.
 *
 *  But to ensure that an extension can be compiled on PHP5 and PHP7, we have
 *  still added it to the source code, so that it will not cause compile
 *  errors.
 *
 *  But you can use it to throw fatal errors.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2019 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Begin of namespace
 */
namespace Php {

/**
 *  Class definition
 */
class PHPCPP_EXPORT Error : public Throwable
{
public:
    /**
     *  Constructor
     *  @param  message
     *  @param  code
     */
    Error(const std::string &message, int code = 0) : Throwable(message, code) {}
    
    /**
     *  Destructor
     */
    virtual ~Error() = default;
    
    /**
     *  Is this a native exception (one that was thrown from C++ code)
     *  @return bool
     */
    virtual bool native() const
    {
        // although it is native, we return 0 because it should not persist
        // as exception, but it should live on as zend_error() in stead
        return false;
    }

    /**
     *  Report this error as a fatal error
     *  @return bool
     */
    virtual bool report() const override;
                                                                              
};

/**
 *  End of namespace
 */
}

