#include "Client.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace NetworkHelper;

void showRoom(ClientHelper& _client) {
	/*******************************
	展示房间列表
	getRoomList(room_list_t)返回值为bool，传参为room_list_t的引用。
	如果成功获取到房间信息，函数返回true，并且将房间列表存入结构体room_list_t。
	room_list_t结构如下
	struct room_list_t {
		uint32_t roomNum;   // 当前存在的房间数量
		room_t *rooms;    // 每个房间的信息
	};
	room_t结构如下
	struct room_t {
		uint32_t roomId;     // 房间id
		uint32_t existing;	 // 已有人数
		char roomName[40];	 // 房间名
		msg_t* everyOne;     // 对于本函数，没有存入该成员
	};
	本方法(showRoom)提供了读取房间信息的思路参考
	********************************/
	room_list_t rlt;
	if (!_client.getRoomList(rlt)) {
		printf("获取列表失败\n");
		return;
	}
	printf("房间数量:\t%u\n----列表如下----\n", rlt.roomNum);
	for (uint32_t i = 0; i < rlt.roomNum; ++i) {
		printf("房间%u:\n", i + 1);
		printf("房间名:%s\t房间id:%u\t当前人数:%u\n", rlt.rooms[i].roomName, rlt.rooms[i].roomId, rlt.rooms[i].existing);
	}
}

void queryRoom(ClientHelper& _client) {
	/*******************************
	查询房间
	getRoomInfo(room_t)返回值为bool，传参为room_t的引用。
	如果成功获取到房间信息，函数返回true，并且将房间列表存入结构体room_t。
	room_t结构如下
	struct room_t {
		uint32_t roomId;     // 房间id
		uint32_t existing;	 // 已有人数
		char roomName[40];	 // 房间名
		msg_t* everyOne;     // 每个人的信息
	};
	msg_t结构如下
	struct msg_t {
		char ip[20];		 // 用户ip
		char name[40];		 // 用户昵称
		size_t msgLen;		 // 对于本函数，没有往该成员填入信息
		m_time_t time;		 // 用户加入房间的时间，为1970年1月1日至该时间经历的毫秒数
		char *msgContent;	 // 对于本函数，没有往该成员填入信息
	};
	本方法(queryRoom)提供了读取房间详细信息的思路参考
	********************************/
	showRoom(_client);

	printf("请输入要查询的房间id\n");
	uint32_t a;
	std::cin >> a;
	room_t r;
	if (!_client.getRoomInfo(a, r)) {
		printf("获取列表失败\n");
		return;
	}
	printf("房间名:%s\t房间id:%u\t当前人数:%u\n", r.roomName, r.roomId, r.existing);
	printf("\t用户列表:\n");
	for (size_t j = 0; j < r.existing; ++j) {
		printf("\t  用户%zu\t昵称:%s\t加入时间:%llu\tip:%s\n", j + 1, r.everyOne[j].name, r.everyOne[j].time, r.everyOne[j].ip);
	}
}

void connectRoom(ClientHelper& _client) {
	/*******************************
	连接至某个房间
	通过房间的id进行连接，房间id为唯一标识符。
	connectToRoom(uint32_t)为连接至指定房间的方法，如果连接房间成功，函数返回true。
	connectToRoom(room_t&)为重载方法，你可以传入一个room_t结构体来连接房间。
	即你可以通过获取房间列表rtl，然后connectToRoom(rtl.rooms[i])来快速连接房间。
	********************************/
	showRoom(_client);

	printf("请输入要加入的房间id\n");
	uint32_t a;
	std::cin >> a;
	if (!_client.connectToRoom(a)) {
		printf("连接失败\n");
		return;
	}
}

void hostRoom(ClientHelper& _client) {
	/*******************************
	新建一个房间
	方法_client.hostNewRoom(const char*, uint32_t&)
	新建一个房间名为第一个参数的房间，并将新建的房间id存入第二个参数。
	当新建房间后，你自动会加入到该房间内并成为房主。
	一旦你退出房间，房间会被销毁，所有的连接都会与房间断开连接。
	如果房间新建成功，则返回true。
	********************************/
	char namebuffer[40];
	printf("请输入房间名\n");
	std::cin >> namebuffer;
	uint32_t roomId;
	if (!_client.hostNewRoom(namebuffer, roomId)) {
		printf("建立房间失败！\n");
		return;
	}
}

void goChat(ClientHelper& _client) {
	/*******************************
	进入聊天室
	介绍最核心的两个网络通信会用到的方法：send和recv。
	信息通过结构体msg_package_t进行接收。
	checkRoomStatus()用于检查客户端是否处于房间内，当建立房间或加入房间成功后该函数会返回true。
	recvMsg(msg_package_t&)用于接收信息，如果没有新信息到来，该函数会返回false。
	如果有新信息，函数将信息存入msg_package_t。
	结构如下
	struct msg_package_t {
		uint32_t latency;  // 服务器发送该信息到该信息被recvMsg()调用读取的延迟
		uint32_t msg_type; // 信息类型，通过recv接收的信息均为4
		uint32_t errorcode;// 错误代码，均为0，没有其他指代的错误代码信息
		uint32_t msgNum;   // 信息数量
		msg_t  *msgs;	   // 每个信息内容
		m_time_t recvTime; // recvMsg()调用读取的时间，为1970年1月1日至该时间经历的毫秒数
	};
	msg_t结构如下
	struct msg_t {
		char ip[20];		 // 用户ip
		char name[40];		 // 用户昵称
		uint32_t msgLen;	 // 用户发送信息的信息长度
		m_time_t time;		 // 用户加入房间的时间，为1970年1月1日至该时间经历的毫秒数
		char *msgContent;	 // 用户发送的信息内容
	};
	sendMsg(const char*)用于向房间发送信息，如果发送成功，返回true。
	！！！！注意！！！！
	在本网络通信模型中，房间内用户通信的信息流向如下所示
	房主向房间发送信息
							 +------------+
							 |   Server   |
							 +--^------+--+
								|	   |
		 +----------------------+	   +--------+----------------+---------------+
		 |										|		    	 |			  	 |
	+----+-------+						  +-----ˇ------+   +-----ˇ------+	 +---ˇ--------+
	|    host    |						  |   user 1   |   |   user 2   |	 |   user 3   |
	+------------+						  +------------+   +------------+	 +------------+

	用户向房间发送信息
							 +------------+
							 |   Server   |
							 +--+------^--+
								|	   |
		 +----------------------+	   +--------+--------------------------------+
		 |										|		                	  	 |
	+----ˇ-------+						  +-----+------+   +------------+	 +---+--------+
	|    host    |						  |   user 1   |   |   user 2   |	 |   user 3   |
	+------------+						  +------------+   +------------+	 +------------+

	即在本模型下，用户之间发送信息是看不到的，只有房主能看到所有用户发来的信息。
	如上例，user1和user3发送的信息host能接收到，但是user2并不知道user1和user3发送了什么。
	而房主发送的信息等同于广播，所有用户都能接收到房主的信息。
	故如需要实现聊天室需要另外实现一个转发所有信息的房主程序。
	********************************/
	msg_package_t m;
	char buffer[1024] = { 0 };
	INPUT_RECORD inRecArr[256] = { 0 };	 // 输入缓冲区数组
	DWORD dRead;

	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	printf("输入quit命令退出\n");
	while (1) {
		if (!_client.checkRoomStatus()) {
			printf("不在房间内！\n");
			break;
		}
		if (_client.recvMsg(m)) {
			printf("(新信息)  接收时间:%llu, 信息数量:%u\n", m.recvTime, m.msgNum);
			for (uint32_t i = 0; i < m.msgNum; ++i) {
				printf("\t信息%u  发送者:%s, ip:%s, 时间:%llu, 内容:%s\n", i + 1, m.msgs[i]->name, m.msgs[i]->ip, m.msgs[i]->time, m.msgs[i]->msgContent);
			}
		}

		// 该方法为非阻塞读取stdin的方法，即如果没有鼠标/键盘操作的话，不会进入if语句中
		// * windows 特色
		if (WaitForSingleObject(h, 0) == WAIT_OBJECT_0) {
			std::cin.getline(buffer, 1024);
			if (strncmp(buffer, "quit", 4) == 0)break;
			if (!_client.sendMsg(buffer)) {
				printf("发送信息失败\n");
			}
			else {
				printf("已发送: %s\n", buffer);
			}
			ReadConsoleInputA(h, &inRecArr[0], 256, &dRead);
		}
		Sleep(50);
	}
}

void quitRoom(ClientHelper& _client) {
	/*******************************
	退出房间
	函数没有传参，如果退出失败，返回false。
	********************************/
	if (!_client.disconnectFromRoom()) {
		printf("退出房间失败\n");
	}
}

int main() {
	ClientHelper client;
	char name[40];
	printf("请输入昵称\n");
	std::cin >> name;

	/*******************************
	连接服务器
	固定提供一个服务器，如果你需要本地调试，请使用127开头的地址并提前运行serv.exe
	通过第三个参数设定你在服务器内的昵称。
	若连接成功，函数返回true。

	！注意！：本函数会阻塞程序直至连接成功。

	另注意！ 如果发生请求失败 超时等，记得调用一次client.clearSend() 清除掉请求队列
	********************************/
	client.connectToServer("127.0.0.1", 10001, name);
	//client.connectToServer("111.231.112.136", 10001, name);

	int flag = 1;
	while (flag) {
		printf("\t\t\t请选择指令\n");
		printf("\t1.\t查看现有房间\n");
		printf("\t2.\t查询房间信息\n");
		printf("\t3.\t连接至房间\n");
		printf("\t4.\t新建一个房间\n");
		printf("\t5.\t进入聊天室\n");
		printf("\t6.\t退出房间\n");
		printf("\t7.\t退出程序\n");

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