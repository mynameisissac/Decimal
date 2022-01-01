#include "../include/Decimal.h"
using namespace std;


// default constructor
Decimal::Decimal()
{
    size = 1;
    content = new char[size];
    content[0] = '0';
}

// helper function that return the number of digits of a int
int countDigit(int inputNum)
{
    int count = 1;
    while (inputNum / 10 != 0)
    {
        inputNum /= 10;
        count++;
    }

    return count;
}

// conversion constructor (int type)
Decimal::Decimal(int input)
{
    size = countDigit(input);
    int firstNum_index = 0;
    if (input < 0)
    {
        firstNum_index = 1;
        input = abs(input);         // remove the negative sign
        size++;                     // minus sign take one digit
        content = new char[size];
        content[0] = '-'; // assign the first element as minus sign
    }
    else
        content = new char[size];

    // assign from the back of the array
    for (int i = size - 1; i >= firstNum_index; i--)
    { // note that the last index is size-1
        content[i] = char(input % 10 + 48);
        input /= 10;
    }
}

// conversion constructor (cstring type)
Decimal::Decimal(const char *input)
{
    int count = 0; // count number of digit (without '\0')
    for (int i = 0; input[i] != '\0'; i++)
    {
        count++;
    }

    size = count;
    content = new char[size];
    for (int i = 0; i < size; i++)
    { // assign digits
        content[i] = input[i];
    }
}

// deep copy constructor
Decimal::Decimal(const Decimal &another)
{
    size = another.size;
    content = new char[size]; // deep copy the dynamic array
    for (int i = 0; i < size; i++)
    {
        content[i] = another.content[i];
    }
}

// destructor
Decimal::~Decimal()
{
    // deallocate the dynamic array
    delete [] content;
    content = nullptr;
}


/**
 *  @param arr pointer to array of char which is passed by reference
 *  @param size the size to the array which will also be changed
 *  remove the first char in the array and shift all the elements to the left by 1
 *  Note that the arr pointer is passed by reference
 */
void removeBeginning(char*& arr, int& size)
{
    char* temp = new char[--size];

    for (int i=1; i < size + 1; i++)
        temp[i - 1] = arr[i];

    delete [] arr;          // release the old array pointed by arr
    arr = temp;             // the pointer point to the new dynamic array
}

/**
 *  remove the last char in the array and shift all the elements to the right by 1
 * @param arr pointer to array of char which is passed by reference
 * @param size the size of the array which will also be modified
 */
void removeLast(char*& arr, int& size)
{
    char* temp = new char[--size];

    for (int i=0; i < size; i++)
        temp[i] = arr[i];

    delete [] arr;          // release the old array pointed by arr
    arr = temp;             // the pointer point to the new dynamic array
}

/**
 * insert a new char at the beginning of the array
 * @param arr pointer to array of char which is passed by reference
 * @param size the size of the array which will also be modified
 * @param newElement the char that are going to be inserted
 */
void insertBeginning(char*& arr, int& size, char newElement)
{
    char* temp = new char[++size];  // increase the size
    temp[0] = newElement;           // insert the new char

    for (int i = 1; i < size; i++)
        temp[i] = arr[i - 1];

    delete [] arr;          // release the old array pointed by arr
    arr = temp;             // the pointer point to the new dynamic array
}

/**
 * add a new char at the end of the array of char
 * @param arr the pointer to array of char which is passed by reference
 * @param size the size of the array which is modifiable
 * @param newElement the char that are going to be inserted
 */
void insertLast(char*& arr, int& size, char newElement)
{
    char* temp = new char[++size];

    for (int i=0; i < size - 1; i++)
        temp[i] = arr[i];

    temp[size - 1]  = newElement;   // insert the new char at the end
    delete [] arr;          // release the old array of char
    arr = temp;             // the pointer point to the new dynamic array
}

// check if a number is negative
bool Decimal::isNegative() const
{
    return content[0] == '-'; // return true if the first digit is '-'
}

/**
 * @return a Decimal object with opposite sign but same value
 */
Decimal Decimal::flipSign() const
{
    Decimal newDecimal(*this);      // copy constructor to copy this decimal number

    // speical case : the number is '0'
    if (content[0] == '0' && size == 1)
        return newDecimal;

    else if (!this->isNegative())   // if the number is positive
        insertBeginning(newDecimal.content, newDecimal.size, '-');    // insert the minus sign, i.e. '-' char at the beginning
    else                            // if the number is negative
        removeBeginning(newDecimal.content, newDecimal.size);                   // remove the '-' char at the beginning

    return newDecimal; // return by value the new Decimal object
}

// Helper functions
int min(int x, int y) { return (x < y) ? x : y; }

int max(int x, int y) { return (x > y) ? x : y; }

/**
 * find the position of decimal point in the array of char
 * @param targetArr the pointer point to the dynamic array of char
 * @param size the size of the array
 * @return the position of '.' , return the size of the array if not found
 */
int findPoint(const char *targetArr, int size) // size of the array is also passed
{
    for (int i = 0; i < size; i++)
    {
        if (targetArr[i] == '.')
            return i;
    }
    return size; // return size if not found
}

// Return true if this number is larger than another number. Return false otherwise.
bool Decimal::isLargerThan(const Decimal &another) const
{
    // if some of them are negative
    if (this->isNegative() && another.isNegative())
    { // if both of them are negative
        // recursion here to check with two non negative number
        // reverse the order
        return (another.flipSign().isLargerThan(this->flipSign()));
    }
    else if (this->isNegative()) // if only this number is negative
        return false;
    else if (another.isNegative())
        return true;

    // if both of them are not negative
    int posOfPoint_this = findPoint(content, size);         // get the position of point first
    int posOfPoint_another = findPoint(another.content, another.size);

    if (posOfPoint_this > posOfPoint_another)
        return true;
    else if (posOfPoint_this < posOfPoint_another)
        return false;
    // if both decimal point are in same position
    else
    {
        for (int i = 0; i < min(size, another.size); i++){
            if (content[i] == another.content[i])       // if they are the same, skip to the next iteration
                continue;
            else if (content[i] > another.content[i])
                return true;
            else if (content[i] < another.content[i])
                return false;
        }

        if (size > another.size) // if this number has more digits after comparing all digits that both have
            return true;
        else
            return false;
    }
}

/**
 * create a new dynamic array of char with all elements initialized to null char i.e. '\0'
 * @param size the size of the array
 * @return a pointer point to the dynamic array
 */
char* newCharArray(int size)
{
    char* temp = new char[size];    // dynamically allocated memory for array of char

    for (int i=0; i < size; i++)    // initialize the array of char
        temp[i] = '\0';

    return temp;            // return the pointer
}

/**
 * trim the array of char by removing all the redundant zero
 * @param arr a pointer to array of char which is passed by reference
 * @param size size of the array which is modifiable
 */
void removeZero(char*& arr, int& size)
{
    bool isNegative = false;        // check if the number is negative
    bool hasPoint = (findPoint(arr, size) != size);          // check if the number have decimal point
    if (arr[0] == '-') {
        isNegative = true;
        removeBeginning(arr, size);         // remove the negative sign first, add it back at the end of the function
    }

    // keep remove the first char if it is zero at the beginning
    while(arr[0] == '0' && size != 1)                   // when there is only 1 zero, won't remove it
        removeBeginning(arr,size);

    // keep remove the last char if it is zero at the end and this number has a decimal point
    while(arr[size - 1] == '0' && size != 1 && hasPoint)
        removeLast(arr,size);

    // remove the decimal point if the last digit is decimal point after trimming zero
    if (arr[size - 1] == '.')
        removeLast(arr, size);

    if (isNegative)                             // add the negative sign back if the number is negative
        insertBeginning(arr, size, '-');
}

/**
 * a helper function convert char to decimal digit value, i.e. '2' -> 2
 * @param arr the pointer point to the dynamic array of char
 * @param size the size of the array
 * @param targetPos the position of the char to be converted in the array
 * @return int digit value
 */
int charToInt(const char* arr, int size, int targetPos)
{
    const int asciiIndex = int('0');            // 48 which is the ascii index value of '0'
    if (targetPos < 0 || targetPos > size - 1)  // check if it go beyond the array boundary
        return 0;
    else if (arr[targetPos] == '.')             // return 46 which is ascii value of '.' char when it is '.'
        return 46;                      

    return int(arr[targetPos]) - asciiIndex;
}


/**
 * @param another the Decimal object which is going to be add
 * @return return the result of Adding this number with another
 */
Decimal Decimal::add(const Decimal &another) const
{
    if (this->isNegative() && another.isNegative())                      // if both number are negative
        return this->flipSign().add(another.flipSign()).flipSign();      // flip the sign after adding the positive value of them
    
    int posOfPoint_this = findPoint(content, size);         // find the position of the decimal point
    int posOfPoint_another = findPoint(another.content, another.size);
    int pointDifference = abs(posOfPoint_this - posOfPoint_another);  // absolute difference

    int sum = 0;
    int carry = 0;
    int from = 0;
    // if both of the numbers do not have decimal point
    if (posOfPoint_this == this->size && posOfPoint_another == another.size)        
        from = max(size, another.size) - 1;             // no need consider point difference in this case
    else{       // one of them must have decimal point
        // calculate the number of decimal places
        int numOfPrecision_this = max(size - 1 - posOfPoint_this , 0);        // use max to ensure the minimum value is 0
        int numOfPrecision_another = max(another.size - 1 - posOfPoint_another, 0);
        from = max(posOfPoint_this, posOfPoint_another) + max(numOfPrecision_this, numOfPrecision_another);
    }
    // if only one of them is negative, i.e. XOR exclusive or
    if ( (this->isNegative() || another.isNegative() ) && !(this->isNegative() && another.isNegative()) )
    {
        Decimal tempThis(*this);     // copy constructors to clone the two Decimal objects
        Decimal tempAnother(another);
        // this process ensure both number are positive while subtracting
        if (this->isNegative()){                    // if the negative number is this number
            delete [] tempThis.content;             // prevent memory leak
            // deep copying
            Decimal flipThis = this->flipSign();        // copy constructor
            tempThis.size = flipThis.size;
            tempThis.content = new char[tempThis.size];
            for (int i=0; i < tempThis.size; i++)
                tempThis.content[i] = flipThis.content[i];
        }
        else{                                       // else if the negative number is another
            delete [] tempAnother.content;
            // deep copying
            Decimal flipAnother = another.flipSign();
            tempAnother.size = flipAnother.size;
            tempAnother.content = new char[tempAnother.size];
            for (int i=0; i < tempAnother.size; i++)
                tempAnother.content[i] = flipAnother.content[i];       
        }

        // update some variables values
        posOfPoint_this = findPoint(tempThis.content, tempThis.size);
        posOfPoint_another = findPoint(tempAnother.content, tempAnother.size);
        pointDifference = abs(posOfPoint_this - posOfPoint_another);
        // if both of the numbers do not have decimal point
        if (posOfPoint_this == tempThis.size && posOfPoint_another == tempAnother.size)
            from = max(tempThis.size, tempAnother.size) - 1;
        else{   // one of them has decimal point
            int numOfPrecision_tempThis = max(tempThis.size - 1 - posOfPoint_this , 0);        // use max to ensure the minimum value is 0
            int numOfPrecision_tempAnother = max(tempAnother.size - 1 - posOfPoint_another, 0);
            from = max(posOfPoint_this, posOfPoint_another) + max(numOfPrecision_tempThis, numOfPrecision_tempAnother);
        }
        // use a array of char to store the result
        int sizeOfArr = from + 1;
        char* addResult = newCharArray(sizeOfArr);


        for (int i = from; i >= 0; i--)
        {   // this number - another 
            if (tempThis.isLargerThan(tempAnother))       
            {
                if (charToInt(tempThis.content, tempThis.size, i) == 46 || charToInt(tempAnother.content, tempAnother.size, i - pointDifference) == 46)     // when meeting special char ('.')
                {
                    addResult[i] = '.';
                    continue; // skip this iteration
                }
                sum = charToInt(tempThis.content, tempThis.size, i) - charToInt(tempAnother.content, tempAnother.size, i - pointDifference) + carry;
            }
            else                                            
            {// another - this number
                if (charToInt(tempAnother.content, tempAnother.size, i) == 46 || charToInt(tempThis.content, tempThis.size, i - pointDifference) == 46)
                {
                    addResult[i] = '.';
                    continue; // skip this iteration
                }
                sum = charToInt(tempAnother.content, tempAnother.size, i) - charToInt(tempThis.content, tempThis.size, i - pointDifference) + carry;
            }
            
            carry = (sum < 0) ? -1 :0;
            sum += (sum < 0) ? 10 : 0;          // convert the sum back to a positive digit by adding 10
            addResult[i] = char(sum + 48);      // convert digit to char
        }


        removeZero(addResult,sizeOfArr);
        insertLast(addResult, sizeOfArr, '\0');         // convert the array to cstring by adding one null char at the end
        Decimal newDecimal(addResult);
        delete [] addResult;                         // avoid memory leak
        // consider when we need to add the minus sign in the front
        if (this->isNegative() && tempThis.isLargerThan(tempAnother)    
            ||  another.isNegative() && tempAnother.isLargerThan(tempThis))
            return newDecimal.flipSign();             // add the minus sign in the front

        return newDecimal;        // return an unnamed object by value  
    }
    else        // they are both positive
    {
        // use a array of char to store the result
        int sizeOfArr = from + 1;
        char* addResult = newCharArray(sizeOfArr);

        for (int i = from; i >= 0; i--)
        {
            if (this->isLargerThan(another))
            {
                if (charToInt(content, size, i) == 46 || charToInt(another.content, another.size, i - pointDifference) == 46)     // when meeting special char (non digit)
                {
                    addResult[i] = '.';
                    continue; // skip this iteration
                }
                sum = charToInt(content, size, i) + charToInt(another.content, another.size, i - pointDifference) + carry;
            }
            else
            {
                if (charToInt(another.content, another.size, i) == 46 || charToInt(content, size, i - pointDifference) == 46)
                {
                    addResult[i] = '.';
                    continue; // skip this iteration
                }
                sum = charToInt(content, size, i - pointDifference) + charToInt(another.content, another.size, i) + carry;
            }
            carry = sum / 10;
            sum = sum % 10;
            addResult[i] = char(sum + 48); // convert digit to char
        }

        // if there is carry digit
        if (carry == 1)
            insertBeginning(addResult, sizeOfArr, char(1 + 48));        // add the carry digit 1 at the beginning

        removeZero(addResult,sizeOfArr);
        insertLast(addResult, sizeOfArr, '\0');
        Decimal newDecimal(addResult);
        delete [] addResult;
        return newDecimal;        
    }
}

// Add this number with another and store the result in this number.
void Decimal::addToSelf(const Decimal& another)
{
    // newDecimal store the result of addition
    Decimal newDecimal(this->add(another));          // copy constructor

    // deep copy of newDecimal to this object
    delete [] this->content;                          // avoid memory leak
    this->size = newDecimal.size;
    this->content = new char[this->size];

    for(int i=0; i < this->size; i++)
        this->content[i] = newDecimal.content[i];

} 

// Multiply this number with ten to the power of the given power and return the result.
// assume the power given is always non-negative
Decimal Decimal::multiplyByPowerOfTen(int power) const
{
    int newsize = size;
    char* newcontent = newCharArray(newsize);
    for (int i=0; i < size; i++)                // copy this->content into newcontent
        newcontent[i] = content[i];

    // first adjust the position of decimal point
    int posOfPoint = findPoint(newcontent, newsize);
    int numOfPrecision = newsize - posOfPoint - 1 + int(posOfPoint == size);        // calculate the number of decimal places

    for (int i = posOfPoint; i < power + posOfPoint && i < newsize - 1; i++){       // ensure i < newsize - 1
        // keep swapping the decimal point and its neighbour
        char temp = newcontent[i];
        newcontent[i] = newcontent[i + 1];
        newcontent[i + 1] = temp;
    }

    if (newcontent[newsize - 1] == '.')                       // if the decimal point is at the end
        removeLast(newcontent, newsize);

    for (int i=0; i < power - numOfPrecision; i++)               // second, insert '0' with correct number
        insertLast(newcontent, newsize, '0');

    removeZero(newcontent, newsize);                    // call the removeZero before adding null char
    insertLast(newcontent, newsize, '\0');      // convert newcontent to cstring
    Decimal newDecimal(newcontent);
    delete [] newcontent;
    return newDecimal;
}

/**
 * check if a number need to insert meaningful zero at the beginning, and add it
 * @param arr a pointer point to a dynamic array of char which is passed by reference
 * @param size the size of the array which is modifiable
 */
void addZeroAtBeginning(char*& arr, int& size)
{
    if (arr[0] == '-'){         // if the number is negative
        removeBeginning(arr, size);             // temporarily remove the '-'
        if (arr[0] == '.')      // if it starts '.' but not '0'
            insertBeginning(arr, size, '0');
        insertBeginning(arr, size, '-');    // add back the '-' after check and inserting '0'
    }
    else
        if (arr[0] == '.')      // if it starts '.' but not '0'
            insertBeginning(arr, size, '0');
}

// Multiply this number with a single-digit number given by multiplier and return the result.  multiplier always in [0, 9]
Decimal Decimal::multiplyBySingleDigit(int multiplier) const
{
    if (multiplier == 0)
        return Decimal(0);
    else if (multiplier == 1)
        return *this;          // copy constructor
    else if (this->isNegative())                // if this number is negative, flip it first to multiply then flip it again to negative
        return this->flipSign().multiplyBySingleDigit(multiplier).flipSign();

    int product = 0;
    int carry = 0;
    int resultSize = size;
    char* multiplyResult = newCharArray(resultSize);

    for (int i = resultSize - 1; i >= 0; i--)         // do the multiplication from the back
    {
        if (content[i] == '.' ){
            multiplyResult[i] = content[i];
            continue;
        }
        product = charToInt(content, size, i) * multiplier + carry;
        carry = product /10;
        product = product % 10;
        multiplyResult[i] = char(product + 48);
    }

    if (carry != 0)
        insertBeginning(multiplyResult, resultSize, char(carry + 48));      // add the carry digit

    removeZero(multiplyResult,resultSize);
    addZeroAtBeginning(multiplyResult, resultSize);
    insertLast(multiplyResult, resultSize, '\0');       // convert the result to cstring
    Decimal newDecimal(multiplyResult);
    delete [] multiplyResult;
    return newDecimal;
}


// Multiply this number with another and return the result.
Decimal Decimal::multiply(const Decimal& another) const
{
    if (another.content[0] == '0' && another.size == 1)         // everything multiply zero will get zero
        return another;
    else if (content[0] == '0' && size == 1)
        return (*this);
    
    else if (another.content[0] == '1' && another.size == 1)         // everything times 1 will be itself
        return *this;
    else if (content[0] == '1' && size == 1)
        return another;
    
    // create a Decimal object for storing multiplication result 
    Decimal result;                             // default constructor
    int posOfPoint_another = findPoint(another.content, another.size);
    
    // let this number be the multiplicand here, another being the multiplier
    int power_offset = 0;
    int To = 0;
    if (another.isNegative())           // if another is negative, do multiplication to the digit after '-'
        To = 1;
    for (int i = another.size - 1; i >= To; i--)
    {
        if (another.content[i] == '.'){
            power_offset = 1;               // set the power_offset when passing the '.'
            continue;
        }
        // copy constructor to store each digit multiplication result into Decimal object product
        int power = another.size - 1 - i - power_offset;
        Decimal product = this->multiplyBySingleDigit(int(another.content[i]) - 48).multiplyByPowerOfTen(power);
        // add the product into result itself
        result.addToSelf(product);
    }

    // if another has decimal point, then need to adjust the position of decimal point of the result
    if(posOfPoint_another != another.size)
    {
        int posOfPoint = findPoint(result.content, result.size);        // the position of decimal point of result.content
        if (posOfPoint == result.size)                                  // add one decimal point at the end if it does not have
            insertLast(result.content, result.size, '.');
        int numOfPrecision_another = another.size - posOfPoint_another - 1 + int(posOfPoint_another == another.size);        // calculate the number of decimal places

        int move = 0;       // record how many time the decimal point move
        for (int i = posOfPoint; i > posOfPoint - numOfPrecision_another && i >= 1; i--){       // ensure i >= 1
            // keep swapping the decimal point and its neighbour
            char temp = result.content[i];
            result.content[i] = result.content[i - 1];
            result.content[i - 1] = temp;
            move++;
        }

        // if the decimal point has not finished moving because of insufficient places for it to move
        for (; move < numOfPrecision_another; move++){
            insertBeginning(result.content, result.size, '0');      // add padding zero
            int newPosOfPoint = findPoint(result.content, result.size);
            char temp = result.content[newPosOfPoint];
            result.content[newPosOfPoint] = result.content[newPosOfPoint - 1];
            result.content[newPosOfPoint - 1] = temp;
        }

    }

    removeZero(result.content, result.size);
    addZeroAtBeginning(result.content, result.size);
    insertLast(result.content, result.size, '\0');      // convert to cstring
    return Decimal(result.content); // so here we return another object constructed by cstring
}

// Subtract another number from this number and return the result.
Decimal Decimal::subtract(const Decimal& another) const
{
    // this number is subtracted by another
    return this->add(another.flipSign());
}

// Return the number of digits before the decimal point.
int Decimal::countDigitsBeforeDP() const
{
    if (this->isNegative())                     // if number is negative, count its positive value
        return this->flipSign().countDigitsBeforeDP();

    return findPoint(content,size);
}

// Return the number of digits after the decimal point.
int Decimal::countDigitsAfterDP() const
{
    int posOfPoint = findPoint(content,size);
    if (posOfPoint == size)             // there is no decimal point, so no digits after decimal point
        return 0;
    else
        return size - posOfPoint - 1;
}

