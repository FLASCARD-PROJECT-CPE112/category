//flashcard 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Category
{
    char name[100];
    struct Category* firstsub;
    struct Category* nextsub; // next category

} Category;

    
//create category
Category* createCate(const char* name)
{
    Category* newcate = (Category*)malloc(sizeof(Category)); //newcate = main cate name 
    strcpy(newcate->name, name);
    newcate->firstsub = NULL; // SET! start = NULL no child
    newcate->nextsub = NULL; // no sibling yet
    return newcate;

}


//find category (parent)
Category* findCate(Category* Node, const char* name)
{
    if (Node == NULL)  // Node = main node
    {
        return NULL;
    }
    
    if (strcmp(Node->name, name) == 0) // can find name (match)
    {
        return Node;
    }
    

    Category* found = findCate(Node->firstsub, name);
    if (found != NULL)
    {
        return found;
    }

    return findCate(Node->nextsub, name);
    
}


//add sub category in main
void addsubCate(Category* parent, Category* child) //add child in parent
{
    if (parent->firstsub == NULL)
    {
        parent->firstsub = child;
    }
    else //case already have child
    {
        Category* temp = parent->firstsub; //temp: check how many child in parent 

        while (temp->nextsub != NULL)
        {
            temp = temp->nextsub;
        }

        temp->nextsub = child;
        
    }
    
}

//remove category
Category* findParent(Category* curr, const char* name) //curr = current > main category
{
    if (curr == NULL) //nothing (stop) check main category first (like MAth)
    {
        return NULL; 
    }

    Category* child = curr->firstsub;
    while (child != NULL) // check child in main category
    {
        if (strcmp(child->name, name) == 0)
        {
            return curr;
        }

        Category* found = findParent(child, name);
        if (found) //find another child
        {
            return found;
        }
        child = child->nextsub; 
        
        
    }

    return NULL;
    
}

void removeCate(Category* parent, const char* name)
{                          //no child
    if (parent == NULL || parent->firstsub == NULL)
    {
        return ;
    }

    Category* curr = parent->firstsub; //pointer(curr)
    Category* prev = NULL;

    while (curr != NULL && strcmp(curr->name, name) != 0)
    {
        prev = curr;
        curr = curr->nextsub;
    }

    if (curr == NULL)
    {
        printf("Category not found.\n");
        return;
    }

    if (prev == NULL)
    {
        parent->firstsub = curr->nextsub;
    }
    else
    {
        prev->nextsub = curr->nextsub;
    }

    free(curr);
    printf("Category < %s > removed successfully.\n", name);
    
    
}


//show all category
void printCate(Category* Node, int level)
{
    if (Node == NULL)
    {
        return;
    }

    for (int i = 0; i < level; i++)
    {
        printf("  ");
    }

    printf("- %s\n", Node->name);

    printCate(Node->firstsub, level + 1);

    printCate(Node->nextsub, level);
    
}

/*
print
> - Math
    - M1
    - M2
  - Science
*/

int main() 
{
   
    Category* Node = createCate("root");

    int choice;
    char parentName[100];
    char newName[100];

    while (1) 
    {
        printf("\n-----Menu-----\n");
        printf("1. Add Main Category\n");
        printf("2. Add Sub Category\n");
        printf("3. Show All Categories\n");
        printf("4. Remove Category\n");
        printf("5. Exit\n");
        printf("Select: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) 
        {
            printf("Enter new main category name: ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            Category* newcate = createCate(newName);
            addsubCate(Node, newcate);

            printf("Main category added successfully\n");
        }
        else if (choice == 2) 
        {
            printf("Add main category name: ");
            fgets(parentName, sizeof(parentName), stdin);
            parentName[strcspn(parentName, "\n")] = '\0';

            Category* parent = findCate(Node, parentName);
            if (parent == NULL) 
            {
                printf("Category not found\n");
                continue;
            }

            printf("Enter subcategory name: ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            Category* newCate = createCate(newName);
            addsubCate(parent, newCate);

            printf("Subcategory added successfully\n");
        }
        else if (choice == 3) 
        {
            printf("\n All Categories:\n");
            printCate(Node->firstsub, 0); 
        }
        else if (choice == 4)
        {
            printf("Enter category name to remove (main or sub): ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            if (strcmp(Node->name, newName) == 0)
            {
                printf("Can't remove main category\n");
                continue;
                
            }

            Category* parent = findParent(Node, newName);

            if (parent == NULL)
            {
                printf("Category not found\n");
            }

            else
            {
                removeCate(parent, newName);
            }   
            
        }
        
        else if (choice == 5) 
        {
            printf("Exiting the program\n");
            break;
        }
        else 
        {
            printf("Invalid selection. Please try again.\n");
        }
    }

    return 0;
}
