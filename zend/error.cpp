/**
 *  Error.cpp
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace Php {

/**
 *  Report this error as a fatal error
 *  @return bool
 */
bool Error::report() const
{
    // report the error
    zend_error(E_ERROR, "%s", what());
    
    // return true: it was reported
    return true;
}
    
/**
 *  End of namespace
 */
}

