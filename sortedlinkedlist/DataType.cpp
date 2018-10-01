/** 
 * @brief Implementation of DataType's comparison method.
 * @author Jennifer Teissler
 */

#include "DataType.h"

DataType::Comparison DataType::compareTo(DataType & item) const {
    if (this->value > item.getValue()) {
        return GREATER; // this object is valued as greater than the parameter
    } 
    else if (this->value < item.getValue()) {
        return LESSER;  // this object is valued as lesser than the parameter
    } 
    else {
        return EQUAL;   // this object is valued as functionally equal to the parameter
    }
};

int DataType::getValue() const {
    return this->value; // gets the actual data from within the wrapper class
}