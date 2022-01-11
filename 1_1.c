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

void insert(int data){		//�]���O��i�h�A�ҥH�|�ݭnmalloc�A��n�ǤJ��data�A�����ݭn�^�ǭȡC 

    tree lead, tail;
    tree temp = (tree) malloc(sizeof(struct treeNode));
	//temp����ƪ�l�� 
    temp->data = data;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
	
    if(!root)			//�Y�L root 
        root = temp;	//temp ������ root 
    else{
        lead = root;	//�q root�}�l 
        while(lead){	//�� lead����NULL�� 
            tail = lead;	//tail�n�O lead�� parent 
            if(temp->data > lead->data)			//��lead�}�l���X 
                lead = lead->rightChild;		//temp->data�j�� lead -> data : �V�k�� 
            else if(temp->data < lead->data)
                lead = lead->leftChild;			//temp->data�p�� lead -> data : �V����
            else
                break;
        }
        if(!lead){		//�S�o���I 
            if(temp->data > tail->data)
                tail->rightChild = temp;	 
            else if(temp->data < tail->data)
                tail->leftChild = temp;		 
        }
        else
            free(temp);//lead����NULL�A�N�� temp�Τ��W�F 
    }
}

void delete(int data){

    tree lead, tail, middle, deleteNode;
	lead = NULL;
    tail = NULL;
    middle = NULL;

    for(deleteNode = root ; deleteNode ;){		//��deleteNode != NULL 
	
        tail = middle;
        middle = deleteNode;
		//deleteNode�O�ӧ�data���A���N�w��C 
        if(data > deleteNode->data)
            deleteNode = deleteNode->rightChild;
        else if(data < deleteNode->data)
            deleteNode = deleteNode->leftChild;
        else
            break;
    }
	
    if(!deleteNode) return;		//�n�R���I���b�̭��Nreturn 

    lead = deleteNode;			
    middle = NULL;				

    if(deleteNode->leftChild){		//�Y�� leftchild �A�N����l�𪺳̤j�ȩ�W�� 
        lead = lead->leftChild;		//lead(���ɵ��� deleteNode)�V leftchild�� 
        tail = NULL;				
        while(lead){	
            tail = middle;			
            middle = lead;		
            lead = lead->rightChild;					//���� lead : �D�� �A�u���k�l���ۤv��j�� �A���ۤv���F�������ɡA�N�O�жǩӵ�middle 
        }
        deleteNode->data = middle->data;				//�N middle�� data ���� deleteNode
        if(tail)										//tail�� middle�� parent�A�]�� middle�n�Q�R���F�A �ҥHmiddle����l�|�~�ӥL����m�A����tail���k�l(�쥻middle�Otail���k�l) 
            tail->rightChild = middle->leftChild;
        else											//�@�}�l��N���F�A�ҥH tail�٬O�� NULL�A��deleteNode�ӱ��N�n 
        	deleteNode->leftChild = middle->leftChild;
		free(middle);									//middle�O�n���W�Ӫ����� node����m �A���L���C 
    }
    else if(deleteNode->rightChild){					//�Y�� rightchild �A�N�k��l�𪺳̤p�ȩ�W�� 
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
    else{		//deleteNode�����`�I 
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

    for(lead = root; lead ;){		//��lead�O�_�s�b 

        if(data > lead->data && info > lead->data)		//�N��info &data���blead���k�� 
            lead = lead->rightChild;					//����lead
        else if(data < lead->data && info < lead->data)		//�N��info &data���blead������
            lead = lead->leftChild;							//����lead
        else
            break;
    }

    if(!lead) return;

    right = lead;
    while(right){
        if(right->data > 0) record += right->data;		//sum

        if(data > right->data)							//������ 
            right = right->rightChild;					
        else if(data < right->data)
            right = right->leftChild;
        else
            break;
    }

    left = lead;
    while(left){
        if(left->data > 0) record += left->data;		//sum

        if(info > left->data)							//������ 
            left = left->rightChild;
        else if(info < left->data)
            left = left->leftChild;
        else
            break;
    }

    if(lead->data > 0) record -= lead->data;			//�������I�|�Q���ƭp��A�ݦ����C�[�^�ӫh�����A�p��s�ɥ��ӴN���|�Q�[��C 
    
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
