#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <queue>
#include <algorithm>
using namespace std;

//��������� ����
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

        while (!nodes.empty()) {//����� nodes !empty, �� ��� ��������, ��� l � r ���������� ������ ������
            TreeNode* current = nodes.front();
            nodes.pop();
            //������� � �����, �� ��������� ���� � ������� � ���� � ������� �� �������.
            if (current->left == nullptr) {
                current->left = new TreeNode(value);
                break;
            }
            else {
                nodes.push(current->left);
            }
            /*�� ��������� ������ ������� �������� ����. ���� ����� ������� null, �� �� ��������� ����� ���� � �������� ���������.
            �����, ���� ����� ������� ��� ����������, �� ��������� ��� � ������� ��� ����������� ������.
            ���������� ��� ������� �������.*/
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
        //����� return ���������� nullptr, ��� �������� � ���������� �������� ������ ������� � �������� � ����������� ������ ��������. 

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
            cout << "������ �� ����������" << endl;
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

        // ���������� ������� ����� � ������ ���������
        deleteTree(root->left);
        deleteTree(root->right);

        // ������� ������� ����
        delete root;
    }

    double averageLeftSubtree() {
        if (root == nullptr)
        {
            cout << "������ �� ����������\n";
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
        root = nullptr; // �������� ������
    }

};

int main() {
    BinaryTree tree;
    setlocale(LC_ALL, "Russian");
    int n;
    double val;
    cout << "������� ���������� ��������� � ������: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "������� �������� ��������: ";
        cin >> val;
        tree.insert(val);
    }
    cout << "���� �������� ������:\n";
    tree.print();
    cout << endl;

    while (1) {
        cout << "����:\n" <<
            "1. ��������� ������� �������������� ����� ������ ���������, � ����� � �������, �� �����������.\n" <<
            "2. ������� �������� ������.\n";
        int var;
        cin >> var;
        switch (var) {

        case 1:
            cout << "������� �������������� ������ ���������: " << tree.averageLeftSubtree() << endl;
            cout << "������� �������������� ������� ���������: " << tree.averageRightSubtree() << endl;
            break;
        case 2:
            tree.deleteTree();
            cout << "������ �������." << endl;
            break;
        default:
            cout << "������ �������� ���" << endl;
            break;
        }
    }
    return 0;
}