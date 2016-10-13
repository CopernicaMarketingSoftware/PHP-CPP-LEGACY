/**
 *  LowerCase.h
 *
 *  Class to temporary convert a name to lowercase
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2016 Copernica BV
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
class LowerCase
{
private:
    /**
     *  The lowercase name
     *  @var char *
     */
    char *_name;

public:
    /**
     *  Constructor
     *  @param  name        the original name
     *  @param  size        size of the name
     */
    LowerCase(const char *name, size_t size) : 
        _name(zend_str_tolower_dup(name, size)) {}
        
    /**
     *  No copy'ing or moving
     *  @param  that
     */
    LowerCase(const LowerCase &that) = delete;
    LowerCase(LowerCase &&that) = delete;

    /**
     *  Destructor
     */
    virtual ~LowerCase()
    {
        // release the data
        efree(_name);
    }
    
    /**
     *  Expose internal value
     *  @return const char *
     */
    const char *value()
    {
        // expose member
        return _name;
    }
    
    /**
     *  Cast to a char *
     *  @return char *
     */
    operator char * () 
    {
        // expose member
        return _name;
    }
};

/**
 *  End of namespace
 */
}
