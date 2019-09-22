/* Problem Statement:
Verified on leetcode

https://leetcode.com/problems/find-largest-value-in-each-tree-row/

515. Find Largest value in each tree row

You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]


 *
 * Time Complexity : O(n)
 * Space Complexity : O(h) where h is height of tree 
 */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


#define MAX_QUEUE_SIZE 90000
#define ROW_COL 4
#define DIR_LEN 4

// A structure to represent a queue
typedef struct queue
{
    int front, rear, size;
    unsigned capacity;
    struct TreeNode **array;
}queue_t;

/**** Queue functions start ***/

queue_t* createqueue()
{
    queue_t* q = (queue_t*)calloc(1, sizeof(queue_t));
    q->array = (struct TreeNode **)calloc(MAX_QUEUE_SIZE, sizeof(struct TreeNode *));
    q->capacity = MAX_QUEUE_SIZE;
    q->front = q->size = 0; 
    q->rear = MAX_QUEUE_SIZE - 1;
    return q;
}
 
// queue is full when size becomes equal to the capacity 
int isFull(queue_t* queue)
{  return (queue->size == queue->capacity);  }
 
// queue is empty when size is 0
int isEmpty(queue_t* queue)
{  return (queue->size == 0); }
 
// Function to add an item to the queue.  It changes rear and size
void enqueue(queue_t* queue, struct TreeNode *item)
{
    if (isFull(queue)) {
        printf("full new capacity: %d\n", (queue->size) * 2);
        queue->array = (struct TreeNode **)realloc(queue->array, sizeof(struct TreeNode*) * (queue->size) * 2);
        queue->capacity = (queue->size) * 2;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%ld enqueued to queue\n", item->data);
}
 
// Function to remove an item from queue.  It changes front and size
struct TreeNode* dequeue(queue_t* queue)
{
    if (isEmpty(queue))
        return NULL;
    struct TreeNode *item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void free_queue(queue_t* queue) {
    free(queue->array);
    free(queue);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestValues(struct TreeNode* root, int* returnSize){
    int *final_arr = NULL;
    int curr_size = 0;
    int idx = 0;
    int max_val = 0;
    struct TreeNode *item = NULL;
    queue_t *queue = NULL;
    int max_size = 100;
    
    *returnSize = 0;
    
    if (!root) {
        return final_arr;
    }
    queue = createqueue();
    
    final_arr = (int *)malloc(sizeof(int ) * max_size);
    
    enqueue(queue, root);
    
    while (!isEmpty(queue)) {
        max_val = INT_MIN;
        curr_size = (queue->size);
        /* process each level of tree first and find max in it. Update max in the final array */
        for (idx = 0; idx < curr_size; idx++) {
            item = dequeue(queue);
            
            if (max_val < item->val)
                max_val = item->val;
            
            /* add left and right subtree */
            if (item->left != NULL) {
                enqueue(queue, item->left);
            }
            
            if (item->right != NULL) {
                enqueue(queue, item->right);
            }
            /* free item */
            free(item);
        }
        /* need to realloc */
        if (*returnSize == max_size ) {
            max_size = *returnSize * 2;
            final_arr = (int *)realloc(final_arr, sizeof(int) * max_size);
        }
        final_arr[*returnSize] = max_val;
        *returnSize = *returnSize + 1;
    }
    free_queue(queue);
    /* return final array */
    return final_arr;

}




/* Execute it on LeetCode platform*/

