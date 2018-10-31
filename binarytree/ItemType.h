/** 
 * @brief Prototype for the class used for data storage.
 *
 * This class exists for the purpose of decoupling as much as possible
 * the implementation and design of the binary tree from what type of data
 * it is actually storing.
 *
 * @author Jennifer Teissler
 */

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

class ItemType {
    public:
        enum Comparison {
            LESSER,
            EQUAL,
            GREATER
        };

        explicit ItemType(int value) : value(value) {};
        Comparison compareTo (ItemType & item) const;
        int getValue() const;

    private:
        int value;
};

#endif
