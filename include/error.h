/**
 *  Error.h
 *
 *  Unused Error class. In PHP7 errors are thrown as Error objects, while in PHP5
 *  errors immediately cause a fatal crash. Because the PHP-CPP-LEGACY class
 *  only supports PHP5, the Error class in this file is thus not in use and
 *  should not be used.
 *
 *  But to ensure that an extension can be compiled on PHP5 and PHP7, we have
 *  still added it to the source code, so that it will not cause compile
 *  errors.
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
class Error : public Throwable
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
};

/**
 *  End of namespace
 */
}

