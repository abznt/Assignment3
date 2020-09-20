#ifndef CELLVALUE_H
#define CELLVALUE_H

/**
 * @brief The TttValue enum defines the possible contents of a board cell
 */
enum class TttValue : int
{
    X = 1,    /**< An 'X' maps to the integer value 1 */
    O = -1,   /**< An 'O' maps to the integer value -1 */
    EMPTY = 0 /**< An empty cell maps to the integer value 0 */
};

#endif // CELLVALUE_H
