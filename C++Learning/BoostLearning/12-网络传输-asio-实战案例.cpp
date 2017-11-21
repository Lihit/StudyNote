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

/**
 * udp客户端测试
 */
void main1() {
    try {
        boost::asio::io_service service; // #1

        //这是在本地做的测试
        /*udp::resolver resolver(service); // #2
        udp::resolver::query query(udp::v4(), "localhost", "8868"); // #3
        udp::endpoint receiverEndpoint = *resolver.resolve(query); // #4
        udp::socket socket(service, udp::v4());// #5*/

        udp::socket socket(service);
        socket.open(udp::v4()); // #5
        udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("10.108.204.85"), 8080);
        char buf[512];
        for (;;) {
            memset(buf, 0, 512);
            cin.getline(buf, 512);
            socket.send_to(boost::asio::buffer(buf, strlen(buf)),
                           receiverEndpoint); // #6
            memset(buf, 0, 512);
            socket.receive_from(boost::asio::buffer(buf), receiverEndpoint); // #8
            cout << buf << endl;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * udp服务器
 */
void main2(){
    try {
        boost::asio::io_service service; // #1
        udp::socket socket(service, udp::endpoint(udp::v4(), 52792)); //#2

        char buf[512];
        for (;;) {
            memset(buf, 0, 512);
            udp::endpoint remoteEndpoint; // #3
            boost::system::error_code error;
            size_t len = socket.receive_from(boost::asio::buffer(buf),
                                             remoteEndpoint, 0, error);//#4
            cout<<buf<<endl;
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
 * tcp同步客户端
 */
void main3() {
    try {
        // 1, 创建io_service对象
        boost::asio::io_service io_service;
        tcp::socket socket(io_service);
        // 6, socket对象发起到服务器端的同步连接操作
        boost::system::error_code error = boost::asio::error::host_not_found;
        tcp::endpoint tcpServerAddress(boost::asio::ip::address::from_string("10.108.204.85"),8080);
        socket.connect(tcpServerAddress,error);
        // 7, 一系列 同步read()和write()
        cout<<"请输入要发送的数据：";
        string selection;
        cin >> selection;
        socket.send(boost::asio::buffer(selection, selection.size()), 0, error);
        // receive response from server
        char buf[512];
        int len = socket.read_some(boost::asio::buffer(buf), error);
        buf[len] = '\0';
        cout << buf;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * 多线程tcp 同步服务器
 */
typedef boost::shared_ptr<tcp::socket> SocketPtr;

void handleIo(SocketPtr socket) {
    char message[]="hello world!";
    boost::system::error_code ignored_error;
    boost::asio::write(*socket, boost::asio::buffer(message),
                       boost::asio::transfer_all(), ignored_error);

    // 2, receive selection from client
    char selection[120];
    size_t n = socket->read_some(boost::asio::buffer(selection), ignored_error);
    // 3, send response
    selection[n]='\0';
    cout<<selection<<endl;
    string response="Do not response!";
    boost::asio::write(*socket, boost::asio::buffer(response),
                       boost::asio::transfer_all(), ignored_error);

    socket->close();//主动关闭socket
}

void main4() {
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
int main_test12_1(){
    main4();
    return 0;
}