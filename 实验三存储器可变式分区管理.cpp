#include <iostream>
#include <string>
#define inf 10 
using namespace std;
 
int sum = 0;   //�ڴ������������С
int alreadyUse = 0;  //�Ѿ�ʹ�õ��ڴ������С
struct space { //�������빤������������һͳһ�����ݽṹ
	int begin;  //��ʼ��ַ
	int length;  //����
	string name;  //������
	space *next;//ָ��ָ����һ���ڴ�ռ�
};
typedef space *Space;
 
/*��ʼ��, ��ʱempty��ʼ��ַΪ�ڴ��׵�ַ������Ϊ�����ڴ����䣬work��Ϊ��*/
void Init( Space empty, Space work, int length) {
	empty->next = NULL;
	work->next = NULL;
	empty->begin = 0;
	empty->length = length;
}
 
/*�״���Ӧ*/
void firstSuit(Space empty) {
	space* temp1 = empty;
	space* temp2 = empty;
	if (empty == NULL)
		return;
	for (;temp1->next != NULL;temp1 = temp1->next)
	{
		for (temp2 = empty;temp2->next != NULL;temp2 = temp2->next)
		{
			if (temp2->begin > temp2->next->begin)//��ǰ����ָ����ʼ��ַ�����жϣ�ʹ֮����С�������У���ǰ��ָ���ַ������н��� 
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
 
/*�����Ӧ*/
void bestSuit(Space empty) {
	space* temp1 = empty;
	space* temp2 = empty;
	if (empty == NULL)
		return;
	for (;temp1->next != NULL;temp1 = temp1->next)
	{
		for (temp2 = empty;temp2->next != NULL;temp2 = temp2->next)
		{
			if (temp2->length > temp2->next->length)//��ǰ����ָ����ռ�ռ�����жϣ�ʹ֮����С�������У���ǰ��ָ��ռ������н���
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
 
/*����ѡ���empty�����������*/
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
		cout << "*        δ֪��ѡ��,Ĭ�ϵ�ǰѡ��!        *" << endl;
		break;
	}
}
 

void displayEmpty(Space empty) {
	cout << endl << endl << "*        empty        *" << endl << endl;
	if (empty == NULL) {
		cout << "*        �޿�����ռ�!        *" << endl;
		return;
	}
	space *temp = new space;
	temp = empty;
	cout << "begin" << "\t" << "length" << "\t" << "״̬" << endl;
	while (temp) {
		cout << temp->begin << "\t" << temp->length << "\t" << "δ����" << endl;
		temp = temp->next;
	}
	cout << endl;
}
 

void displayWork(Space work) {
	cout << endl << endl << "*        work        *" << endl << endl;
	if (work == NULL) {
		cout << "*        �޿ɻ����ڴ�!        *" << endl;
		return;
	}
	space *temp = new space;
	temp = work->next;
	cout << "begin" << "\t" << "length" << "\t" << "������" << endl;
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
	cout << "*        ��ѡ������㷨 :        *" << endl;
	cout << "*        1:  �״���Ӧ�㷨        *" << endl;
	cout << "*        2:  �����Ӧ�㷨        *" << endl;
	cin >> choice;//����ѡ��Ĳ�ͬ�㷨���ڴ�Ϳ������������� 
	sortBychoice(empty,choice);
	displayEmpty(empty);
	cout << "*        ���������Ҫ�ĳ���: ";
	cin >> length;
	if (length > sum - alreadyUse) {
		cout << "*        ��ǰʣ��洢���������������󣬾ܾ�������ӳ���" << endl;
		return;
	}
	cout << "*        ���������ڴ�ĳ�����: ";
	cin >> name;
	space *temp = new space;
	space *preTemp = new space;
	preTemp = empty;
	temp = empty;
	while (temp) {//����������ڴ�ռ���빤���� 
		if (temp->length > length) {//����10�ռ����ֵ 
			//����ֵС����ֵ
			if (temp->length - length <= inf) {
				//�ж��Ƿ��ǵ�һ�����
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
	displayWork(work);//�ֱ��ӡ���������Ϳ�������� 
	cout << endl;
	displayEmpty(empty);
}
 
/*ͳ��empty����*/
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
 
//�����ڴ�ʱ����������ӣ������������������empty����ڵ����ɾ�����޸�
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
	//��ĩβ���ļ��
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
 
 
/*�������еĳ���*/
void callBack(Space empty, Space work) {
	string name;
	int len;
	int begin;
	int length;
	int flag = 0;   //�����ж������Ƿ���ȷ
	displayWork(work);
	cout << "*        ���뽫Ҫ���յĳ�����: ";
	cin >> name;
	space *tempWork = new space;
	space *preTempwork = new space;
	space *tempEmpty = new space;
	tempWork = work->next;
	preTempwork = work;
	tempEmpty = empty;
	while (tempWork) {
		if (!tempWork->name.compare(name)){
			flag = 1; //Ѱ�ҵ�Ŀ�����
			begin = tempWork->begin;
			length = tempWork->length;
			len = getLength(empty);
			preTempwork->next = tempWork->next; //��work����ɾ���ýڵ�
			while (tempEmpty){
				space *newEmpty = new space;
				newEmpty->begin = begin;
				newEmpty->length = length;
				newEmpty->name = "δ����";
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
				tempEmpty = tempEmpty->next;    //���ﲻ�ڵ�һ�β�ѯ����break����Ϊ������ܱ��ֶδ洢
			}
		}
		tempWork = tempWork->next;
		preTempwork = preTempwork->next;
	}
	if (flag == 0)
		cout << "δ��ѯ����Ҫ���յĳ����,������ѡ��!" << endl;
	else {
		//�ϲ��ڴ�
		firstSuit(empty);
		checkAddress(empty);
	}
	displayWork(work);//�����պ������ӡ���� 
	displayEmpty(empty);
}
 
 
 
int main()
{	int choice, length;
	Space empty, work;
	empty = new space;
	work = new space;
	cout << "��������ڴ�����: ";
	cin >> length;
	sum = length;
	Init(empty, work, length);
								
	while (1) {
		cout << "*************************" << endl;
		cout << "*        1:�����ҵ     *" << endl;
		cout << "*        2:�����ڴ�     *" << endl;
		cout << "*        3:�˳�����     *" << endl;
		cout << "*        ��ѡ��:        *" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			Create(empty, work);
			break;
		case 2:
			callBack(empty, work);
			break;
		case 3:
			cout << "*				   ллʹ��!				   *" << endl;
			return 0;
		}
	}
    return 0;
}
