#include "Client.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace NetworkHelper;

void showRoom(ClientHelper& _client) {
	/*******************************
	չʾ�����б�
	getRoomList(room_list_t)����ֵΪbool������Ϊroom_list_t�����á�
	����ɹ���ȡ��������Ϣ����������true�����ҽ������б����ṹ��room_list_t��
	room_list_t�ṹ����
	struct room_list_t {
		uint32_t roomNum;   // ��ǰ���ڵķ�������
		room_t *rooms;    // ÿ���������Ϣ
	};
	room_t�ṹ����
	struct room_t {
		uint32_t roomId;     // ����id
		uint32_t existing;	 // ��������
		char roomName[40];	 // ������
		msg_t* everyOne;     // ���ڱ�������û�д���ó�Ա
	};
	������(showRoom)�ṩ�˶�ȡ������Ϣ��˼·�ο�
	********************************/
	room_list_t rlt;
	if (!_client.getRoomList(rlt)) {
		printf("��ȡ�б�ʧ��\n");
		return;
	}
	printf("��������:\t%u\n----�б�����----\n", rlt.roomNum);
	for (uint32_t i = 0; i < rlt.roomNum; ++i) {
		printf("����%u:\n", i + 1);
		printf("������:%s\t����id:%u\t��ǰ����:%u\n", rlt.rooms[i].roomName, rlt.rooms[i].roomId, rlt.rooms[i].existing);
	}
}

void queryRoom(ClientHelper& _client) {
	/*******************************
	��ѯ����
	getRoomInfo(room_t)����ֵΪbool������Ϊroom_t�����á�
	����ɹ���ȡ��������Ϣ����������true�����ҽ������б����ṹ��room_t��
	room_t�ṹ����
	struct room_t {
		uint32_t roomId;     // ����id
		uint32_t existing;	 // ��������
		char roomName[40];	 // ������
		msg_t* everyOne;     // ÿ���˵���Ϣ
	};
	msg_t�ṹ����
	struct msg_t {
		char ip[20];		 // �û�ip
		char name[40];		 // �û��ǳ�
		size_t msgLen;		 // ���ڱ�������û�����ó�Ա������Ϣ
		m_time_t time;		 // �û����뷿���ʱ�䣬Ϊ1970��1��1������ʱ�侭���ĺ�����
		char *msgContent;	 // ���ڱ�������û�����ó�Ա������Ϣ
	};
	������(queryRoom)�ṩ�˶�ȡ������ϸ��Ϣ��˼·�ο�
	********************************/
	showRoom(_client);

	printf("������Ҫ��ѯ�ķ���id\n");
	uint32_t a;
	std::cin >> a;
	room_t r;
	if (!_client.getRoomInfo(a, r)) {
		printf("��ȡ�б�ʧ��\n");
		return;
	}
	printf("������:%s\t����id:%u\t��ǰ����:%u\n", r.roomName, r.roomId, r.existing);
	printf("\t�û��б�:\n");
	for (size_t j = 0; j < r.existing; ++j) {
		printf("\t  �û�%zu\t�ǳ�:%s\t����ʱ��:%llu\tip:%s\n", j + 1, r.everyOne[j].name, r.everyOne[j].time, r.everyOne[j].ip);
	}
}

void connectRoom(ClientHelper& _client) {
	/*******************************
	������ĳ������
	ͨ�������id�������ӣ�����idΪΨһ��ʶ����
	connectToRoom(uint32_t)Ϊ������ָ������ķ�����������ӷ���ɹ�����������true��
	connectToRoom(room_t&)Ϊ���ط���������Դ���һ��room_t�ṹ�������ӷ��䡣
	�������ͨ����ȡ�����б�rtl��Ȼ��connectToRoom(rtl.rooms[i])���������ӷ��䡣
	********************************/
	showRoom(_client);

	printf("������Ҫ����ķ���id\n");
	uint32_t a;
	std::cin >> a;
	if (!_client.connectToRoom(a)) {
		printf("����ʧ��\n");
		return;
	}
}

void hostRoom(ClientHelper& _client) {
	/*******************************
	�½�һ������
	����_client.hostNewRoom(const char*, uint32_t&)
	�½�һ��������Ϊ��һ�������ķ��䣬�����½��ķ���id����ڶ���������
	���½���������Զ�����뵽�÷����ڲ���Ϊ������
	һ�����˳����䣬����ᱻ���٣����е����Ӷ����뷿��Ͽ����ӡ�
	��������½��ɹ����򷵻�true��
	********************************/
	char namebuffer[40];
	printf("�����뷿����\n");
	std::cin >> namebuffer;
	uint32_t roomId;
	if (!_client.hostNewRoom(namebuffer, roomId)) {
		printf("��������ʧ�ܣ�\n");
		return;
	}
}

void goChat(ClientHelper& _client) {
	/*******************************
	����������
	��������ĵ���������ͨ�Ż��õ��ķ�����send��recv��
	��Ϣͨ���ṹ��msg_package_t���н��ա�
	checkRoomStatus()���ڼ��ͻ����Ƿ��ڷ����ڣ��������������뷿��ɹ���ú����᷵��true��
	recvMsg(msg_package_t&)���ڽ�����Ϣ�����û������Ϣ�������ú����᷵��false��
	���������Ϣ����������Ϣ����msg_package_t��
	�ṹ����
	struct msg_package_t {
		uint32_t latency;  // ���������͸���Ϣ������Ϣ��recvMsg()���ö�ȡ���ӳ�
		uint32_t msg_type; // ��Ϣ���ͣ�ͨ��recv���յ���Ϣ��Ϊ4
		uint32_t errorcode;// ������룬��Ϊ0��û������ָ���Ĵ��������Ϣ
		uint32_t msgNum;   // ��Ϣ����
		msg_t  *msgs;	   // ÿ����Ϣ����
		m_time_t recvTime; // recvMsg()���ö�ȡ��ʱ�䣬Ϊ1970��1��1������ʱ�侭���ĺ�����
	};
	msg_t�ṹ����
	struct msg_t {
		char ip[20];		 // �û�ip
		char name[40];		 // �û��ǳ�
		uint32_t msgLen;	 // �û�������Ϣ����Ϣ����
		m_time_t time;		 // �û����뷿���ʱ�䣬Ϊ1970��1��1������ʱ�侭���ĺ�����
		char *msgContent;	 // �û����͵���Ϣ����
	};
	sendMsg(const char*)�����򷿼䷢����Ϣ��������ͳɹ�������true��
	��������ע�⣡������
	�ڱ�����ͨ��ģ���У��������û�ͨ�ŵ���Ϣ����������ʾ
	�����򷿼䷢����Ϣ
							 +------------+
							 |   Server   |
							 +--^------+--+
								|	   |
		 +----------------------+	   +--------+----------------+---------------+
		 |										|		    	 |			  	 |
	+----+-------+						  +-----��------+   +-----��------+	 +---��--------+
	|    host    |						  |   user 1   |   |   user 2   |	 |   user 3   |
	+------------+						  +------------+   +------------+	 +------------+

	�û��򷿼䷢����Ϣ
							 +------------+
							 |   Server   |
							 +--+------^--+
								|	   |
		 +----------------------+	   +--------+--------------------------------+
		 |										|		                	  	 |
	+----��-------+						  +-----+------+   +------------+	 +---+--------+
	|    host    |						  |   user 1   |   |   user 2   |	 |   user 3   |
	+------------+						  +------------+   +------------+	 +------------+

	���ڱ�ģ���£��û�֮�䷢����Ϣ�ǿ������ģ�ֻ�з����ܿ��������û���������Ϣ��
	��������user1��user3���͵���Ϣhost�ܽ��յ�������user2����֪��user1��user3������ʲô��
	���������͵���Ϣ��ͬ�ڹ㲥�������û����ܽ��յ���������Ϣ��
	������Ҫʵ����������Ҫ����ʵ��һ��ת��������Ϣ�ķ�������
	********************************/
	msg_package_t m;
	char buffer[1024] = { 0 };
	INPUT_RECORD inRecArr[256] = { 0 };	 // ���뻺��������
	DWORD dRead;

	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	printf("����quit�����˳�\n");
	while (1) {
		if (!_client.checkRoomStatus()) {
			printf("���ڷ����ڣ�\n");
			break;
		}
		if (_client.recvMsg(m)) {
			printf("(����Ϣ)  ����ʱ��:%llu, ��Ϣ����:%u\n", m.recvTime, m.msgNum);
			for (uint32_t i = 0; i < m.msgNum; ++i) {
				printf("\t��Ϣ%u  ������:%s, ip:%s, ʱ��:%llu, ����:%s\n", i + 1, m.msgs[i]->name, m.msgs[i]->ip, m.msgs[i]->time, m.msgs[i]->msgContent);
			}
		}

		// �÷���Ϊ��������ȡstdin�ķ����������û�����/���̲����Ļ����������if�����
		// * windows ��ɫ
		if (WaitForSingleObject(h, 0) == WAIT_OBJECT_0) {
			std::cin.getline(buffer, 1024);
			if (strncmp(buffer, "quit", 4) == 0)break;
			if (!_client.sendMsg(buffer)) {
				printf("������Ϣʧ��\n");
			}
			else {
				printf("�ѷ���: %s\n", buffer);
			}
			ReadConsoleInputA(h, &inRecArr[0], 256, &dRead);
		}
		Sleep(50);
	}
}

void quitRoom(ClientHelper& _client) {
	/*******************************
	�˳�����
	����û�д��Σ�����˳�ʧ�ܣ�����false��
	********************************/
	if (!_client.disconnectFromRoom()) {
		printf("�˳�����ʧ��\n");
	}
}

int main() {
	ClientHelper client;
	char name[40];
	printf("�������ǳ�\n");
	std::cin >> name;

	/*******************************
	���ӷ�����
	�̶��ṩһ�����������������Ҫ���ص��ԣ���ʹ��127��ͷ�ĵ�ַ����ǰ����serv.exe
	ͨ�������������趨���ڷ������ڵ��ǳơ�
	�����ӳɹ�����������true��

	��ע�⣡������������������ֱ�����ӳɹ���

	��ע�⣡ �����������ʧ�� ��ʱ�ȣ��ǵõ���һ��client.clearSend() ������������
	********************************/
	client.connectToServer("127.0.0.1", 10001, name);
	//client.connectToServer("111.231.112.136", 10001, name);

	int flag = 1;
	while (flag) {
		printf("\t\t\t��ѡ��ָ��\n");
		printf("\t1.\t�鿴���з���\n");
		printf("\t2.\t��ѯ������Ϣ\n");
		printf("\t3.\t����������\n");
		printf("\t4.\t�½�һ������\n");
		printf("\t5.\t����������\n");
		printf("\t6.\t�˳�����\n");
		printf("\t7.\t�˳�����\n");

		int a;
		std::cin >> a;

		switch (a) {
		case 1:
			showRoom(client);
			break;
		case 2:
			queryRoom(client);
			break;
		case 3:
			connectRoom(client);
			break;
		case 4:
			hostRoom(client);
			break;
		case 5:
			goChat(client);
			break;
		case 6:
			quitRoom(client);
			break;
		case 7:
			flag = 0;
			break;
		}
	}
	return 0;
}