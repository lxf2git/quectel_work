#include"insert.h"

int insert(pStu pHead, pStu pNew, int (*pIDFind)(pStu pHead, pStu pNew), pStu (*pInsertPosition)(pStu pHead, pStu pNew))
{
  
    init_node(&pNew);

    if (NULL == pNew)
    {
        printf("Error :%s", __FUNCTION__);
        return FAILE;
        
    }
    printf("Input ID:\n");
    scanf("%d",&pNew->num);
    if((*pIDFind)(pHead,pNew) == EXIST)
    {
        printf("Input Error,ID has exist\n");
        free_node(&pNew);
        return FAILE;
    }else 
    {
        printf("Input Age:\n");
        scanf("%d",&pNew->age);
        pStu pPosition=(*pInsertPosition)(pHead, pNew);
        insert_behind(pPosition, pNew);
        printf("Input successful\n");
        
        return SUCCESSED;
    }
}
int findid(pStu pHead,pStu pNew)
{
    if(NULL == find_node_with_id(pHead,pNew->num))
    {
        return NOTHAVE;
    }else
    {
        return EXIST;
    }
}

                
