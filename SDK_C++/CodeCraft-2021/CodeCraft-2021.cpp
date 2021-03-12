#include "iostream"
#include<istream>
#include<fstream>
#include<string>
#include<sstream>


using namespace std;


streamoff read_line(ifstream&, string&, streamoff);
void Serv_info(istringstream& out);
void VirM_info(istringstream& out);
void Request_info(istringstream& out);
streamoff Day_task(ifstream& line, streamoff start, int date);

int main()
{
	// TODO:read standard input
	// TODO:process
	// TODO:write standard output
	// TODO:fflush(stdout);

	//open file
	//用于读取数据的流
	ifstream reader("/home/zhouzhou/Desktop/HuaWei/training-data/training-1.txtiv");

	/*****************************************************************************

	这段代码用于读取可采购服务器的数量，以及对可采购服务器的信息的解析

	******************************************************************************/



	//读取可采购服务器种类数目
	string temp;
	streamoff now = read_line(reader, temp, ifstream::beg);
	cout << temp << endl;

	//依次读取每台的服务器的信息，并解析信息的格式
	int n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		now = read_line(reader, temp, now);
		cout << temp << endl;
		istringstream out(temp);
		Serv_info(out);
	}

	/*****************************************************************************

	这段代码用于读取可售卖虚拟机的数量，以及对可售卖虚拟机的信息的解析

	******************************************************************************/


	//读取可售卖的虚拟机的数目
	now = read_line(reader, temp, now);
	cout << temp << endl;

	//依次读取每台的虚拟机的信息，并解析信息的格式	
	n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		now = read_line(reader, temp, now);
		cout << temp << endl;
		istringstream out(temp);
		VirM_info(out);

	}

	/*****************************************************************************

	这段代码用于读取天数，以及对每天的数据序列的一个解析

	******************************************************************************/


	now = read_line(reader, temp, now);
	cout << temp << endl;

	//依次读取每天的序列，并解析序列的格式	
	n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		now = Day_task(reader, now, i);

	}



	return 0;
}

//每次读取文件的一行，并返回下一行的文件游标；
streamoff read_line(ifstream& line, string& str, streamoff start)
{
	if (!line.is_open())
		line.open("/home/zhouzhou/Desktop/HuaWei/training-data/training-1.txtiv", ifstream::in);
	//如果读取文件失败

	if (!line)
	{
		perror("open file error!");
		exit(1);
	}
	//定位文件读取位置
	line.seekg(start);
	getline(line, str);//读取文件test.txt的一行到temp
	streamoff ret = line.tellg();
	line.close();
	return ret;
}

//服务器信息解析函数
void Serv_info(istringstream& out)
{
	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	cout << "服务器型号：" << str << endl;
	out >> str;
	//str.pop_back();
	cout << "服务器CPU核数：" << atoi(str.c_str()) << endl;
	out >> str;
	//str.pop_back();
	cout << "服务器内存：" << atoi(str.c_str()) << "GB" << endl;
	out >> str;
	//str.pop_back();
	cout << "服务器硬件成本：" << atoi(str.c_str()) << endl;
	out >> str;
	//str.pop_back();
	cout << "服务器日能耗：" << atoi(str.c_str()) << endl;

}

//虚拟机信息解析函数
void VirM_info(istringstream& out)
{
	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	cout << "虚拟机型号：" << str << endl;
	out >> str;
	//str.pop_back();
	cout << "虚拟机CPU核数：" << atoi(str.c_str()) << endl;
	out >> str;
	//str.pop_back();
	cout << "虚拟机内存：" << atoi(str.c_str()) << "GB" << endl;
	out >> str;
	if (atoi(str.c_str())) {
		str = "双节点";
	}
	else {
		str = "单节点";
	}
	cout << "节点部署方式：" << str << endl;
}


//该函数用于解析一条请求序列的信息
void Request_info(istringstream& out)
{
	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	if (str == "add") {
		cout << "请求添加虚拟机" << "  ";
		out >> str;
		str.pop_back();
		cout << "型号：" << str << "  ";
		out >> str;
		//str.pop_back();
		cout << "ID：" << atoi(str.c_str()) << endl;
	}
	else if (str == "del") {
		cout << "请求删除虚拟机" << "  ";
		out >> str;
		//str.pop_back();
		cout << "ID：" << atoi(str.c_str()) << endl;
	}
}



//该函数用于读取一天序列，并对每一条信息进行解析；
streamoff Day_task(ifstream& line, streamoff start, int date)
{
	//判断文件是否打开，若未打开则打开
	if (!line.is_open())
		line.open("/home/zhouzhou/Desktop/HuaWei/training-data/training-1.txtiv", ifstream::in);

	//如果读取文件失败
	if (!line)
	{
		perror("open file error!");
		exit(1);
	}
	string str;
	start = read_line(line, str, start);
	cout << "第" << date + 1 << "天一共有" << str << "条请求序列" << endl;

	//读取第date天的所有序列，并做解析
	int n = atoi(str.c_str());
	for (int i = 0; i < n; i++) {

		start = read_line(line, str, start);
		cout << str << endl;
		istringstream out(str);
		Request_info(out);
	}

	return start;
}
