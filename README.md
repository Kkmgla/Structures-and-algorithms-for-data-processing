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
Record structure: 
Airport (the arrival board for passenger flights saves all data in a file): point of departure, flight number, date of arrival, time of arrival, information about arrival delay in hours.
Add. operation:
1. Generate information on flights delayed on a specified date in a new binary file.
2. Change the arrival time for a given flight to a new value.

Subject. Using a hash table to look up data in a binary file with fixed-length entries.
Target. Gain skills in developing hash tables and using them when searching for data in other data structures (files).

## SIAOD3 (EN)
Exercise 1.
1. Develop an application that uses a hash table to directly access records of the binary file implemented in Practice 2.
2. Create an application and include three header files: hash table control, binary file control (lab 2), binary file control with hash table.
3. To provide direct access to a record in a file, a hash table element must include the required fields: the key of the record in the file, the number of the record with this key in the file. The element may contain other fields required by the method (specified in your variant) that resolves the collision.
4. Hash table management
  	4.1. Determine the structure of the hash table element and the structure of the hash table according to the collision resolution method specified in the option. Place definitions in the appropriate header file. 		Place all hash table management operations in this header file.
  	4.2.Test operations in the main function of the application as they are implemented.
	4.3. After testing all operations, create a function in the header file named testHeshT, move the contents of the main function into it, and check that the application is running.
	4.4. Develop hash table management operations.
	4.5. Develop a hash function (determine the method yourself), test it, and make sure that the hash (table element index) is formed correctly.
	4.6. Develop operations: insert a key into a table, remove a key from a table, find a key in a table, rehash a table. Test each operation as you implement it.
	4.7.Prepare tests (sequence of key values) that ensure:
   		4.7.1. inserting a key without a collision
		4.7.2. key insertion and collision resolution
		4.7.3. inserting a key followed by rehashing
		4.7.4. removing a key from a table
		4.7.5. searching for a key in a table. For the public address method, prepare a test to find the key that is placed in the table after the deleted key, with one hash value for these keys
	4.8. Perform testing of hash table management operations. When testing the operation of inserting a key into a table, provide a list of indexes that are formed when inserting elements into the table.
5. Binary File Management
	5.1. Binary file management operations: create a binary file from a text file, add an entry to a binary file, remove an entry with a given key from a file, read a file entry by a given entry number.
	5.2. The record structure of a binary file and all file manipulation operations must be placed in an appropriate header file.
	5.3. Test the operations in the main application, and move the contents of the main function to the corresponding function in the header file named testBinF.
6. Managing a file using a hash table
7. Include header files into the file control header file using a hash table: hash table control, binary file control. Implement each of the following operations one by one in this header file, testing them from the main function of the application. After developing all operations, perform their comprehensive testing.
8. Develop and implement operations
	8.1. Read a record from a file and insert an element into the table (the element includes: the key and the number of the record with this key in the file, and additional fields are possible for the open addressing method).
	8.2. Delete a record from the table with a given key value and, accordingly, from the file.
	8.3. Find a record in a file by key value (find a key in a hash table, get the number of the record with this key in the file, directly access the record by its number).
Hash table type (collision resolution method): Open address (offset by 1)
Binary File Record Structure: Airport (the arrival board for passenger flights saves all data in a file): point of departure, flight number, date of arrival, time of arrival, information about arrival delay in hours.

## SIAOD4 (EN)
Subject. Nonlinear data structures. Binary tree.
Target. Obtaining skills in developing and implementing operations on the binary tree data structure.
Exercise:
Tree type: perfectly balanced with n nodes (not AVL).
1. Implement operations common to options 1 to 7
	1.2. Create a perfectly balanced binary tree of n nodes. The structure of a tree node includes: the information part of the node, a pointer to the left and a pointer to the right subtree. The information part of the node is determined by the variant.
	1.3. Display the tree on the screen by rotating it counterclockwise on the screen.
2. Implement variant operations.
3. Develop a program that demonstrates the execution of all operations.
4. Compile a report showing a description of the implementation of all stages of development, testing and the code of the entire program with screenshots of the testing results.
Meaning of the information part: Real number
Option Operations: 
1. Calculate the arithmetic mean of the numbers of the left subtree, as well as the right one, separately.
2. Delete binary tree

## SIAOD5 (EN)
Subject. Balanced search trees (BSTs) and their use for searching data in a file.
Target:
	gain skills in the development and implementation of algorithms for managing a binary search tree and balanced binary search trees (ABL trees);
	gain skills in using file streams for direct access to file data;
	Gain skills in using a balanced search tree to directly access file records.
Exercise.
1. Develop a file management class. Include methods: creating a binary file of fixed-length records from pre-prepared data in a text file; searching and displaying a record in a file using linear search; outputting a record to a known address in a file, adding a record to a file. The file record structure is determined by the individual job option.
2. Develop the “Binary Search Tree” class. The structure of the information part of a tree node includes a key and a link to a record in the file. Develop basic methods: building a tree from an existing file; adding an element to the tree; search by key in the tree; removing an element from the tree; tree output in tree form.
3. Develop a “Balanced Search Tree” class. The structure of the information part of a tree node includes a key and a link to a record in the file. Develop basic methods: building a tree from an existing file; adding an element to the tree; search by key in the tree; removing an element from the tree; tree output in tree form.
4. Develop an application that demonstrates the execution of all methods and searching for records in a file using LDS, LDS and linear search.
5. Analyze the execution time of searching for records located at the beginning, middle and end of a large file in three ways.
6. Determine the average number of turns performed (number of turns per total number of keys inserted) when including keys in the PSD when it is generated from a binary file.
Balanced type search tree (STD): B-Tree
Record structure: Company employees: number(key), full name, fact of higher education (bool)

## SIAOD6 (EN)
Subject. Basic algorithms for working with graphs.
Target. Obtaining practical skills in performing operations on graph data structures.
Exercise.
1. Develop a “Graph” class that provides storage and work with the “graph” data structure, in accordance with the individual task option. Implement a method for entering a graph from the keyboard, adding a node, adding an edge, outputting a graph, and methods that perform tasks defined by the individual task option.
2. Develop a program that demonstrates the operation of all methods of the class.
Representation of a graph in memory: Adjacency matrix
Tasks:
1. Print all the chains in the graph using the depth-first search method.
2. Create a program for finding the shortest paths in a graph using the given method of “Constructing a decision tree.”
3. Print the paths obtained by the method

## SIAOD7 (EN)
Subject. Encoding and compression of data using lossless methods.
Target. Obtaining practical skills and knowledge to perform data compression using the methods in question.
Exercise.
1. Develop a program that demonstrates the execution of the following algorithms:
	1.1. Text compression using the RLE method (run length encoding/run length encoding/group encoding). Calculate the compression ratio in tests.
	1.2. Test on a long series of repeating characters.
	1.3. Test on a long series of non-repeating characters.
2. Text compression using the Lempel-Ziv algorithm (LZ77), LZ78.
	2.1. Calculate the compression ratio in tests.
	2.2. Test the implementation of LZ77 in accordance with the individual version of the task, using the two-character alphabet (0, 1). Describe in the report the process of recovering the resulting compressed text.
	2.3. Test the implementation of LZ78 in accordance with the individual version of the task. Describe in the report the process of recovering the resulting compressed text.
3. Text compression and recovery using Shannon-Fano and Huffman algorithms.
	3.1. Test the Shannon-Fano method in accordance with the individual version of the task.
  	3.2. Present the code generation table in the report, display the prefix tree, and calculate the compression ratio.
	3.3. Test the Huffman method on a line containing your full name.
   	3.4. Construct a table 	of symbol occurrence frequencies, form an alphabet of the source string, and calculate the frequency of occurrences and the probability of occurrence of symbols.
   	3.5. Draw a prefix Huffman tree. Show the encoding of each character in a string.
   	3.6. Calculate compression ratio, average code length and variance.
	3.7. Apply the algorithm to a large text file. Archive the same file using any archiver.
   	3.8. Perform a comparative analysis of compression using these methods.

## SIAOD1 (RU)
Тема. Поразрядные операции и их применение.
Цель. Получение навыков применения поразрядных операций в алгоритмах.
Задание.
1. Разработать программу, которая продемонстрирует выполнение упражнений варианта. Результаты выполнения упражнения и входные значения выводить на монитор в десятичном и двоичном виде.
Требования к упражнениям:
1. Определить переменную целого типа, присвоить ей значение, используя константу в шестнадцатеричной системе счисления. Разработать функцию, которое установит заданные в задании биты исходного значения переменной в значение 1, используя соответствующую маску и поразрядную операцию.
2. Разработать функцию, которая обнуляет заданные в задании биты исходного значения целочисленной переменной, введенной пользователем, используя соответствующую маску и поразрядную операцию.
3. Разработать функцию, которая умножает значение целочисленной переменной, введенной пользователем, на множитель, используя соответствующую поразрядную операцию.
4. Разработать функцию, которая делит значение целочисленной переменной, введенной пользователем, на делитель, используя соответствующую поразрядную операцию.
5. Разработать функцию, реализующую задание, в которой используются только поразрядные операции. В выражении используется маска – переменная. Маска инициализируется единицей в младшем разряде (маска 1) или единицей в старшем разряде (маска 2). Изменяемое число и n вводится с клавиатуры.
Упр.1: 3-ий, 11-ый, 5-ый
Упр.2: Четыре младших
Упр.3: 128
Упр.4: 128
Упр.5: Установить n-ый бит в 1, используя маску 2

## SIAOD2 (RU)
Тема. Внешние структуры данных: текстовый и двоичный файлы.
Цель. Получить навыки применения файловых потоков языка С++ (или файлов языка Си) по управлению текстовым и двоичным файлами.
Задание 1.
1. Разработать программу, управления текстовым файлом.
	1.1. Реализация ввода-вывода на основе файловых потоков С++: ofstream, ifstream.
	1.2. Имя физического файла вводится пользователем и передается в функции обработки через параметр.
	1.3. Разработать функции для выполнения операций над текстовым файлом:
		1.3.1. создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке; файл может быть образцовым или введен пользователем;
		1.3.2. вывод содержимого текстового файла;
		1.3.3. добавление новой строки в конец файла;
		1.3.4. прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение;
		1.3.5. определить количество чисел в файле.
		1.3.6. реализовать дополнительные операции, определенные вариантов
Упр.1: Создать новый файл из значений исходного, переписав в него только простые числа, располагая каждое на отдельной строке текстового файла. 
