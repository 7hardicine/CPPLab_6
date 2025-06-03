#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct GraphicsCard
{
    string interfaceType;
    string gpuManufacturer;  // ���� ��� ������
    string gpuModel;
    int gpuFrequency;        // � MHz
    int vramSize;            // � GB
};
struct TreeNode
{
    GraphicsCard data;
    TreeNode* left;
    TreeNode* right;
};
TreeNode* createNode(const GraphicsCard& card)
{
    TreeNode* newNode = new TreeNode;
    newNode->data = card;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
TreeNode* insertNode(TreeNode* root, const GraphicsCard& card)
{
    if (root == nullptr)
    {
        return createNode(card);
    }
    if (card.gpuManufacturer < root->data.gpuManufacturer)
    {
        root->left = insertNode(root->left, card);
    }
    else if (card.gpuManufacturer > root->data.gpuManufacturer)
    {
        root->right = insertNode(root->right, card);
    }
    return root;
}
TreeNode* searchNode(TreeNode* root, const string& manufacturer)
{
    if (root == nullptr || root->data.gpuManufacturer == manufacturer)
    {
        return root;
    }
    if (manufacturer < root->data.gpuManufacturer)
    {
        return searchNode(root->left, manufacturer);
    }
    else
    {
        return searchNode(root->right, manufacturer);
    }
}

TreeNode* findMinNode(TreeNode* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, const string& manufacturer) {
    if (root == nullptr)
    {
        return root;
    }
    if (manufacturer < root->data.gpuManufacturer)
    {
        root->left = deleteNode(root->left, manufacturer);
    }
    else if (manufacturer > root->data.gpuManufacturer)
    {
        root->right = deleteNode(root->right, manufacturer);
    }
    else
    {
        if (root->left == nullptr)
        {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.gpuManufacturer);
    }
    return root;
}

void printCard(const GraphicsCard& card)
{
    cout << "\n���������� � ����������� �����:" << endl;
    cout << "�������������: " << card.gpuManufacturer << endl;
    cout << "������: " << card.gpuModel << endl;
    cout << "���������: " << card.interfaceType << endl;
    cout << "������� ������������ ���������: " << card.gpuFrequency << " MHz" << endl;
    cout << "�����������: " << card.vramSize << " GB" << endl;
    cout << "------------------------" << endl;
}

void inorderTraversal(TreeNode* root)
{
    if (root != nullptr)
    {
        inorderTraversal(root->left);
        printCard(root->data);
        inorderTraversal(root->right);
    }
}

void deleteTree(TreeNode* root)
{
    if (root != nullptr)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void clearInputBuffer()
{
    // ������������ numeric_limits<streamsize>::max()
    while (cin.get() != '\n') {}
}

GraphicsCard inputGraphicsCard()
{
    GraphicsCard card;

    clearInputBuffer();
    cout << "������� ��� ���������� (��������, PCIe 3.0 x16): ";
    getline(cin, card.interfaceType);

    cout << "������� ������������� GPU (��������, NVIDIA ��� AMD): ";
    getline(cin, card.gpuManufacturer);

    cout << "������� ������ GPU: ";
    getline(cin, card.gpuModel);

    cout << "������� ������� GPU (� MHz): ";
    cin >> card.gpuFrequency;

    cout << "������� ����� ����������� (� GB): ";
    cin >> card.vramSize;

    return card;
}

void displayMenu()
{
    cout << "\n����:" << endl;
    cout << "1. �������� ����������� �����" << endl;
    cout << "2. ����� ����������� ����� �� �������������" << endl;
    cout << "3. ������� ����������� �����" << endl;
    cout << "4. �������� ��� ����������� �����" << endl;
    cout << "5. �����" << endl;
    cout << "�������� ��������: ";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TreeNode* root = nullptr;
    int choice;
    string manufacturer;

    do {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: {
            GraphicsCard newCard = inputGraphicsCard();
            root = insertNode(root, newCard);
            cout << "\n����������� ����� ���������!" << endl;
            break;
        }
        case 2: {
            clearInputBuffer();
            cout << "\n������� ������������� ��� ������: ";
            getline(cin, manufacturer);

            TreeNode* found = searchNode(root, manufacturer);
            if (found != nullptr)
            {
                cout << "\n������� ����������� �����:" << endl;
                printCard(found->data);
            }
            else
            {
                cout << "\n����������� ����� �� " << manufacturer << " �� �������." << endl;
            }
            break;
        }
        case 3: {
            clearInputBuffer();
            cout << "\n������� ������������� ��� ��������: ";
            getline(cin, manufacturer);

            if (searchNode(root, manufacturer) != nullptr)
            {
                root = deleteNode(root, manufacturer);
                cout << "\n����������� ����� �� " << manufacturer << " �������." << endl;
            }
            else
            {
                cout << "\n����������� ����� �� " << manufacturer << " �� �������." << endl;
            }
            break;
        }
        case 4: {
            cout << "\n������ ���� ����������� ����:" << endl;
            if (root == nullptr)
            {
                cout << "���� ������ �����." << endl;
            }
            else
            {
                inorderTraversal(root);
            }
            break;
        }
        case 5: {
            cout << "\n���������� ���������..." << endl;
            break;
        }
        default: {
            cout << "\n�������� �����. ���������� �����." << endl;
            clearInputBuffer();
            break;
        }
        }
    } while (choice != 5);

    deleteTree(root);

    system("pause");
    return 0;
}