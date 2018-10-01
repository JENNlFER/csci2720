/** 
 * @brief Prototype for the class used for data storage.
 *
 * This class exists for the purpose of decoupling as much as possible
 * the implementation and design of the LinkedList from what type of data
 * it is actually storing.
 *
 * @author Jennifer Teissler
 */

#ifndef DATATYPE_H
#define DATATYPE_H

class DataType {
    public:
        enum Comparison {
            LESSER,
            EQUAL,
            GREATER
        };

        explicit DataType(int value) : value(value) {};
        Comparison compareTo (DataType & item) const;
        int getValue() const;

    private:
        int value;
};

#endif
