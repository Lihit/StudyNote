#include <iostream>
#include <ctime>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <algorithm>
#include <functional>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using namespace std;

/*
 * 时间转为字符串
 */
string make_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}

/**
 * tcp同步服务器，显示服务器时间
 */
void main1() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));
        while (true) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            string message = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }
}

/**
 * tcp同步服务器，提供多种选择
 */
const char serviceList[] =
        "         Services          \n"
                "**************************\n"
                "[1] Get current time.     \n"
                "[2] Who's online.         \n"
                "[3] Get system info.      \n"
                "**************************\n"
                "Please pick a service[1-3]: ";

void getResult(const string &cmdPrefix, const char *outputFile, string &res) {
    string cmd(cmdPrefix + outputFile);
    system(cmd.c_str());

    ifstream fin;
    fin.open(outputFile);
    if (fin) {
        ostringstream os;
        os << fin.rdbuf();
        res = os.str();
    }
    if (fin.is_open()) {
        fin.close();
    }
}

string getServiceContent(const int &select) {
    string res;
    switch (select) {
        case 1: {
            time_t now = time(0);
            res = ctime(&now);
            break;
        }

        case 2:
            getResult("w > ", "who", res);
            break;
        case 3:
            getResult("uname -a > ", "uname", res);
            break;
        default:
            res = "Sorry,No such service!";
            break;
    }
    return res;
}

void main2() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8868));
        while (1) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(serviceList), ignored_error);

            char selection[20];
            size_t n = socket.read_some(boost::asio::buffer(selection), ignored_error);
            string response = getServiceContent(atoi(selection));
            boost::asio::write(socket, boost::asio::buffer(response), boost::asio::transfer_all(), ignored_error);
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

/**
 * 多线程tcp 同步服务器
 */
typedef boost::shared_ptr<tcp::socket> SocketPtr;

void handleIo(SocketPtr socket) {
    boost::system::error_code ignored_error;
    boost::asio::write(*socket, boost::asio::buffer(serviceList),
                       boost::asio::transfer_all(), ignored_error);

    // 2, receive selection from client
    char selection[20];
    size_t n = socket->read_some(boost::asio::buffer(selection), ignored_error);
    // 3, send response
    string response = getServiceContent(atoi(selection));
    boost::asio::write(*socket, boost::asio::buffer(response),
                       boost::asio::transfer_all(), ignored_error);

    socket->close();//主动关闭socket
}

void main3() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8868));
        boost::thread_group grp;
        while (1) {
            SocketPtr socket(new tcp::socket(io_service));
            acceptor.accept(*socket);
            grp.create_thread(boost::bind(handleIo, socket));
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

/**
 * tcp同步客户端
 */
void main4() {
    try {
        // 1, 创建io_service对象
        boost::asio::io_service io_service;

        // 2, 创建resolver对象关联到io_service对象
        tcp::resolver resolver(io_service);

        // 3, 创建一个查询对象
        tcp::resolver::query query("localhost", "8868");

        // 4, 用resolver对象和查询对象获取可用服务器地址
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        // 5, 创建tcp::socket对象，关联到io_service
        tcp::socket socket(io_service);
        // 6, socket对象发起到服务器端的同步连接操作
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end) {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error) // 如果没有一个地址能连接成功，则抛出异常
            throw boost::system::system_error(error);

        // 7, 一系列 同步read()和write()
        char buf[512];
        // receive service list from server
        //        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        //        size_t len = socket.receive(boost::asio::buffer(buf), 0, error);
        size_t len = boost::asio::read(socket, boost::asio::buffer(buf),
                                       boost::asio::transfer_at_least(1), error);
        buf[len] = '\0';
        cout << buf;

        string selection;
        cin >> selection;
        // send selection to server
        //        boost::asio::write(socket, boost::asio::buffer(selection),
        //                boost::asio::transfer_all(), error);

        //        socket.write_some(boost::asio::buffer(selection,selection.size()), error);
        socket.send(boost::asio::buffer(selection, selection.size()), 0, error);
        // receive response from server
        len = socket.read_some(boost::asio::buffer(buf), error);
        buf[len] = '\0';
        cout << buf;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * boost域名地址解析
 */
void main5() {
    // 1, 创建io_service对象
    boost::asio::io_service io_service;

    // 2, 创建resolver对象关联到io_service对象
    tcp::resolver resolver(io_service);

    for (;;) {
        try {
            string host, port;
            cin >> host >> port;
            // 3, 创建一个查询对象
            tcp::resolver::query query(host, port);

            // 4, 用resolver对象和查询对象获取可用服务器地址
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            tcp::resolver::iterator end;

            // 5, 创建tcp::socket对象，关联到io_service
            tcp::socket socket(io_service);
            // 6, socket对象发起到服务器端的同步连接操作
            boost::system::error_code error =
                    boost::asio::error::host_not_found;
            while (endpoint_iterator != end) {
                cout << endpoint_iterator->endpoint() << endl;
                socket.close();
                socket.connect(*endpoint_iterator++, error);
            }
            if (error) // 如果没有一个地址能连接成功，则抛出异常
                throw boost::system::system_error(error);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

}

/**
 * udp同步服务器
 */
void main6(){
    try {
        boost::asio::io_service service; // #1
        udp::socket socket(service, udp::endpoint(udp::v4(), 8868)); //#2

        char buf[512];
        for (;;) {
            memset(buf, 0, 512);
            udp::endpoint remoteEndpoint; // #3
            boost::system::error_code error;
            size_t len = socket.receive_from(boost::asio::buffer(buf),
                                             remoteEndpoint, 0, error);//#4
            if (error && error != boost::asio::error::message_size)
                throw boost::system::system_error(error);

            boost::system::error_code ignoredError;
            socket.send_to(boost::asio::buffer(buf, len), remoteEndpoint, 0,
                           ignoredError); // #5
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * udp同步客户端
 */
void main7(){
    try {
        boost::asio::io_service service; // #1

        udp::resolver resolver(service); // #2
        udp::resolver::query query(udp::v4(), "localhost", "8868"); // #3
        udp::endpoint receiverEndpoint = *resolver.resolve(query); // #4

        //        udp::socket socket(service);
        //        socket.open(udp::v4()); // #5

        //        udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("192.168.0.101"), 51179);

        udp::socket socket(service, udp::v4());// #5
        char buf[512];
        for (;;) {
            memset(buf, 0, 512);
            cin.getline(buf, 512);
            socket.send_to(boost::asio::buffer(buf, strlen(buf)),
                           receiverEndpoint); // #6
            memset(buf, 0, 512);
            udp::endpoint senderEndpoint; // #7
            socket.receive_from(boost::asio::buffer(buf), senderEndpoint); // #8
            cout << buf << endl;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
int main_test12() {
    int a[]={11,2,31,12,33};
    return 0;
}