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
1. Create a perfectly balanced binary tree of n nodes. The structure of a tree node includes: the information part of the node, a pointer to the left and a pointer to the right subtree. The information part of the node is determined by the variant.
2. Display the tree on the screen by rotating it counterclockwise on the screen.
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
	1.1. Text compression using the RLE method (run length encoding/run length encoding/group encoding).
   	1.2. Calculate the compression ratio in tests.
	1.3. Test on a long series of repeating characters.
	1.4. Test on a long series of non-repeating characters.
3. Text compression using the Lempel-Ziv algorithm (LZ77), LZ78.
	2.1. Calculate the compression ratio in tests.
	2.2. Test the implementation of LZ77 in accordance with the individual version of the task, using the two-character alphabet (0, 1). Describe in the report the process of recovering the resulting compressed text.
	2.3. Test the implementation of LZ78 in accordance with the individual version of the task. Describe in the report the process of recovering the resulting compressed text.
4. Text compression and recovery using Shannon-Fano and Huffman algorithms.
	3.1. Test the Shannon-Fano method in accordance with the individual version of the task.
  	3.2. Present the code generation table in the report, display the prefix tree, and calculate the compression ratio.
	3.3. Test the Huffman method on a line containing your full name.
   	3.4. Construct a table 	of symbol occurrence frequencies, form an alphabet of the source string, and calculate the frequency of occurrences and the probability of occurrence of symbols.
   	3.5. Draw a prefix Huffman tree. Show the encoding of each character in a string.
   	3.6. Calculate compression ratio, average code length and variance.
	3.7. Apply the algorithm to a large text file. Archive the same file using any archiver.
   	3.8. Perform a comparative analysis of compression using these methods.

## SIAOD8 (EN)
Subject. Algorithmic strategies or methods for developing algorithms. Overkill and methods for reducing it.
Target. Gain skills in using methods to reduce the number of searches in problems that can only be solved by searching through all possible solution options.
Exercise.
1. Develop an algorithm for solving the problem using the method specified in the option and implement the program.
2. Estimate the number of searches when solving a problem using a “head-on” strategy - brute force.
3. Provide an analysis of reducing the number of searches when applying the method.

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

Задание 2.
2. Разработать программу управления двоичными файлами с записями фиксированной длины. Общие требования: файл состоит из записей определенной структуры, согласно варианту. Записи имеют ключ, уникальный в пределах файла.
	2.1. Разработать структуру записи двоичного файла согласно варианту задания.
	2.2. Подготовить тестовые данные в текстовом файле с кодировкой ASCII, в соответствии со структурой записи варианта. При открытии файла выполнить контроль его существования и открытия.
	2.3. Имя файла вводит пользователь.
	2.4. При открытии файла обеспечить контроль существования и открытия файла.
	2.5. При применении механизма прямого доступа к записи файла выполнить контроль присутствия записи с заданным номером в файле.
	2.6. Разработать функции для выполнения операций:
		2.6.1. преобразование тестовых данных из текстового файла в двоичный файл;
		2.6.2. преобразование данных из двоичного файла в текстовый;
		2.6.3. вывод всех записей двоичного файла;
		2.6.4. доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле;
		2.6.5. удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись.
		2.6.6. манипулирование записями в двоичном файле согласно дополнительным операциям, определенным в варианте;
Структура записи: Аэропорт (табло прибытия пассажирских авиарейсов сохраняет все данные в файле): пункт вылета, номер рейса(ключ), дата прилета, время прилета, информация о задержке прилета в часах. 
Доп. операция:
1. Сформировать в новом двоичном файле информацию по рейсам, задержанным в указанную дату.
2. Изменить время прилета для заданного рейса на новое значение.

## SIAOD3 (RU)
Тема. Применение хеш-таблицы для поиска данных в двоичном файле с записями фиксированной длины.
Цель. Получить навыки по разработке хеш-таблиц и их применении при поиске данных в других структурах данных (файлах).

Задание 1.
1. Разработать приложение, которое использует хеш-таблицу для организации прямого доступа к записям двоичного файла, реализованного в практической работе 2.
2. Создать приложение и включить в него три заголовочных файла: управление хеш-таблицей, управление двоичным файлом (практическая работа 2), управление двоичным файлом посредством хеш-таблицы.
3. Для обеспечения прямого доступа к записи в файле элемент хеш-таблицы должен включать обязательные поля: ключ записи в файле, номер записи с этим ключом в файле. Элемент может содержать другие поля, требующиеся методу (указанному в вашем варианте), разрешающему коллизию.
4. Управление хеш-таблицей
	4.1. Определить структуру элемента хеш-таблицы и структуру хеш-таблицы в соответствии с методом разрешения коллизии, указанном в варианте. Определения разместить в соответствующем заголовочном файле. Все операции управления хеш-таблицей размещать в этом заголовочном файле. 
	4.2. Тестирование операций выполнять в функции main приложения по мере их реализации. 
	4.3. После тестирования всех операций, создать в заголовочном файле функцию с именем testHeshT переместить в нее содержание функции main, проверить, что приложение выполняется. 
	4.4. Разработать операции по управлению хеш-таблицей.
	4.5. Разработать хеш-функцию (метод определить самостоятельно), выполнить ее тестирование, убедиться, что хеш (индекс элемента таблицы) формируется верно.
	4.6. Разработать операции: вставить ключ в таблицу, удалить ключ из таблицы, найти ключ в таблице, рехешировать таблицу. Каждую операцию тестируйте по мере ее реализации.
	4.7. Подготовить тесты (последовательность значений ключей), обеспечивающие:
		4.7.1. вставку ключа без коллизии
		4.7.2. вставку ключа и разрешение коллизии
		4.7.3. вставку ключа с последующим рехешированием
		4.7.4. удаление ключа из таблицы
		4.7.5. поиск ключа в таблице. Для метода с открытым адресом подготовить тест для поиска ключа, который размещен в таблице после удаленного ключа, с одним значением хеша для этих ключей
	4.8. Выполнить тестирование операций управления хеш-таблицей. При тестировании операции вставки ключа в таблицу предусмотрите вывод списка индексов, которые формируются при вставке элементов в таблицу.
5. Управление двоичным файлом
	5.1. Операции управления двоичным файлом: создание двоичного файла из текстового, добавить запись в двоичный файл, удалить запись с заданным ключом из файла, прочитать запись файла по заданному номеру записи. 
	5.2. Структура записи двоичного файла и все операции по управлению файлом должны быть размещены в соответствующем заголовочном файле. 
	5.3. Выполнить тестирование операций в main приложения, и содержание функции main переместить в соответствующую функцию заголовочного файла с именем testBinF.
6. Управление файлом посредством хеш-таблицы
7. В заголовочный файл управления файлом посредством хеш-таблицы подключить заголовочные файлы: управления хеш-таблицей, управления двоичным файлом. Реализовать поочередно все перечисленные ниже операции в этом заголовочном файле, выполняя их тестирование из функции main приложения. После разработки всех операций выполнить их комплексное тестирование.
8. Разработать и реализовать операции
	8.1. Прочитать запись из файла и вставить элемент в таблицу (элемент включает: ключ и номер записи с этим ключом в файле, и для метода с открытой адресацией возможны дополнительные поля).
	8.2. Удалить запись из таблицы при заданном значении ключа и соответственно из файла.
	8.3. Найти запись в файле по значению ключа (найти ключ в хеш-таблице, получить номер записи с этим ключом в файле, выполнить прямой доступ к записи по ее номеру).
Тип хеш-таблицы (метод разрешения коллизии): Открытый адрес (смещение на 1)
Структура записи двоичного файла:
Аэропорт (табло прибытия пассажирских авиарейсов сохраняет все данные в файле): пункт вылета, номер рейса(ключ), дата прилета, время прилета, информация о задержке прилета в часах. 

## SIAOD4 (RU)
Тема. Нелинейные структуры данных. Бинарное дерево.
Цель. Получение умений и навыков разработки и реализаций операций над структурой данных бинарное дерево.
Задание.
Вид дерева: идеально сбалансированное из n узлов (не AVL).
1. Создать идеально сбалансированное бинарное дерево из n узлов. Структура узла дерева включает: информационная часть узла, указатель на левое и указатель на правое поддерево. Информационная часть узла определена вариантом.
2. Отобразить дерево на экране, повернув его на экране против часовой стрелки.
Значение информационной части: Вещественное число
Операции варианта:
1. Вычислить среднее арифметическое чисел левого поддерева, а также и правого, по отдельности.
2. Удалить двоичное дерево

## SIAOD5 (RU)
Тема. Сбалансированные деревья поиска (СДП) и их применение для поиска данных в файле.
Цель:
	получить навыки в разработки и реализации алгоритмов управления бинарным деревом поиска и сбалансированными бинарными деревьями поиска (АВЛ – деревьями);
	получить навыки в применении файловых потоков прямого доступа к данным файла;
	получить навыки в применении сбалансированного дерева поиска для прямого доступа к записям файла.
Задание.
1. Разработать класс управления файлом. Включить методы: создание двоичного файла записей фиксированной длины из заранее подготовленных данных в текстовом файле; поиск и вывод записи в файле с помощью линейного поиска; вывод записи по известному адресу в файле, добавление записи в файл. Структура записи файла определена индивидуальным вариантом задания.
2. Разработать класс «Бинарное дерево поиска». Структура информационной части узла дерева включает ключ и ссылку на запись в файле. Разработать основные методы: построение дерева по существующему файлу; добавление элемента в дерево; поиск по ключу в дереве; удаление элемента из дерева; вывод дерева в форме дерева.
3. Разработать класс «Сбалансированное дерево поиска». Структура информационной части узла дерева включает ключ и ссылку на запись в файле. Разработать основные методы: построение дерева по существующему файлу; добавление элемента в дерево; поиск по ключу в дереве; удаление элемента из дерева; вывод дерева в форме дерева.
4. Разработать приложение, демонстрирующее выполнение всех методов и поиск записей в файле с помощью БДП, СДП и линейного поиска.
5. Провести анализ времени выполнения поиска записей, находящихся в начале, середине и конце большого файла тремя способами.
6. Определить среднее число выполненных поворотов (число поворотов на общее число вставленных ключей) при включении ключей в СДП при его формировании из двоичного файла.
Тип балансированного дерева поиска (СДП): В-дерево
Структура записи (ключ – подчеркнутое поле):
Сотрудники предприятия: номер(ключ), ФИО, факт наличия высшего образования (bool)

## SIAOD6 (RU)
Тема. Основные алгоритмы работы с графами.
Цель. Получение практических навыков по выполнению операций над структурой данных граф.
Задание.
1. Разработать класс «Граф», обеспечивающий хранение и работу со структурой данных «граф», в соответствии с вариантом индивидуального задания. Реализовать метод ввода графа с клавиатуры, добавления узла, добавления ребра, вывода графа и методы, выполняющие задачи, определенные вариантом индивидуального задания.
Представление графа в памяти: Матрица смежности
Задачи: 
1. Вывести все цепочки в графе, используя метод поиска в глубину.
2. Составить программу нахождения кратчайших путей в графе заданным методом «Построения дерева решений». Вывести пути, полученные методом

## SIAOD7 (RU)
Тема. Кодирование и сжатие данных методами без потерь.
Цель. Получение практических навыков и знаний по выполнению сжатия данных рассматриваемыми методами.
Задание.
1. Разработать программу, демонстрирующую выполнение следующих алгоритмов: 
	1.1. Сжатие текста, используя метод RLE (run length encoding/кодирование длин серий/групповое кодирование).
	1.2. Рассчитать коэффициент сжатия в тестах.
	1.3. Провести тестирование на длинной серии повторяющихся символов.
	1.4. Провести тестирование на длинной серии неповторяющихся символов.
2. Сжатие текста алгоритмом Лемпеля-Зива (LZ77), LZ78.
	2.1. Рассчитать коэффициент сжатия в тестах.
	2.2. Провести тестирование реализации LZ77 в соответствии с индивидуальным вариантом задания, используя двухсимвольный алфавит (0, 1). Описать в отчете процесс восстановления полученного сжатого текста.
	2.3. Провести тестирование реализации LZ78 в соответствии с индивидуальным вариантом задания. Описать в отчете процесс восстановления полученного сжатого текста.
3.Сжатие и восстановление текста алгоритмами Шеннона-Фано и Хаффмана.
	3.1. Провести тестирование метода Шеннона-Фано в соответствии с индивидуальным вариантом задания. Представить в отчете таблицу формирования кода, изобразить префиксное дерево, рассчитать коэффициент сжатия.
	3.2. Провести тестирование метода Хаффмана на строке, содержащей ваше ФИО.
	3.3. Построить таблицу частот встречаемости символов, сформировать алфавит исходной строки и посчитать частоту вхождений и вероятность появления символов.
	3.4. Изобразить префиксное дерево Хаффмана. Показать кодирование каждого символа в строке.
	3.5. Рассчитать коэффициент сжатия, среднюю длину кода и дисперсию.
	3.6. Применить алгоритм к большому текстовому файлу.
	3.7. Архивировать тот же файл любым архиватором.
	3.8. Выполнить сравнительный анализ сжатия этими способами.

## SIAOD8 (RU)
Тема. Алгоритмические стратегии или методы разработки алгоритмов. Перебор и методы его сокращения.
Цель. Получить навыки применения методов, позволяющих сократить число переборов в задачах, которые могут быть решены только методом перебора всех возможных вариантов решения.
Задание.
1. Разработать алгоритм решения задачи с применением метода, указанного в варианте и реализовать программу.
2. Оценить количество переборов при решении задачи стратегией «в лоб» - грубой силы.
3. Привести анализ снижения числа переборов при применении метода.
Задача:
Разработать процедуру оптимального способа расстановки скобок в произведении последовательности матриц, чтобы количество скалярных умножений стало максимальным.
Метод: Жадный алгоритм
