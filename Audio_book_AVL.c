#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 50   // defining the Max length of Each field
#define MAXINPUT 20 // Max Audio books
// structure definition for Audiobook
typedef struct AVL_Audio_book
{
    int Audio_book_id;
    char Title[MAXLEN];
    char Author[MAXLEN];
    char Narrator[MAXLEN];
    float duration;
    char Genere[MAXLEN];
    float sum_rating;
    int count_rating;

    struct AVL_Audio_book *left;
    struct AVL_Audio_book *right;
    int height;

} Audio_book_Tree;
// structure definition for Audiobook in the user
typedef struct Audio_book_user_Tag
{
    int Audio_book_id;
    char Title[MAXLEN];
    char Author[MAXLEN];
    char Narrator[MAXLEN];
    float duration;
    char Genere[MAXLEN];
    float sum_rating;
    int count_rating;
    float timestamp;

    struct Audio_book_user_Tag *left;
    struct Audio_book_user_Tag *right;
    int height;

} Audio_book_user_Tree;
// structure definition for user
typedef struct User_Tree_Tag
{
    int User_id;
    char Name[MAXLEN];
    char Email[MAXLEN];
    char Narrator_preference[MAXLEN];
    char Author_preference[MAXLEN];
    char Genere_preference[MAXLEN];
    Audio_book_user_Tree *audiobooks;

    struct User_Tree_Tag *left;
    struct User_Tree_Tag *right;
    int height;

} User_Tree;
// function that converts string to integer
int maxi(int l, int k)
{
    return l > k ? l : k;
}
// Function to convert the Integer Present in the form of string to Integer
int parse(char s[])
{
    int num = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        num = num * 10 + (s[i] - 48);
    }
    return num;
}
// Fuction that search for the Audiobook with the given ID in the Audiolist
Audio_book_Tree *search(Audio_book_Tree *root, int id)
{
    Audio_book_Tree *temp = root;
    Audio_book_Tree *ans = NULL;
    int found = 0;
    while (temp != NULL && !found)
    {
        // Audiobook with the given id found
        if (temp->Audio_book_id == id)
        {
            ans = temp;
            found = 1;
        } // Search in the right subtree
        else if (temp->Audio_book_id < id)
        {
            temp = temp->right;
        } // search in the left subtree
        else
        {
            temp = temp->left;
        }
    }

    return ans;
}
Audio_book_user_Tree *search_abu(Audio_book_user_Tree *root, int id)
{
    Audio_book_user_Tree *temp = root;
    Audio_book_user_Tree *ans = NULL;
    int found = 0;
    while (temp != NULL && !found)
    {
        // Audiobook with given id found
        if (temp->Audio_book_id == id)
        {
            ans = temp;
            found = 1;
        } // search in the right sub tree
        else if (temp->Audio_book_id < id)
        {
            temp = temp->right;
        } // search in the left sub tree
        else
        {
            temp = temp->left;
        }
    }

    return ans;
}
// Function to rotate Audiobook tree towards Left side
Audio_book_Tree *Leftrotation(Audio_book_Tree *root)
{
    Audio_book_Tree *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right); // Modifying  the height of root
    root->height = h + 1;
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1; // Modifying  the height of new root

    return temp;
}
// Function to rotate Audiobok tree towards Right side

Audio_book_Tree *Rightrotation(Audio_book_Tree *root)
{

    Audio_book_Tree *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right);
    root->height = h + 1; // Modifying  the height of root
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1; // Modifying  the height of  new root

    return temp;
}
// Function to insert New Audiobook in the Audiolist
Audio_book_Tree *insert_into_avl_abt(Audio_book_Tree *root, Audio_book_Tree *newnode)
{

    if (root == NULL)
    {
        root = newnode; // Inserting the New Audiobbok in Audiolist
    }
    else
    { // Insert in the Left Subtree
        if (root->Audio_book_id > newnode->Audio_book_id)
        {

            root->left = insert_into_avl_abt(root->left, newnode);
        } // Insert in the Right Subtree
        else if (root->Audio_book_id < newnode->Audio_book_id)
        {
            root->right = insert_into_avl_abt(root->right, newnode);
        } // Modifying the height  this Node after Insertion
        int left = root->left ? root->left->height : 0;
        int right = root->right ? root->right->height : 0;
        root->height = maxi(left, right) + 1;
        if (abs(left - right) <= 1)
        {
            // It is Already Satisfying AVL Rules No need of Rotations
            return root;
        }
        else
        {
            if (left > right)
            {
                // Left subtree height is greater than Right subtree
                int l = root->left->left ? root->left->left->height : -1;
                int r = root->left->right ? root->left->right->height : -1;
                // Children of Left subtree is Lopsided towards Right
                if (r > l)
                {
                    // Rotating it to Left to make it Left Lopsided
                    root->left = Leftrotation(root->left);

                } // Rotating the Left Lopsided Node for height Balancing
                root = Rightrotation(root);
            }
            // right rotation
            else if (right > left)
            {
                // Right subtree height is greater than Left subtree
                int l = root->right->left ? root->right->left->height : -1;
                int r = root->right->right ? root->right->right->height : -1;
                // Children of Left subtree is Lopsided towards Left
                if (l > r)
                {
                    // Rotating it to  Right to make it Left Lopsided
                    root->right = Rightrotation(root->right);
                }
                // Rotating the  Right Lopsided Node for height Balancing
                root = Leftrotation(root);
            }
        }
    }
    return root;
}
Audio_book_Tree *insert(Audio_book_Tree *root, Audio_book_Tree *newnode)
{
    Audio_book_Tree *temp = search(root, newnode->Audio_book_id);
    if (temp != NULL && root != NULL)
    { // Audiobook Exists
        printf("Duplicate Node \n");
        return root;
    }
    // Audiobook is  not Available  Insert in the Audiolist
    root = insert_into_avl_abt(root, newnode);

    return root;
}
// Function to create Audiobook tree using File Handling
Audio_book_Tree *create_audiobook_tree()
{
    Audio_book_Tree *head = NULL;

    FILE *fp = fopen("Audio_book_input.txt", "r");
    char word[MAXLEN];
    while (fscanf(fp, " %s", word) == 1)
    {
        Audio_book_Tree *temp = (Audio_book_Tree *)malloc(sizeof(Audio_book_Tree));
        temp->Audio_book_id = parse(word);
        fscanf(fp, "%s", word);
        strcpy(temp->Title, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Author, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Narrator, word);
        float q;
        fscanf(fp, "%f", &q);
        temp->duration = q;
        fscanf(fp, "%s", word);
        strcpy(temp->Genere, word);
        fscanf(fp, "%f", &q);
        temp->sum_rating = q;
        int num;
        fscanf(fp, "%d", &num);
        temp->count_rating = num;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 0;

        head = insert_into_avl_abt(head, temp);
    }
    fclose(fp);
    return head;
}
// Function to rotate  user Audiobook  tree towards Left side
Audio_book_user_Tree *Leftrotation_abu(Audio_book_user_Tree *root)
{
    Audio_book_user_Tree *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right);
    root->height = h + 1;
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1;

    return temp;
}
// Function to rotate Audiobook tree towards Right side
Audio_book_user_Tree *Rightrotation_abu(Audio_book_user_Tree *root)
{

    Audio_book_user_Tree *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right);
    root->height = h + 1;
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1;

    return temp;
}
// Function to insert New Audiobook in the  user Audiolist
Audio_book_user_Tree *insert_into_avl_abu(Audio_book_user_Tree *root, Audio_book_user_Tree *newnode)
{
    if (root == NULL)
    {
        root = newnode;
    }
    else
    {
        if (root->Audio_book_id > newnode->Audio_book_id)
        {
            root->left = insert_into_avl_abu(root->left, newnode);
        }
        else if (root->Audio_book_id < newnode->Audio_book_id)
        {
            root->right = insert_into_avl_abu(root->right, newnode);
        }
        int left = root->left ? root->left->height : -1;
        int right = root->right ? root->right->height : -1;
        root->height = maxi(left, right) + 1;
        if (abs(left - right) <= 1)
        {
            // it is avl no need of extra cases
            return root;
        }
        else
        {
            if (left > right)
            {
                int l = root->left->left ? root->left->left->height : -1;
                int r = root->left->right ? root->left->right->height : -1;

                if (r > l)
                {
                    root->left = Leftrotation_abu(root->left);
                    // lr
                }
                root = Rightrotation_abu(root);
                // ll
            }
            // right rotation
            else if (right > left)
            {
                int l = root->right->left ? root->right->left->height : -1;
                int r = root->right->right ? root->right->right->height : -1;
                if (l > r)
                {
                    root->right = Rightrotation_abu(root->right);
                    // rl
                }
                root = Leftrotation_abu(root);
                // rr
            }
        }
    }
    return root;
}
// Function to create  user Audiobook tree
Audio_book_user_Tree *construct_user_audiolist(Audio_book_Tree *a, int id, Audio_book_user_Tree *abu)
{
    Audio_book_user_Tree *new_abu = (Audio_book_user_Tree *)malloc(sizeof(Audio_book_user_Tree));
    Audio_book_Tree *temp = search(a, id);
    new_abu->Audio_book_id = temp->Audio_book_id;
    strcpy(new_abu->Author, temp->Author);
    strcpy(new_abu->Narrator, temp->Narrator);
    strcpy(new_abu->Genere, temp->Genere);
    strcpy(new_abu->Title, temp->Title);

    new_abu->sum_rating = temp->sum_rating;
    new_abu->count_rating = temp->count_rating;
    new_abu->duration = temp->duration;
    new_abu->timestamp = 0.0;

    return insert_into_avl_abu(abu, new_abu);
}
// Function to rotate User tree towards Left side
User_Tree *Leftrotation_user(User_Tree *root)
{
    User_Tree *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right);
    root->height = h + 1;
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1;

    return temp;
}
// Function to rotate User tree towards Right side
User_Tree *Rightrotation_user(User_Tree *root)
{

    User_Tree *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    int h = maxi(left, right);
    root->height = h + 1;
    int tleft = temp->left ? temp->left->height : -1;
    int tright = temp->right ? temp->right->height : -1;
    int th = maxi(tleft, tright);
    temp->height = th + 1;

    return temp;
}
// Function to insert New User Node in the user -list
User_Tree *insert_into_avl_user(User_Tree *root, User_Tree *newnode)
{
    if (root == NULL)
    {
        root = newnode;
    }
    else
    {
        if (root->User_id > newnode->User_id)
        {
            root->left = insert_into_avl_user(root->left, newnode);
        }
        else if (root->User_id < newnode->User_id)
        {
            root->right = insert_into_avl_user(root->right, newnode);
        }
        int left = root->left ? root->left->height : -1;
        int right = root->right ? root->right->height : -1;
        root->height = maxi(left, right) + 1;
        if (abs(left - right) <= 1)
        {
            // it is avl no need of extra cases
            return root;
        }
        else
        {
            if (left > right)
            {
                int l = root->left->left ? root->left->left->height : -1;
                int r = root->left->right ? root->left->right->height : -1;

                if (r > l)
                {
                    root->left = Leftrotation_user(root->left);
                    // lr
                }
                root = Rightrotation_user(root);
                // ll
            }
            // right rotation
            else if (right > left)
            {
                int l = root->right->left ? root->right->left->height : -1;
                int r = root->right->right ? root->right->right->height : -1;
                if (l > r)
                {
                    root->right = Rightrotation_user(root->right);
                    // rl
                }
                root = Leftrotation_user(root);
                // rr
            }
        }
    }
    return root;
}
// Function to create user tree using File Handling
User_Tree *create_user_tree(Audio_book_Tree *a)
{
    User_Tree *head = NULL;
    FILE *fp = fopen("users_input.txt", "r");
    char word[MAXLEN];
    int k;
    while (fscanf(fp, " %d", &k) == 1)
    {
        User_Tree *temp = (User_Tree *)malloc(sizeof(User_Tree));
        temp->User_id = k;
        fscanf(fp, "%s", word);
        strcpy(temp->Name, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Email, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Narrator_preference, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Author_preference, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Genere_preference, word);

        Audio_book_user_Tree *abu = NULL;
        while (fscanf(fp, " %s", word) == 1 && strcmp(word, "end") != 0)
        {
            int k = parse(word);
            abu = construct_user_audiolist(a, k, abu);
        }
        temp->audiobooks = abu;

        temp->left = NULL;
        temp->right = NULL;
        temp->height = 0;
        head = insert_into_avl_user(head, temp);
    }
    fclose(fp);
    return head;
}
// Fuction to traverse  through Audiobooks
void inordertraversal_Audiobook(Audio_book_Tree *root)
{
    if (root != NULL)
    {
        inordertraversal_Audiobook(root->left);
        printf("ID:%d\t Title %s\n", root->Audio_book_id, root->Title);
        inordertraversal_Audiobook(root->right);
    }
    return;
}
// Fuction to traverse  through  user Audiobooks
void inordertraversal_Audiobook_users(Audio_book_user_Tree *root)
{
    if (root != NULL)
    {
        inordertraversal_Audiobook_users(root->left);
        printf("ID:%d\t Title %s\n", root->Audio_book_id, root->Title);
        inordertraversal_Audiobook_users(root->right);
    }
    return;
}
// Fuction to traverse  through users
void inordertraversal_users(User_Tree *root)
{
    if (root != NULL)
    {
        inordertraversal_users(root->left);
        printf("ID:%d\t Name: %s\n", root->User_id, root->Name);
        inordertraversal_users(root->right);
    }
    return;
}
// Function to Adjust the Tree into AVL tree from Initial path to final path
Audio_book_Tree *delete_abt_helper(Audio_book_Tree *root, Audio_book_Tree *smallparent)
{
    if (root->Audio_book_id > smallparent->Audio_book_id)
    {

        root->left = delete_abt_helper(root->left, smallparent);
    }
    else if (root->Audio_book_id < smallparent->Audio_book_id)
    {

        root->right = delete_abt_helper(root->right, smallparent);
    }
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    root->height = maxi(left, right) + 1;
    if (abs(left - right) <= 1)
    {
        // it is avl no need of extra cases

        return root;
    }
    else if (root != NULL)
    {
        if (left > right)
        {
            int l = root->left->left ? root->left->left->height : -1;
            int r = root->left->right ? root->left->right->height : -1;

            if (r > l)
            {
                root->left = Leftrotation(root->left);
                // lr
            }
            root = Rightrotation(root);
            // ll
        }
        // right rotation
        else if (right > left)
        {
            int l = root->right->left ? root->right->left->height : -1;
            int r = root->right->right ? root->right->right->height : -1;
            if (l > r)
            {
                root->right = Rightrotation(root->right);
                // rl
            }
            root = Leftrotation(root);
            // rr
        }
    }
    return root;
}
// Function to delete Audiobook using BST deletion Technique
void delete_Audio_book_bst(Audio_book_Tree **root)
{
    Audio_book_Tree *nptr = (*root);
    if (nptr != NULL)
    {
        if (nptr->right == NULL && nptr->left == NULL)
        {
            (*root) = NULL;
            free(nptr);
        }
        else if (nptr->right == NULL)
        {
            (*root) = nptr->left;

            free(nptr);
        }
        else if (nptr->left == NULL)
        {
            (*root) = nptr->right;

            free(nptr);
        }
        else
        {

            Audio_book_Tree *prev, *ptr;
            // take left go to right of left
            prev = nptr->left;
            ptr = nptr->left;
            while (ptr->right != NULL)
            {
                prev = ptr;
                ptr = ptr->right;
            }
            if (ptr == prev)
            {
                ptr->right = nptr->right;
                free(nptr);

                // i have to balance tree fr ptr only
            }
            else
            {
                int l = prev->left ? prev->left->height : -1;
                int r = ptr->left ? ptr->left->height : -1;

                prev->right = ptr->left;
                prev->height = 1 + maxi(l, r); // changed ptr to prev

                ptr->right = nptr->right;
                ptr->left = nptr->left;

                free(nptr);
                // set function
            }

            (*root) = delete_abt_helper(ptr, prev);
        }
    }

    return;
}
// Function to delete Audiobook in the AVL tree
Audio_book_Tree *delete_abt_rec(Audio_book_Tree *root, int id)
{
    if (root->Audio_book_id == id)
    {
        // Audiobook with given ID found
        delete_Audio_book_bst(&root);
        return root;
    }
    else if (root->Audio_book_id > id)
    {
        // Searching audiobook in left subtree
        root->left = delete_abt_rec(root->left, id);
    }
    else
    {
        // Searching audiobook in right subtree
        root->right = delete_abt_rec(root->right, id);
    }
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    root->height = maxi(left, right) + 1; // updating height
    if (abs(left - right) <= 1)
    {
        // It is avl tree no need of extra rotations
        return root;
    }
    else if (root != NULL)
    {
        if (left > right)
        {
            // left lopsided
            int l = root->left->left ? root->left->left->height : -1;
            int r = root->left->right ? root->left->right->height : -1;

            if (r > l)
            {
                // child is right lopsided
                // adjusting the child to make it left lopsided
                root->left = Leftrotation(root->left);
                // lr
            }
            root = Rightrotation(root);
            // adjusting the left unbalanced tree
        }
        else if (right > left)
        {
            // right rotation
            int l = root->right->left ? root->right->left->height : -1;
            int r = root->right->right ? root->right->right->height : -1;
            if (l > r)
            {
                // child is left lopsided
                // adjusting the child to make it right lopsided
                root->right = Rightrotation(root->right);
                // rl
            }
            root = Leftrotation(root);
            // adjusting the right unbalanced tree
        }
    }
    return root;
}

Audio_book_Tree *delete_abt(Audio_book_Tree *root, int id)
{
    // checking whether audiobook is present or not
    Audio_book_Tree *temp = search(root, id);
    if (temp != NULL)
    {
        // calling delete audiobook recursively
        root = delete_abt_rec(root, id);
    }
    else
    {
        printf("ID doesn't exist\n");
    }

    return root;
}
// Function to store the ID''s of Audiobook's Matching the criteria Through Traversing the tree
void Delete_Audio_book_helper(Audio_book_Tree *root, int n, char word[], int array[], int *size)
{
    // inorder traversal to get IDs
    if (root != NULL)
    {
        Delete_Audio_book_helper(root->left, n, word, array, size);
        if ((n == 1 && strcmp(root->Title, word) == 0) || (n == 2 && strcmp(root->Author, word) == 0))
        {
            // If given criteria matches,storing ID in array
            array[*size] = root->Audio_book_id;
            (*size) = (*size) + 1;
        }
        Delete_Audio_book_helper(root->right, n, word, array, size);
    }
    return;
}
// Function That Allow Users to Choose the criteria for Deletion of Audiobook
void Delete_Audio_book(Audio_book_Tree **mainroot)
{
    Audio_book_Tree *root = (*mainroot);
    char word[MAXLEN];
    int n;
    // providing user multiple options for deletion
    printf("Choose one of the option\n");
    printf("1.Delete by title\n");
    printf("2.Delete by author\n");
    scanf("%d", &n);
    if (n == 1)
    {
        printf("Enter the title\n");
        scanf("%s", word);
    }
    else if (n == 2)
    {
        printf("Enter the author\n");
        scanf("%s", word);
    }
    else
    {
        printf("Invalid option\n");
        return;
    }
    int array[MAXINPUT] = {0}; // Creating an array to store IDs of audiobooks to be deleted
    int size = 0;
    // Calling helper function to store IDs of audiobooks to be deleted
    Delete_Audio_book_helper(root, n, word, array, &size);
    int i = 0;
    while (i < size)
    {
        // calling delete function to delete all audiobooks with IDs in array
        root = delete_abt(root, array[i]);
        i++;
    }

    if (n == 1 && i == 0)
    {
        printf("no audio book found with the title %s ", word);
    }
    else if (n == 2 && i == 0)
    {
        printf("no audio book found with the author  %s ", word);
    }
    else
    {

        printf("deletion done successfully");
    }
    (*mainroot) = root;
    return;
}
// Function to add Audiobook with the given ID to Audiobook list
void add_AudioBook(Audio_book_Tree **abt, int id, char title[], char author[], char narrator[], float duration, char genre[], float rating)
{

    Audio_book_Tree *root = (*abt);
    // seraching for audiobook in audiolist
    Audio_book_Tree *ptr = search(root, id);
    if (ptr == NULL)
    {
        // Audiobook is not available in audiolist
        // Creating new audiobook
        Audio_book_Tree *new_ab = (Audio_book_Tree *)malloc(sizeof(Audio_book_Tree));
        new_ab->Audio_book_id = id;
        strcpy(new_ab->Title, title);
        strcpy(new_ab->Author, author);
        strcpy(new_ab->Narrator, narrator);
        strcpy(new_ab->Genere, genre);
        new_ab->duration = duration;
        new_ab->sum_rating = rating;
        new_ab->left = NULL;
        new_ab->right = NULL;
        new_ab->height = 0;
        // inserting new audiobook in audiolist
        root = insert_into_avl_abt(root, new_ab);
        (*abt) = root;
        printf("Audibook with ID %d is added successfully\n", id);
    }
    else
    {
        printf("Audibook with ID %d is already present\n", id);
    }
}
// Function to Edit Audiobook with the given ID
void Edit_audiobook(Audio_book_Tree *abt)
{
    // searching for audiobook with given ID in the audiolist
    int id;
    printf("Enter ID of audibook you want to edit : ");
    scanf("%d", &id);
    Audio_book_Tree *temp = search(abt, id);
    if (temp == NULL)
    {
        printf("Audiobook with ID %d not found\n", id);
    }
    else
    {
        // Editing the audiobook with given ID
        int t = 1, n;
        while (t != 0)
        {
            printf("Which field you want to edit for audiobook with ID %d\n", id);
            printf("0.Exit\n");
            printf("1.Title\n");
            printf("2.Auhtor\n");
            printf("3.Duration\n");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("Enter new title\n");
                scanf("%s", temp->Title);
                printf("Title edited successfully\n");
            }
            else if (n == 2)
            {
                printf("Enter new Auhtor\n");
                scanf("%s", temp->Author);
                printf("Author edited successfully\n");
            }
            else if (n == 3)
            {
                printf("Enter new duration\n");
                scanf("%f", &temp->duration);
                printf("Duration edited successfully\n");
            }
            else if (n == 0)
            {
                t = 0;
            }
        }
    }
}
// Function to search for the user with given ID  in the Userlist
User_Tree *search_user_id(User_Tree *root, int id)
{
    User_Tree *temp = root;
    User_Tree *ans = NULL;
    int found = 0;
    while (temp != NULL && !found)
    {
        if (temp->User_id == id)
        {
            ans = temp;
            found = 1;
        }
        else if (temp->User_id < id)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    return ans;
}
// Fuction to search for the user with the given Email in the Userlist
User_Tree *search_user_email(User_Tree *root, char email[])
{
    User_Tree *ans = NULL;
    if (root != NULL)
    {
        if (strcmp(email, root->Email) == 0)
            ans = root;
        if (ans == NULL)
        {
            User_Tree *left_ans = search_user_email(root->left, email);
            User_Tree *right_ans = search_user_email(root->right, email);
            if (left_ans)
                ans = left_ans;
            else
                ans = right_ans;
        }
    }
    return ans;
}
// Function to add user to Userlist
void add_user_profile(User_Tree **uth)
{
    int id;
    char email[MAXLEN];
    char word[MAXLEN];
    User_Tree *ut = (*uth);
    printf("Enter ID for new user:");
    scanf("%d", &id);
    printf("Enter email for new user:");
    scanf("%s", email);
    // searching if user with given ID exists
    if (search_user_id(ut, id) != NULL)
        printf("User ID already exist\n");
    // searching if user with given email exists
    else if (search_user_email(ut, email) != NULL)
        printf("Email already exist\n");
    else
    {
        // Creating new user
        User_Tree *new_user = (User_Tree *)malloc(sizeof(User_Tree));
        new_user->User_id = id;
        strcpy(new_user->Email, email);
        printf("Enter Name for user:");
        scanf("%s", new_user->Name);
        printf("Enter author preference:");
        scanf("%s", new_user->Author_preference);
        printf("Enter genre preference:");
        scanf("%s", new_user->Genere_preference);
        printf("Enter narrator preference:");
        scanf("%s", new_user->Narrator_preference);
        new_user->right = NULL;
        new_user->left = NULL;
        new_user->height = 0;
        // Inserting user in user avl tree
        ut = insert_into_avl_user(ut, new_user);
        printf("User added successfully\n");
        (*uth) = ut;
    }
}
// Function to Balance the Tree in the Modified Path
Audio_book_user_Tree *delete_abt_user_helper(Audio_book_user_Tree *root, Audio_book_user_Tree *smallparent)
{
    if (root->Audio_book_id > smallparent->Audio_book_id)
    {

        root->left = delete_abt_user_helper(root->left, smallparent);
    }
    else if (root->Audio_book_id < smallparent->Audio_book_id)
    {

        root->right = delete_abt_user_helper(root->right, smallparent);
    }
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    root->height = maxi(left, right) + 1;
    if (abs(left - right) <= 1)
    {
        // it is avl no need of extra cases

        return root;
    }
    else if (root != NULL)
    {
        if (left > right)
        {
            int l = root->left->left ? root->left->left->height : -1;
            int r = root->left->right ? root->left->right->height : -1;

            if (r > l)
            {
                root->left = Leftrotation_abu(root->left);
                // lr
            }
            root = Rightrotation_abu(root);
            // ll
        }
        // right rotation
        else if (right > left)
        {
            int l = root->right->left ? root->right->left->height : -1;
            int r = root->right->right ? root->right->right->height : -1;
            if (l > r)
            {
                root->right = Rightrotation_abu(root->right);
                // rl
            }
            root = Leftrotation_abu(root);
            // rr
        }
    }

    return root;
}
// Function to delete Audiobook using BST deletion Technique
void delete_Audio_book_user_bst(Audio_book_user_Tree **root)
{
    Audio_book_user_Tree *nptr = (*root);
    if (nptr != NULL)
    {
        if (nptr->right == NULL && nptr->left == NULL)
        {
            (*root) = NULL;
            free(nptr);
        }
        else if (nptr->right == NULL)
        {
            (*root) = nptr->left;

            free(nptr);
        }
        else if (nptr->left == NULL)
        {
            (*root) = nptr->right;

            free(nptr);
        }
        else
        {

            Audio_book_user_Tree *prev, *ptr;
            // take left go to right of left
            prev = nptr->left;
            ptr = nptr->left;
            while (ptr->right != NULL)
            {
                prev = ptr;
                ptr = ptr->right;
            }
            if (ptr == prev)
            {
                ptr->right = nptr->right;
                free(nptr);

                // i have to balance tree fr ptr only
            }
            else
            {
                int l = prev->left ? prev->left->height : -1;
                int r = ptr->left ? ptr->left->height : -1;

                prev->right = ptr->left;
                ptr->height = 1 + maxi(l, r);

                ptr->right = nptr->right;
                ptr->left = nptr->left;

                free(nptr);
                // set function
            }

            (*root) = delete_abt_user_helper(ptr, prev);
        }
    }

    return;
}
// Function to delete Audiobook Using AVL deletion Tecchnique
Audio_book_user_Tree *delete_abut_rec(Audio_book_user_Tree *root, int id)
{
    if (root->Audio_book_id == id)
    {
        delete_Audio_book_user_bst(&root);
        return root;
    }
    else if (root->Audio_book_id > id)
    {
        root->left = delete_abut_rec(root->left, id);
    }
    else
    {
        root->right = delete_abut_rec(root->right, id);
    }
    int left = root->left ? root->left->height : -1;
    int right = root->right ? root->right->height : -1;
    root->height = maxi(left, right) + 1;
    if (abs(left - right) <= 1)
    {
        // it is avl no need of extra cases

        return root;
    }
    else if (root != NULL)
    {
        if (left > right)
        {
            int l = root->left->left ? root->left->left->height : -1;
            int r = root->left->right ? root->left->right->height : -1;

            if (r > l)
            {
                root->left = Leftrotation_abu(root->left);
                // lr
            }
            root = Rightrotation_abu(root);
            // ll
        }
        // right rotation
        else if (right > left)
        {
            int l = root->right->left ? root->right->left->height : -1;
            int r = root->right->right ? root->right->right->height : -1;
            if (l > r)
            {
                root->right = Rightrotation_abu(root->right);
                // rl
            }
            root = Leftrotation_abu(root);
            // rr
        }
    }

    return root;
}
// Fuction to add/delete Audiobooks to user with the given ID
void Add_to_User_library(User_Tree *userlist, Audio_book_Tree *audiolist)
{
    int n;
    int id;
    printf("Enter ID of user you want to add/delete audiobook :");
    scanf("%d", &id);
    User_Tree *utemp = search_user_id(userlist, id); // Getting the user
    if (utemp == NULL)
    {
        printf("User not found\n");
    }
    else
    {
        // providing options for user to select
        printf("Enter number of which operation to be performed\n");
        printf("1.Add audiobook to user audiolist with user ID %d\n", id);
        printf("2.Delete audiobook from user audiolist with user ID %d\n", id);
        scanf("%d", &n);
        if (n == 1)
        {
            printf("Enter audiobook ID:");
            scanf("%d", &id);
            // seraching audiobook with given id
            Audio_book_user_Tree *abu_search = search_abu(utemp->audiobooks, id);
            if (abu_search != NULL)
            {
                printf("Audiobook with ID %d is already present in user library\n", id);
            }
            else
            {
                Audio_book_Tree *new_book = search(audiolist, id);
                if (new_book == NULL)
                {
                    printf("Audiobook with ID %d is not present in audiolist\n", id);
                }
                else
                {
                    Audio_book_user_Tree *new_user_ab = (Audio_book_user_Tree *)malloc(sizeof(Audio_book_user_Tree));
                    new_user_ab->Audio_book_id = new_book->Audio_book_id;
                    strcpy(new_user_ab->Author, new_book->Author);
                    strcpy(new_user_ab->Genere, new_book->Genere);
                    strcpy(new_user_ab->Narrator, new_book->Narrator);
                    strcpy(new_user_ab->Title, new_book->Title);
                    new_user_ab->count_rating = new_book->count_rating;
                    new_user_ab->duration = new_book->duration;
                    new_user_ab->sum_rating = new_book->sum_rating;
                    new_user_ab->right = NULL;
                    new_user_ab->left = NULL;
                    new_user_ab->height = 0;
                    new_user_ab->timestamp = 0.0;
                    // inserting it in user audiolist
                    utemp->audiobooks = insert_into_avl_abu(utemp->audiobooks, new_user_ab);
                    // inordertraversal_Audiobook_users(utemp->audiobooks);
                    printf("Audiobook added successfully\n");
                }
            }
        }
        else if (n == 2)
        {
            printf("Enter audiobook ID:");
            scanf("%d", &id);
            // searching audiobook from user's audiolist
            Audio_book_user_Tree *abu_search = search_abu(utemp->audiobooks, id);
            if (abu_search == NULL)
            {
                printf("Audiobook with ID %d is not  present in user library\n", id);
            }
            else
            {
                // deleting that audiobook
                utemp->audiobooks = delete_abut_rec(utemp->audiobooks, abu_search->Audio_book_id);
            }
            printf("Audio book Deleted Successfully\n");
        }
    }
}
// Function to search Audiobooks with Multiple choices
void search_by_choice(Audio_book_Tree *root, char word[], int n, int *found)
{
    if (root != NULL)
    {
        search_by_choice(root->left, word, n, found);
        if ((n == 1 && strcmp(word, root->Title) == 0) || (n == 2 && strcmp(word, root->Genere) == 0) || (n == 3 && strcmp(word, root->Author) == 0))
        {
            (*found) = 1;
            printf("Audiobook with ID %d\n", root->Audio_book_id);
        }
        search_by_choice(root->right, word, n, found);
    }
    return;
}
// Function to display Audiobooks Providing Multiple Choices
void Search_audiobook(Audio_book_Tree *abt)
{
    int n;
    char word[MAXLEN];
    // providing options for user
    printf("Based on which field you want to search audiobooks\n");
    printf("1.Title\n");
    printf("2.Genre\n");
    printf("3.Author\n");
    scanf("%d", &n);
    int found = 0;
    if (n == 1)
    {
        printf("Enter title : ");
        scanf("%s", word);
        // searching by title
        search_by_choice(abt, word, n, &found);
        if (found == 0)
            printf("Audiobook with title not found\n");
        else
            printf("Above are audiobooks with title %s\n", word);
    }
    else if (n == 2)
    {
        printf("Enter genre : ");
        scanf("%s", word);
        search_by_choice(abt, word, n, &found);
        // searching by genre
        if (found == 0)
            printf("Audiobook with genre not found\n");
        else
            printf("Above are audiobooks with genre %s\n", word);
    }
    else if (n == 3)
    {
        printf("Enter author : ");
        scanf("%s", word);
        search_by_choice(abt, word, n, &found);
        // searching by author
        if (found == 0)
            printf("Audiobook with author not found\n");
        else
            printf("Above are audiobooks with author %s\n", word);
    }
    else
    {
        printf("Invalid input\n");
    }

    return;
}
// Function to add Listening time to user's Audiobooks
void Listening_progress(User_Tree *users, Audio_book_Tree *abt)
{
    int id;
    printf("Enter user ID to add his/her listening progress : ");
    scanf("%d", &id);
    User_Tree *user = search_user_id(users, id); // finding user
    if (user == NULL)
    {
        printf("User not found\n");
    }
    else
    {
        printf("Enter audiobook ID from user's library to add its listening progress : ");
        scanf("%d", &id);
        Audio_book_user_Tree *ab = search_abu(users->audiobooks, id); // finding user's audiobook
        if (ab == NULL)
        {
            printf("Audio book not found in user's library\n");
        }
        else
        {
            float time;
            printf("ID :%d\n", ab->Audio_book_id);
            printf("Enter timestamp to be added : ");
            scanf("%f", &time);
            // updating the timestamp
            ab->timestamp += time;
            printf("Time stamp updated successfully\n");
        }
    }
}
// Function to create new user's  Audiobook tree based on the the timestamp
Audio_book_user_Tree *insert_by_sorted_timestamp(Audio_book_user_Tree *root, Audio_book_user_Tree *newnode)
{
    if (root == NULL)
    {
        root = newnode;
    }
    else
    {
        if (root->timestamp >= newnode->timestamp)
        {
            root->left = insert_by_sorted_timestamp(root->left, newnode);
        }
        else if (root->timestamp < newnode->timestamp)
        {
            root->right = insert_by_sorted_timestamp(root->right, newnode);
        }
        int left = root->left ? root->left->height : -1;
        int right = root->right ? root->right->height : -1;
        root->height = maxi(left, right) + 1;
        if (abs(left - right) <= 1)
        {
            // it is avl no need of extra cases
            return root;
        }
        else
        {
            if (left > right)
            {
                int l = root->left->left ? root->left->left->height : -1;
                int r = root->left->right ? root->left->right->height : -1;

                if (r > l)
                {
                    root->left = Leftrotation_abu(root->left);
                    // lr
                }
                root = Rightrotation_abu(root);
                // ll
            }
            // right rotation
            else if (right > left)
            {
                int l = root->right->left ? root->right->left->height : -1;
                int r = root->right->right ? root->right->right->height : -1;
                if (l > r)
                {
                    root->right = Rightrotation_abu(root->right);
                    // rl
                }
                root = Leftrotation_abu(root);
                // rr
            }
        }
    }
    return root;
}
// Function to travel through the user's Audiobooks
Audio_book_user_Tree *abu_sort_by_timestamp(Audio_book_user_Tree *abu_sorted, Audio_book_user_Tree *abu_ptr)
{
    if (abu_ptr != NULL)
    {
        abu_sorted = abu_sort_by_timestamp(abu_sorted, abu_ptr->left);
        // creating new tree
        Audio_book_user_Tree *new_abu = (Audio_book_user_Tree *)malloc(sizeof(Audio_book_user_Tree));
        new_abu->Audio_book_id = abu_ptr->Audio_book_id;
        strcpy(new_abu->Author, abu_ptr->Author);
        new_abu->count_rating = abu_ptr->count_rating;
        new_abu->duration = abu_ptr->duration;
        strcpy(new_abu->Genere, abu_ptr->Genere);
        new_abu->height = 0;
        new_abu->left = NULL;
        strcpy(new_abu->Narrator, abu_ptr->Narrator);
        new_abu->right = NULL;
        new_abu->sum_rating = abu_ptr->sum_rating;
        new_abu->timestamp = abu_ptr->timestamp;
        strcpy(new_abu->Title, abu_ptr->Title);
        // adding accordingly
        abu_sorted = insert_by_sorted_timestamp(abu_sorted, new_abu);
        abu_sorted = abu_sort_by_timestamp(abu_sorted, abu_ptr->right);
    }
    return abu_sorted;
}
void search_by_choice_abu(Audio_book_user_Tree *root, char word[], int n, int *found)
{
    if (root != NULL)
    {
        search_by_choice_abu(root->left, word, n, found);
        if (n == 1 || (n == 2 && strcmp(word, root->Genere) == 0) || (n == 3 && strcmp(word, root->Title) == 0))
        {
            (*found) = 1; // atleast 1  audiobook found
            printf("Audiobook with ID %d\n", root->Audio_book_id);
        }
        search_by_choice_abu(root->right, word, n, found);
    }
    return;
}
// Function to Display User's Library Providing Multiple Choices
void Display_user_libraries(User_Tree *users)
{
    int id;
    printf("Enter user ID for diplaying his/her library : ");
    scanf("%d", &id);
    User_Tree *user = search_user_id(users, id); // searching user
    if (user == NULL)
    {
        printf("User not found\n");
    }
    else
    {
        // sorting based on timestamp
        Audio_book_user_Tree *abu_sorted = abu_sort_by_timestamp(NULL, user->audiobooks);
        inordertraversal_Audiobook_users(abu_sorted);
        int n;
        int *found;
        (*found) = 0;
        char word[MAXLEN];
        // providing user choice to display audiobooks
        printf("Select criteria to display user library\n");
        printf("1.Display all audiobooks\n");
        printf("2.Display by genre\n");
        printf("3.Display by title\n");
        scanf("%d", &n);
        if (n == 1)
        {
            search_by_choice_abu(abu_sorted, NULL, n, found);
        }
        else if (n == 2)
        {
            printf("Enter genre : ");
            scanf("%s", word);
            search_by_choice_abu(abu_sorted, word, n, found);
        }
        else if (n == 3)
        {
            printf("Enter title : ");
            scanf("%s", word);
            search_by_choice_abu(abu_sorted, word, n, found);
        }

        if ((*found) == 0)
        {
            printf("No audiobooks with given critera found\n");
        }
    }
}
// Function to update Rating in the user's Library
void update_audiobook_from_users(User_Tree *users, float sum_rating, int count_rating, int id)
{
    if (users != NULL)
    {
        update_audiobook_from_users(users->left, sum_rating, count_rating, id);
        Audio_book_user_Tree *abu = search_abu(users->audiobooks, id); // getting audiobook from user audiolist
        if (abu != NULL)
        {
            // updating ratings
            abu->sum_rating = sum_rating;
            abu->count_rating = count_rating;
        }
        update_audiobook_from_users(users->right, sum_rating, count_rating, id);
    }
}
// Function to Rate Audiobook in the Audiolist
void Rate_Audiobook(User_Tree *users, Audio_book_Tree *abt)
{
    int id;
    printf("Enter user ID to rate an audiobook : ");
    scanf("%d", &id);
    User_Tree *user = search_user_id(users, id); // seraching user
    if (user == NULL)
    {
        printf("User not found\n");
    }
    else
    {
        printf("Enter audiobook ID to rate : ");
        scanf("%d", &id);
        Audio_book_user_Tree *abu = search_abu(user->audiobooks, id); // seraching audiobook in user's audiolist
        if (abu == NULL)
        {
            printf("Audiobook not found\n");
        }
        else
        {
            printf("Enter rating for this audiobook (from 1-5) : "); // taking rating from user
            float r;
            scanf("%f", &r);
            while (r < 1 || r > 5)
            {
                printf("Please give correct rating (from 1-5) : ");
                scanf("%f", &r);
            }
            abu->sum_rating += r;
            abu->count_rating += 1;
            // updating rating of audiobook from main audiolist
            Audio_book_Tree *ab = search(abt, abu->Audio_book_id);
            ab->sum_rating = abu->sum_rating;
            ab->count_rating = abu->count_rating;
            // updating from users' audiolist
            update_audiobook_from_users(users, abu->sum_rating, abu->count_rating, id);
            printf("Rating updated successfully\n");
        }
    }
}
// Function to find Most Popular Audiobook in the Audiolist
void get_popular(Audio_book_Tree *root, float *max, Audio_book_Tree **ans)
{
    if (root != NULL)
    {
        get_popular(root->left, max, ans);
        float k = (root->sum_rating / root->count_rating);
        if (k > (*max))
        {
            // updating the max rating and most popular audiobook
            (*max) = k;
            (*ans) = root;
        }
        get_popular(root->right, max, ans);
    }
    return;
}
// Function to Display the Most Popular Audiobbok Details
void Most_Popular_Audio_book(Audio_book_Tree *root)
{
    Audio_book_Tree *ans = NULL;
    float max = 0.0;
    get_popular(root, &max, &ans);
    if (ans == NULL)
    {
        printf("Audio books are not rated yet\n");
    }
    else
    {
        printf("The Most Popular Audio book Title : %s Author : %s Average rating : %f", ans->Title, ans->Author, (ans->sum_rating / ans->count_rating));
    }
    return;
}
// Function to Display the Details of Listening time of every Audiobook in the User's List
void Calculate_time(Audio_book_user_Tree *root, float *total_time)
{
    if (root != NULL)
    {

        Calculate_time(root->left, total_time);
        if (root->timestamp > 0.0)
        {
            // adding the timestamp and dispalying details
            printf("Title : %s Author : %s Listened Time : %f \n", root->Title, root->Author, root->timestamp);
            (*total_time) += root->timestamp;
        }
        Calculate_time(root->right, total_time);
    }

    return;
}
// Function to Calculate the Listening time of user with the given ID
void Listening_History_report_User(User_Tree *root, int id)
{
    User_Tree *usernode = search_user_id(root, id);
    if (usernode == NULL)
    {
        printf("User with the given ID %d not exist\n", id);
    }
    else
    {
        float total_time = 0.0;
        // adding total time
        Calculate_time(usernode->audiobooks, &total_time);
        if (total_time == 0.0)
        {
            printf("User hasn't listened to any Audio book\n");
        }
        else
        {
            printf("Above are the audiobooks listened by user\n");
            printf("The total Listening time of user %s is %.2f", usernode->Name, total_time);
        }
    }

    return;
}
// Function to  travel through User's Library to calculate the Listening Time of Audiobook with given ID
void Calculate_time_Audio_book(Audio_book_user_Tree *root, float *total_time, int id)
{
    if (root != NULL)
    {
        // adding all the total timestamp of particular audiobook
        Calculate_time(root->left, total_time);
        if (root->Audio_book_id == id)
        {
            (*total_time) += root->timestamp;
        }
        Calculate_time(root->right, total_time);
    }

    return;
}
// Function to travel through User's list
void travel_user(User_Tree *root, float *total_time, int id)
{

    if (root != NULL)
    {
        travel_user(root->left, total_time, id);
        Calculate_time_Audio_book(root->audiobooks, total_time, id);
        travel_user(root->right, total_time, id);
    }
}

// Function to display the Listening History Report of Audiobook with given ID
void Listening_History_Audio_book(Audio_book_Tree *root, int id, User_Tree *user_root)
{
    Audio_book_Tree *audiobook = search(audiobook, id);
    if (audiobook == NULL)
    {
        printf("Audio book with ID %d not exist ", id);
    }
    else
    {
        float total_time = 0.0;
        travel_user(user_root, &total_time, id);
        printf("Title : %s  Audio book id : %d Author : %s Total Listening time : %f", audiobook->Title, audiobook->Audio_book_id, audiobook->Author, total_time);
    }

    return;
}
// Function to display  the Information of Audiobooks with in the given range
void Range_search_helper(Audio_book_Tree *root, int id1, int id2, int *found)
{
    if (root != NULL)
    {
        Range_search_helper(root->left, id1, id2, found);
        if (root->Audio_book_id < id2 && root->Audio_book_id > id1)
        {
            // printing audiobook in given range
            printf("ID: %d\t Title  %s\n", root->Audio_book_id, root->Title);
            (*found) = 1;
        }
        Range_search_helper(root->right, id1, id2, found);
    }

    return;
}

void Range_search(Audio_book_Tree *root, int id1, int id2)
{
    if (id1 > id2)
    {
        int temp = id1;
        id1 = id2;
        id2 = temp;
    }
    if (id1 == id2)
    {
        printf("Both are same\n");
    }
    else
    {
        int found = 0;
        Range_search_helper(root, id1, id2, &found);
        if (found == 0)
        {
            printf("No audiobook exist between ID %d and ID %d\n", id1, id2);
        }
        else
        {
            printf("Above are the audiobooks between ID %d and %d\n", id1, id2);
        }
    }

    return;
}
// Function to print the information in the Audiobook  to the File
void helper_output(Audio_book_Tree *root, FILE **fpm)
{
    if (root != NULL)
    {
        helper_output(root->left, fpm);
        FILE *fp = (*fpm);
        fprintf(fp, "%d\t", root->Audio_book_id);
        fprintf(fp, "%s\t\t", root->Title);
        fprintf(fp, "%s\t\t", root->Author);
        fprintf(fp, "%s\t\t", root->Narrator);
        fprintf(fp, "%.2f\t\t", root->duration);
        fprintf(fp, "%s\t\t", root->Genere);
        fprintf(fp, "%.2f\t\t", root->sum_rating);
        fprintf(fp, "%d\n", root->count_rating);
        (*fpm) = fp;
        helper_output(root->right, fpm);
    }
    return;
}
// Function to Modify the Audiobook  Input File
void Modify_audiobook_tree_ouput(Audio_book_Tree *root)
{

    FILE *fp = fopen("Audio_book_input.txt", "w");
    helper_output(root, &fp);
    fclose(fp);
    return;
}
// Function to print the ID's of Audiobooks present in the User Library
void get_Audio_book_helper(Audio_book_user_Tree *root, int array[], int *size)
{
    if (root != NULL)
    {
        get_Audio_book_helper(root->left, array, size);
        array[*size] = root->Audio_book_id;
        (*size) = (*size) + 1;
        get_Audio_book_helper(root->right, array, size);
    }
    return;
}
// Function to print the details of User's to the File
void helper_user_output(User_Tree *root, FILE **fp)
{
    if (root != NULL)
    {
        helper_user_output(root->left, fp);

        fprintf(*fp, "%d\t", root->User_id);
        fprintf(*fp, "%s\t\t", root->Name);
        fprintf(*fp, "%s\t\t", root->Email);
        fprintf(*fp, "%s\t\t", root->Narrator_preference);

        fprintf(*fp, "%s\t\t", root->Author_preference);
        fprintf(*fp, "%s\t\t", root->Genere_preference);
        int array[20] = {0};
        int size = 0;

        get_Audio_book_helper(root->audiobooks, array, &size);
        int i = 0;
        while (i < size)
        {
            fprintf(*fp, "%d\t", array[i]);
            i++;
        }
        fprintf(*fp, "%s\n", "end");
        helper_user_output(root->right, fp);
    }
}
// Function to Modify the User's Input File
void Modify_Users_tree_output(User_Tree *root)
{
    FILE *fp = fopen("users_input.txt", "w");
    helper_user_output(root, &fp);

    fclose(fp);
    return;
}
int main()
{
    Audio_book_Tree *Audio_list = create_audiobook_tree();
    // inordertraversal_Audiobook(Audio_list);
    User_Tree *Users_list = create_user_tree(Audio_list);
    inordertraversal_users(Users_list);
    add_AudioBook(&Audio_list, 00, "Title", "Author", "Narrator", 4.5, "Genre", 4.0);
    // Edit_audiobook(Audio_list);
    // Delete_Audio_book(&Audio_list);
    // add_user_profile(&Users_list);
    // Add_to_User_library(Users_list, Audio_list);
    // Search_audiobook(Audio_list);
    // Listening_progress(Users_list, Audio_list);
    Display_user_libraries(Users_list);
    // Rate_Audiobook(Users_list, Audio_list);
    // Most_Popular_Audio_book(Audio_list);
    // Listening_History_report_User(Users_list,3);
    // Listening_History_Audio_book(Audio_list,4,Users_list);
    // Range_search(Audio_list,2,7);
    Modify_audiobook_tree_ouput(Audio_list);
    Modify_Users_tree_output(Users_list);

    return 0;
}

