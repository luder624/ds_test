#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode *tree;
struct treeNode{
    int data;
    tree rightChild;
    tree leftChild;
};

tree root;
FILE *output;

void insert(int data){		//因為是放進去，所以會需要malloc，跟要傳入的data，但不需要回傳值。 

    tree lead, tail;
    tree temp = (tree) malloc(sizeof(struct treeNode));
	//temp內資料初始化 
    temp->data = data;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
	
    if(!root)			//若無 root 
        root = temp;	//temp 直接為 root 
    else{
        lead = root;	//從 root開始 
        while(lead){	//當 lead不為NULL時 
            tail = lead;	//tail要是 lead的 parent 
            if(temp->data > lead->data)			//用lead開始走訪 
                lead = lead->rightChild;		//temp->data大於 lead -> data : 向右走 
            else if(temp->data < lead->data)
                lead = lead->leftChild;			//temp->data小於 lead -> data : 向左走
            else
                break;
        }
        if(!lead){		//沒這個點 
            if(temp->data > tail->data)
                tail->rightChild = temp;	 
            else if(temp->data < tail->data)
                tail->leftChild = temp;		 
        }
        else
            free(temp);//lead不為NULL，代表 temp用不上了 
    }
}

void delete(int data){

    tree lead, tail, middle, deleteNode;
	lead = NULL;
    tail = NULL;
    middle = NULL;

    for(deleteNode = root ; deleteNode ;){		//當deleteNode != NULL 
	
        tail = middle;
        middle = deleteNode;
		//deleteNode是來找data的，找到就定住。 
        if(data > deleteNode->data)
            deleteNode = deleteNode->rightChild;
        else if(data < deleteNode->data)
            deleteNode = deleteNode->leftChild;
        else
            break;
    }
	
    if(!deleteNode) return;		//要刪的點不在裡面就return 

    lead = deleteNode;			
    middle = NULL;				

    if(deleteNode->leftChild){		//若有 leftchild ，將左邊子樹的最大值放上來 
        lead = lead->leftChild;		//lead(此時等於 deleteNode)向 leftchild走 
        tail = NULL;				
        while(lead){	
            tail = middle;			
            middle = lead;		
            lead = lead->rightChild;					//此時 lead : 主角 ，只往右子找比自己更大的 ，找到自己的靈壓消失時，將記憶傳承給middle 
        }
        deleteNode->data = middle->data;				//將 middle的 data 換給 deleteNode
        if(tail)										//tail為 middle的 parent，因為 middle要被刪掉了， 所以middle的兒子會繼承他的位置，成為tail的右子(原本middle是tail的右子) 
            tail->rightChild = middle->leftChild;
        else											//一開始找就找到了，所以 tail還是為 NULL，拿deleteNode來接就好 
        	deleteNode->leftChild = middle->leftChild;
		free(middle);									//middle是要換上來的那個 node的位置 ，給他死。 
    }
    else if(deleteNode->rightChild){					//若有 rightchild ，將右邊子樹的最小值放上來 
        lead = lead->rightChild;
        tail = NULL;
        while(lead){
            tail = middle;
            middle = lead;
            lead = lead->leftChild;
        }
        deleteNode->data = middle->data;
		if(tail)
            tail->leftChild = middle->rightChild;
        else
        	deleteNode->rightChild = middle->rightChild;
        free(middle);
    }
    else{		//deleteNode為葉節點 
        if(deleteNode == root)
            root = NULL;
        else if(deleteNode->data > tail->data)
            tail->rightChild = NULL;
        else if(deleteNode->data < tail->data) 
            tail->leftChild = NULL;
        free(deleteNode);
    }   
}

void road(int data, int info){

    int record;
    tree right, left;
    tree lead;

    record = 0;

    for(lead = root; lead ;){		//找lead是否存在 

        if(data > lead->data && info > lead->data)		//代表info &data都在lead的右邊 
            lead = lead->rightChild;					//移動lead
        else if(data < lead->data && info < lead->data)		//代表info &data都在lead的左邊
            lead = lead->leftChild;							//移動lead
        else
            break;
    }

    if(!lead) return;

    right = lead;
    while(right){
        if(right->data > 0) record += right->data;		//sum

        if(data > right->data)							//走走看 
            right = right->rightChild;					
        else if(data < right->data)
            right = right->leftChild;
        else
            break;
    }

    left = lead;
    while(left){
        if(left->data > 0) record += left->data;		//sum

        if(info > left->data)							//走走看 
            left = left->rightChild;
        else if(info < left->data)
            left = left->leftChild;
        else
            break;
    }

    if(lead->data > 0) record -= lead->data;			//中間那點會被重複計算，需扣掉。加回來則不必，小於零時本來就不會被加到。 
    
    if(left && right && right->data == data && left->data == info)
        fprintf(output, "%d\n", record);
}

void freeAll(tree temp){
	
    if(temp){
        freeAll(temp->leftChild);
        freeAll(temp->rightChild);
        free(temp);
    }
}

int main(){

    FILE *input;

    char c;
    
    int cnt;
    int i, j, k;
    int data, info;
    int numNode, numInstructor;

    cnt = 1;
    input = fopen("input_1-4.txt","r");
    output = fopen("output_1.txt", "w");


        fscanf(input, "%d %d", &numNode, &numInstructor);
        printf("%d %d\n",numNode,com_count);
        if(! numNode && !numInstructor) return 0 ;

        root = NULL;

        for(i = 0; i < numNode ; i++){
            fscanf(input, "%d", &data);
            insert(data);
        }

        for( j = 0; j < numInstructor ; j++){
            fscanf(input, " %c", &c);
			fgetc(input);
            switch (c)
            {
            case 'I':
                fscanf(input, "%d\n", &data);
                insert(data);
                break;
            case 'D':
                fscanf(input, "%d\n", &data);
                delete(data);
                break;
            case 'P':
                fscanf(input, "%d %d\n", &data, &info);
                road(data, info);
                break;
            default:
                break;
            }
        }

        if(root) freeAll(root);

    fclose(input);
    fclose(output);
    return 0;
}
