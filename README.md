# Structures-and-algorithms-for-data-processing

## SIAOD1 (EN)
Subject. Bitwise operations and their applications.
Target: Gaining skills in using bitwise operations in algorithms.
Exercise:
Develop a program that will demonstrate the implementation of variant exercises. The results of the exercise and input values are displayed on the monitor in decimal and binary form.
Exercise requirements:
1. Define a variable of integer type, assign a value to it using a constant in hexadecimal notation. Develop a function that will set the bits of the initial value of a variable specified in the 2. task to the value 1, using the appropriate mask and bitwise operation.
3. Develop a function that resets the specified bits of the initial value of an integer variable entered by the user, using the appropriate mask and bitwise operation.
4. Develop a function that multiplies the value of an integer variable entered by the user by a factor using the appropriate bitwise operation.
5. Develop a function that divides the value of an integer variable entered by the user by a divisor using the appropriate bitwise operation.
Task1: 3,5,11
Task2: four juniors
Task3: 128
Task4: 128
Task5: Set nth bit to 1 using mask2(The mask is initialized to one in the most significant bit)

## SIAOD2 (EN)
Subject. External data structures: text and binary files.
Target. Gain skills in using C++ file streams (or C language files) to manage text and binary files.
Exercise 1.
1. Develop a program to manage a text file.
  1.1. Implementation of I/O based on C++ file streams: ofstream, ifstream.
  1.2. The name of the physical file is entered by the user and passed to the processing functions via a parameter.
  1.3. Develop functions to perform operations on a text file:
    1.3.1. creating an ASCII text file containing decimal numbers, several numbers per line;
    1.3.2. output the contents of a text file;
    1.3.3. adding a new line to the end of the file;
    1.3.4. read the value of a number, indicating its serial number in the file, and return its value;
    1.3.5. determine the number of numbers in the file.
    1.3.6. implement additional operations defined by options
Task1: Create a new file from the values of the original one, copying only prime numbers into it, placing each on a separate line of the text file.   

Exercise 2.
2. Develop a binary file management program with fixed-length records. General requirements: the file consists of records of a certain structure, according to the option. Records have a key that is unique within the file.
  2.1. Develop a binary file recording structure according to the assignment option.
  2.2. Prepare test data in a text file with ASCII encoding, in accordance with the structure of the variant record. When opening a file, check its existence and opening.
  2.3. The file name is entered by the user.
  2.4. When opening a file, provide control over the existence and opening of the file.
  2.5. When using the mechanism of direct access to a file record, check the presence of a record with a given number in the file.
  2.6. Develop functions to perform operations:
    2.6.1. converting test data from a text file to a binary file;
    2.6.2. converting data from a binary file to a text file;
    2.6.3. output all entries of a binary file;
    2.6.4 accessing a record by its serial number in the file, using the mechanism of direct access to a record in a binary file;
    2.6.5. Delete a record with a given key value by replacing it with the last record.
    2.6.6. manipulating entries in a binary file according to additional operations defined in the variant;
    
