#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct GraphicsCard 
{
    string interfaceType;
    string gpuManufacturer;  // Ключ для поиска
    string gpuModel;
    int gpuFrequency;       // в MHz
    int vramSize;           // в GB
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
    cout << "Manufacturer: " << card.gpuManufacturer << endl;
    cout << "Model: " << card.gpuModel << endl;
    cout << "Interface: " << card.interfaceType << endl;
    cout << "GPU Frequency: " << card.gpuFrequency << " MHz" << endl;
    cout << "VRAM: " << card.vramSize << " GB" << endl;
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

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TreeNode* root = nullptr;
    root = insertNode(root, { "PCIe 3.0 x16", "NVIDIA", "GeForce RTX 3080", 1440, 10 });
    root = insertNode(root, { "PCIe 4.0 x16", "AMD", "Radeon RX 6800 XT", 2015, 16 });
    root = insertNode(root, { "PCIe 4.0 x16", "NVIDIA", "GeForce RTX 3090", 1395, 24 });
    root = insertNode(root, { "PCIe 4.0 x16", "AMD", "Radeon RX 6900 XT", 2015, 16 });
    cout << "Graphics Cards (sorted by GPU manufacturer):" << endl;
    inorderTraversal(root);
    string searchManufacturer = "NVIDIA";
    TreeNode* found = searchNode(root, searchManufacturer);
    if (found != nullptr) 
    {
        cout << "\nFound graphics card by " << searchManufacturer << ":" << endl;
        printCard(found->data);
    }
    else 
    {
        cout << "\nGraphics card by " << searchManufacturer << " not found." << endl;
    }
    string deleteManufacturer = "AMD";
    cout << "\nRemoving graphics card by " << deleteManufacturer << "..." << endl;
    root = deleteNode(root, deleteManufacturer);
    cout << "\nGraphics Cards after removal:" << endl;
    inorderTraversal(root);
    deleteTree(root);

    return 0;
}