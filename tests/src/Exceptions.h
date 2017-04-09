#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

/***********************************
 ***********************************
 *****Do not modify this file. *****
 ***********************************
 ***********************************/

#include <exception>

/** Do not modify this class. */
class MissingImplementationException : public std::exception {
    virtual const char* what() const throw() { return "Did you fill in this function?"; }
};

#endif //EXCEPTIONS_H
