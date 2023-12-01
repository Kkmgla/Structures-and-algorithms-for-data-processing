#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <queue>
#include <algorithm>
using namespace std;

//Структура узла
class TreeNode {
public:
    double value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(double val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    void insert(double value) {
        root = insertRec(root, value);
    }

    TreeNode* insertRec(TreeNode* root, double value) {
        if (root == nullptr) {
            return new TreeNode(value);
        }

        queue<TreeNode*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {//когда nodes !empty, то это означает, что l и r локального предка заняты
            TreeNode* current = nodes.front();
            nodes.pop();
            //Начиная с корня, мы добавляем узлы в очередь и идем в глубину по уровням.
            if (current->left == nullptr) {
                current->left = new TreeNode(value);
                break;
            }
            else {
                nodes.push(current->left);
            }
            /*Мы проверяем левого потомка текущего узла. Если левый потомок null, то мы вставляем новый узел с заданным значением.
            Иначе, если левый потомок уже существует, мы добавляем его в очередь для дальнейшего обхода.
            Аналогично для правого потомка.*/
            if (current->right == nullptr) {
                current->right = new TreeNode(value);
                break;
            }
            else {
                nodes.push(current->right);
            }
        }

        return root;
    }

    void printTree(TreeNode* root, int space) {
        if (root == nullptr) return;
        //когда return возвращает nullptr, это приводит к завершению текущего вызова функции и возврату к предыдущему уровню рекурсии. 

        space += 5;

        printTree(root->right, space);
        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " ";
        }
        cout << root->value;
        printTree(root->left, space);
    }

    void print() {
        if (root == nullptr)
        {
            cout << "Дерева не существует" << endl;
            return;
        }
        else
        {
            printTree(root, 0);
        }
    }

    double averageLeftSubtree(TreeNode* root) {
        if (root == nullptr) {
            return 0.0;
        }

        double sum = root->value;
        int count = 1;

        if (root->left != nullptr) {
            sum += averageLeftSubtree(root->left);
            count++;
        }

        if (root->right != nullptr) {
            sum += averageLeftSubtree(root->right);
            count++;
        }

        return static_cast<double>(sum) / count;
    }

    double averageRightSubtree(TreeNode* root) {
        if (root == nullptr) {
            return 0.0;
        }

        double sum = root->value;
        int count = 1;

        if (root->left != nullptr) {
            sum += averageRightSubtree(root->left);
            count++;
        }

        if (root->right != nullptr) {
            sum += averageRightSubtree(root->right);
            count++;
        }

        return static_cast<double>(sum) / count;
    }

    void deleteTree(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        // Рекурсивно удаляем левое и правое поддерево
        deleteTree(root->left);
        deleteTree(root->right);

        // Удаляем текущий узел
        delete root;
    }

    double averageLeftSubtree() {
        if (root == nullptr)
        {
            cout << "Дерева не существует\n";
            return 0;
        }
        else
        {
            return averageLeftSubtree(root->left);
        }
    }

    double averageRightSubtree() {
        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            return averageRightSubtree(root->right);
        }
    }

    void deleteTree() {
        deleteTree(root);
        root = nullptr; // Обнуляем корень
    }

};

int main() {
    BinaryTree tree;
    setlocale(LC_ALL, "Russian");
    int n;
    double val;
    cout << "Введите количество элементов в дереве: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Введите значение элемента: ";
        cin >> val;
        tree.insert(val);
    }
    cout << "Ваше бинарное дерево:\n";
    tree.print();
    cout << endl;

    while (1) {
        cout << "Меню:\n" <<
            "1. Вычислить среднее арифметическое чисел левого поддерева, а также и правого, по отдельности.\n" <<
            "2. Удалить двоичное дерево.\n";
        int var;
        cin >> var;
        switch (var) {

        case 1:
            cout << "Среднее арифметическое левого поддерева: " << tree.averageLeftSubtree() << endl;
            cout << "Среднее арифметическое правого поддерева: " << tree.averageRightSubtree() << endl;
            break;
        case 2:
            tree.deleteTree();
            cout << "Дерево удалено." << endl;
            break;
        default:
            cout << "Такого варианта нет" << endl;
            break;
        }
    }
    return 0;
}