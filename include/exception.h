/**
 *  Exception.h
 *
 *  Exception class that can be thrown and caught in C++ space and that
 *  will end up in or can originate from PHP space.
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
class Exception : public Throwable
{
public:
    /**
     *  Constructor
     *  @param  message
     *  @param  code
     */
    Exception(const std::string &message, int code = 0) : Throwable(message, code) {}
    
    /**
     *  Destructor
     */
    virtual ~Exception() = default;
};

/**
 *  End of namespace
 */
}

