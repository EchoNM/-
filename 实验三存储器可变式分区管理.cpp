#include <iostream>
#include <string>
#define inf 10 
using namespace std;
 
int sum = 0;   //内存区域的整个大小
int alreadyUse = 0;  //已经使用的内存区域大小
struct space { //空闲区与工作区都采用这一统一的数据结构
	int begin;  //起始地址
	int length;  //长度
	string name;  //程序名
	space *next;//指针指向下一个内存空间
};
typedef space *Space;
 
/*初始化, 此时empty起始地址为内存首地址，长度为整个内存区间，work表为空*/
void Init( Space empty, Space work, int length) {
	empty->next = NULL;
	work->next = NULL;
	empty->begin = 0;
	empty->length = length;
}
 
/*首次适应*/
void firstSuit(Space empty) {
	space* temp1 = empty;
	space* temp2 = empty;
	if (empty == NULL)
		return;
	for (;temp1->next != NULL;temp1 = temp1->next)
	{
		for (temp2 = empty;temp2->next != NULL;temp2 = temp2->next)
		{
			if (temp2->begin > temp2->next->begin)//对前后两指针起始地址进行判断，使之按从小到大排列，若前面指针地址大则进行交换 
			{
				int temp = temp2->length;
				int begin = temp2->begin;
				temp2->length = temp2->next->length;
				temp2->begin = temp2->next->begin;
				temp2->next->length = temp;
				temp2->next->begin = begin;
			}
		}
	}
}
 
/*最佳适应*/
void bestSuit(Space empty) {
	space* temp1 = empty;
	space* temp2 = empty;
	if (empty == NULL)
		return;
	for (;temp1->next != NULL;temp1 = temp1->next)
	{
		for (temp2 = empty;temp2->next != NULL;temp2 = temp2->next)
		{
			if (temp2->length > temp2->next->length)//对前后两指针所占空间进行判断，使之按从小到大排列，若前面指针空间大则进行交换
			{
				int temp = temp2->length;
				int begin = temp2->begin;
				temp2->length = temp2->next->length;
				temp2->begin = temp2->next->begin;
				temp2->next->length = temp;
				temp2->next->begin = begin;
			}
		}
	}
}
 
/*根据选择对empty链表进行排序*/
void sortBychoice(Space empty, int choice) {
	switch (choice)
	{
	case 1:
		firstSuit(empty);
		break;
	case 2:
		bestSuit(empty);
		break;
	default:
		cout << "*        未知的选择,默认当前选择!        *" << endl;
		break;
	}
}
 

void displayEmpty(Space empty) {
	cout << endl << endl << "*        empty        *" << endl << endl;
	if (empty == NULL) {
		cout << "*        无可申请空间!        *" << endl;
		return;
	}
	space *temp = new space;
	temp = empty;
	cout << "begin" << "\t" << "length" << "\t" << "状态" << endl;
	while (temp) {
		cout << temp->begin << "\t" << temp->length << "\t" << "未分配" << endl;
		temp = temp->next;
	}
	cout << endl;
}
 

void displayWork(Space work) {
	cout << endl << endl << "*        work        *" << endl << endl;
	if (work == NULL) {
		cout << "*        无可回收内存!        *" << endl;
		return;
	}
	space *temp = new space;
	temp = work->next;
	cout << "begin" << "\t" << "length" << "\t" << "程序名" << endl;
	while (temp) {
		cout << temp->begin << "\t" << temp->length <<"\t" << temp->name.c_str() << endl;
		temp = temp->next;
	}
}


void Create(Space empty, Space work) {
	int choice;
	int length;
	int m = 0;
	char name[10];
	cout << "*        请选择添加算法 :        *" << endl;
	cout << "*        1:  首次适应算法        *" << endl;
	cout << "*        2:  最佳适应算法        *" << endl;
	cin >> choice;//根据选择的不同算法对内存和空闲区重新排序 
	sortBychoice(empty,choice);
	displayEmpty(empty);
	cout << "*        输入程序需要的长度: ";
	cin >> length;
	if (length > sum - alreadyUse) {
		cout << "*        当前剩余存储区域不足以满足需求，拒绝继续添加程序" << endl;
		return;
	}
	cout << "*        输入申请内存的程序名: ";
	cin >> name;
	space *temp = new space;
	space *preTemp = new space;
	preTemp = empty;
	temp = empty;
	while (temp) {//将所申请的内存空间加入工作区 
		if (temp->length > length) {//留出10空间的阈值 
			//若差值小于阈值
			if (temp->length - length <= inf) {
				//判断是否是第一个结点
				if (temp == empty) {
					space *prog = new space;
					prog->begin = temp->begin;
					prog->length = temp->length;
					prog->name = (string)name;
					space *workList = new space;
					workList = work;
					while (workList->next) {
						workList = workList->next;
					}
					prog->next = workList->next;
					workList->next = prog;
					empty = empty->next;
				}
				else {
					space *prog = new space;
					preTemp->next = temp->next;
					prog->begin = temp->begin;
					prog->length = temp->length;
					prog->name = (string)name;
					space *workList = new space;
					workList = work;
					while (workList->next) {
						workList = workList->next;
					}
					prog->next = workList->next;
					workList->next = prog;
				}
			}
			else {
				space *prog = new space;
				prog->begin = temp->begin;
				prog->length = length;
				temp->begin = temp->begin + length;
				temp->length = temp->length - length;
				prog->name = (string)name;
				space *workList = new space;
				workList = work;
				while (workList->next) {
					workList = workList->next;
				}
				prog->next = workList->next;
				workList->next = prog;
			}
			break;
		}
		temp = temp->next;
		if (m == 1)
			preTemp = preTemp->next;
		m = 1;
	}
	displayWork(work);//分别打印出工作区和空闲区情况 
	cout << endl;
	displayEmpty(empty);
}
 
/*统计empty表长度*/
int getLength(Space empty) {
	int length = 0;
	space *temp = new space;
	temp = empty;
	while (temp)
	{
		length++;
		temp = temp->next;
	}
	return length;
}
 
//回收内存时检查上下连接，若存在连接区域，需对empty链表节点进行删除和修改
void checkAddress(Space empty) {
	space *temp = new space;
	space *preTemp = new space;
	temp = empty;
	while (temp) {
		if (temp->next) {
			if (temp->begin + temp->length == temp->next->begin) {
				temp->length = temp->length + temp->next->length;
				temp->next = temp->next->next;
			}
		}
		temp = temp->next;
	}
	preTemp = empty;
	temp = preTemp->next;
	//对末尾结点的检查
	while (temp) {
		if (temp->next == NULL) {
			if (temp->begin == preTemp->begin + preTemp->length) {
				preTemp->length = preTemp->length + temp->length;
				preTemp->next = NULL;
				break;
			}
		}
		temp = temp->next;
		preTemp = preTemp->next;
	}
}
 
 
/*回收已有的程序*/
void callBack(Space empty, Space work) {
	string name;
	int len;
	int begin;
	int length;
	int flag = 0;   //用于判断输入是否正确
	displayWork(work);
	cout << "*        输入将要回收的程序名: ";
	cin >> name;
	space *tempWork = new space;
	space *preTempwork = new space;
	space *tempEmpty = new space;
	tempWork = work->next;
	preTempwork = work;
	tempEmpty = empty;
	while (tempWork) {
		if (!tempWork->name.compare(name)){
			flag = 1; //寻找到目标程序
			begin = tempWork->begin;
			length = tempWork->length;
			len = getLength(empty);
			preTempwork->next = tempWork->next; //从work表中删除该节点
			while (tempEmpty){
				space *newEmpty = new space;
				newEmpty->begin = begin;
				newEmpty->length = length;
				newEmpty->name = "未分配";
				if (len >= 2) {
					if (tempEmpty->begin  > begin) {
						newEmpty->begin = tempEmpty->begin;
						newEmpty->length = tempEmpty->length;
						tempEmpty->begin = begin;
						tempEmpty->length = length;
						newEmpty->next = tempEmpty->next;
						tempEmpty->next = newEmpty;
						break;
					}
				}
				else {
					if (begin < tempEmpty->begin) {
						newEmpty->begin = tempEmpty->begin;
						newEmpty->length = tempEmpty->length;
						tempEmpty->begin = begin;
						tempEmpty->length = length;
						newEmpty->next = tempEmpty->next;
						tempEmpty->next = newEmpty;
 
					}
					else {
						newEmpty->next = tempEmpty->next;
						tempEmpty->next = newEmpty;
					}
					break;
				}
				tempEmpty = tempEmpty->next;    //这里不在第一次查询到就break是因为程序可能被分段存储
			}
		}
		tempWork = tempWork->next;
		preTempwork = preTempwork->next;
	}
	if (flag == 0)
		cout << "未查询到将要回收的程序段,请重新选择!" << endl;
	else {
		//合并内存
		firstSuit(empty);
		checkAddress(empty);
	}
	displayWork(work);//将回收后情况打印出来 
	displayEmpty(empty);
}
 
 
 
int main()
{	int choice, length;
	Space empty, work;
	empty = new space;
	work = new space;
	cout << "输入最大内存容量: ";
	cin >> length;
	sum = length;
	Init(empty, work, length);
								
	while (1) {
		cout << "*************************" << endl;
		cout << "*        1:添加作业     *" << endl;
		cout << "*        2:回收内存     *" << endl;
		cout << "*        3:退出程序     *" << endl;
		cout << "*        请选择:        *" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			Create(empty, work);
			break;
		case 2:
			callBack(empty, work);
			break;
		case 3:
			cout << "*				   谢谢使用!				   *" << endl;
			return 0;
		}
	}
    return 0;
}
