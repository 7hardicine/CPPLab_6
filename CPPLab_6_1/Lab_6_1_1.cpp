#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct GraphicsCard
{
    string interfaceType;
    string gpuManufacturer;  // Ключ для поиска
    string gpuModel;
    int gpuFrequency;        // в MHz
    int vramSize;            // в GB
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
    cout << "\nИнформация о графической карте:" << endl;
    cout << "Производитель: " << card.gpuManufacturer << endl;
    cout << "Модель: " << card.gpuModel << endl;
    cout << "Интерфейс: " << card.interfaceType << endl;
    cout << "Частота графического процессов: " << card.gpuFrequency << " MHz" << endl;
    cout << "Видеопамять: " << card.vramSize << " GB" << endl;
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
    // Альтернатива numeric_limits<streamsize>::max()
    while (cin.get() != '\n') {}
}

GraphicsCard inputGraphicsCard()
{
    GraphicsCard card;

    clearInputBuffer();
    cout << "Введите тип интерфейса (например, PCIe 3.0 x16): ";
    getline(cin, card.interfaceType);

    cout << "Введите производителя GPU (например, NVIDIA или AMD): ";
    getline(cin, card.gpuManufacturer);

    cout << "Введите модель GPU: ";
    getline(cin, card.gpuModel);

    cout << "Введите частоту GPU (в MHz): ";
    cin >> card.gpuFrequency;

    cout << "Введите объем видеопамяти (в GB): ";
    cin >> card.vramSize;

    return card;
}

void displayMenu()
{
    cout << "\nМеню:" << endl;
    cout << "1. Добавить графическую карту" << endl;
    cout << "2. Найти графическую карту по производителю" << endl;
    cout << "3. Удалить графическую карту" << endl;
    cout << "4. Показать все графические карты" << endl;
    cout << "5. Выход" << endl;
    cout << "Выберите действие: ";
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
            cout << "\nГрафическая карта добавлена!" << endl;
            break;
        }
        case 2: {
            clearInputBuffer();
            cout << "\nВведите производителя для поиска: ";
            getline(cin, manufacturer);

            TreeNode* found = searchNode(root, manufacturer);
            if (found != nullptr)
            {
                cout << "\nНайдена графическая карта:" << endl;
                printCard(found->data);
            }
            else
            {
                cout << "\nГрафическая карта от " << manufacturer << " не найдена." << endl;
            }
            break;
        }
        case 3: {
            clearInputBuffer();
            cout << "\nВведите производителя для удаления: ";
            getline(cin, manufacturer);

            if (searchNode(root, manufacturer) != nullptr)
            {
                root = deleteNode(root, manufacturer);
                cout << "\nГрафическая карта от " << manufacturer << " удалена." << endl;
            }
            else
            {
                cout << "\nГрафическая карта от " << manufacturer << " не найдена." << endl;
            }
            break;
        }
        case 4: {
            cout << "\nСписок всех графических карт:" << endl;
            if (root == nullptr)
            {
                cout << "База данных пуста." << endl;
            }
            else
            {
                inorderTraversal(root);
            }
            break;
        }
        case 5: {
            cout << "\nЗавершение программы..." << endl;
            break;
        }
        default: {
            cout << "\nНеверный выбор. Попробуйте снова." << endl;
            clearInputBuffer();
            break;
        }
        }
    } while (choice != 5);

    deleteTree(root);

    system("pause");
    return 0;
}