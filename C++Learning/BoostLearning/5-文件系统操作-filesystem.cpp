#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

/**
 * path类的基本使用
 */
void main51(){
    //注意 /= 和 += 的区别， /= 表示追加下级目录， +=  仅仅是字符串的串接
    path dir("/home/wenshao/Downloads/");
    dir /= "Downloads";       //追加下级目录
    dir /= "test.txt";
    std::cout << dir << std::endl;
    std::cout << dir.string() << std::endl;            //转换成std::string 类型
    std::cout << dir.root_name()<< std::endl;          //盘符名：C:
    std::cout << dir.root_directory()<< std::endl;     //根目录："\"
    std::cout << dir.root_path()<< std::endl;          //根路径："C:\"
    std::cout << dir.relative_path()<< std::endl;      // 相对路径:Windows\System32\services.exe
    std::cout << dir.parent_path()<< std::endl;        //上级目录：C:\Windows\System32
    std::cout << dir.filename()<< std::endl;           //文件名：services.exe
    std::cout << dir.stem()<< std::endl;               //不带扩展的文件名：services
    std::cout << dir.extension()<< std::endl;          //扩展名：.exe
}

/*常用函数及异常处理
        函数名                                           作用

system_complete(path);           返回完整路径(相对路径+当前路径)
exists(path);                                目录是否存在
is_directory(path);
is_directory(file_status);            是否是路径
is_regular_file(path);
is_regular_file(file_status);             是否是普通文件
is_symlink(path);
is_symlink(file_status);                    是否是一个链接文件
file_status status(path);                  返回路径名对应的状态
initial_path();                                     得到程序运行时的系统当前路径
current_path();                                 得到系统当前路径
current_path(const Path& p);        改变当前路径
space_info space(const Path& p); 得到指定路径下的空间信息，space_info 有capacity, free 和 available三个成员变量，分别表示容量，剩余空间和可用空间。
last_write_time(const Path& p);    最后修改时间
last_write_time(const Path& p, const std::time_t new_time);  修改最后修改时间
bool create_directory(const Path& dp);                                      建立路径
create_hard_link(const Path1& to_p, const Path2& from_p);
error_code create_hard_link(const Path1& to_p, const Path2& from_p, error_code& ec); 建立硬链接
create_symlink(const Path1& to_p, const Path2& from_p);
create_symlink(const Path1& to_p, const Path2& from_p, error_code& ec);  建立软链接
remove(const Path& p, system::error_code & ec = singular );      删除文件
remove_all(const Path& p);                                                                   递归删除p中所有内容，返回删除文件的数量
rename(const Path1& from_p, const Path2& to_p);                         重命名
copy_file(const Path1& from_fp, const Path2& to_fp);                    拷贝文件
omplete(const Path& p, const Path& base=initial_path<Path>()); 以base以基，p作为相对路径，返回其完整路径
create_directories(const Path & p);        建立路径
 */

int main52(){
    //常用函数及异常
    try
    {
        path dir2("/home/wenshao/Downloads/");
        assert(is_directory(dir2));          //判断是否一个目录
        assert(exists(dir2));                //判断目录是否存在
    }
    catch(filesystem_error& e)
    {
        std::cout << e.path1() << std::endl;
        std::cout << e.what() << std::endl;
    }
}

/**
 * 目录迭代
 */
void main53(){
    path dir("/home/wenshao/Downloads/");
    directory_iterator end;
    for(directory_iterator pos(dir);pos!=end;pos++){
        cout<<*pos<<endl;
        path d1(*pos);
        string s=d1.string();
        cout<<s<<endl;
        string s2=pos->path().string();
        cout<<s2<<endl;

    }
}
int main_test5(){
    main53();
    return 0;
}