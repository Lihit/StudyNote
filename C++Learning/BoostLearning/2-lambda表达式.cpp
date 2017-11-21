#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/lambda/bind.hpp>
#include <string>
#include <map>
#include <algorithm>
/**
 * 第一个表达式看起来很奇特，你可以在脑子里按着括号来划分这个表达式；
 * 第一部分就是一个 lambda 表达式，它的意思基本上是说，"打印这些参数到
 * std::cout, 但不是立即就做，因为我还不知道这三个参数"。
 * 表达式的第二部分才是真正调用这个函数，它说，"嘿！这里有你要的三个参数"。
 * 我们再来看看这个表达式的第一部分。
 * std::cout << _1 << " " << _3 << " " << _2 << "!\n"
 * 你会注意到表达式中有三个占位符，命名为 _1, _2, 和 _3 。
 * 这些占位符为 lambda 表达式指出了延后的参数。注意，
 * 跟许多函数式编程语言的语法不一样，创建 lambda 表达式时没有关键字或名字；
 * 占位符的出现表明了这是一个 lambda 表达式。所以，这是一个接受三个参数的
 * lambda 表达式，参数的类型可以是任何支持 operator<< 流操作的类型。
 * 参数按 1-3-2 的顺序打印到 cout 。在这个例子中，我们把这个表达式用括号括
 * 起来，然后调用得到的这个函数对象，传递三个参数给它："Hello", "friend",
 * 和 "my".
 */
void main21() {
    using namespace boost::lambda;
    (std::cout << _1 << " " << _2 << " " << _3 << "\n")("hello", "world", "!");
    boost::function<void(int, int, int)> f =
            std::cout << _1 << "*" << _2 << "+" << _3
                      << "=" << _1 * _2 + _3 << "\n";
    f(1, 2, 4);
    f(11, 22, 33);
}

/*void main22() {
    using namespace boost::lambda;
    typedef std::map<int,std::string> type;
    type keys_and_values;
    keys_and_values[3]="Less than pi";
    keys_and_values[42]="You tell me";
    keys_and_values[0]="Nothing, if you ask me";
    std::cout << "What's wrong with the following expression?\n";
    std::for_each(
            keys_and_values.begin(),
            keys_and_values.end(),
            std::cout << "key=" <<
                      bind(&type::value_type::first,_1) << ", value="
                      << bind(&type::value_type::second,_1) << '\n');
    std::cout << "\n...and why does this work as expected?\n";
    std::for_each(
            keys_and_values.begin(),
            keys_and_values.end(),
            std::cout << constant("key=") <<
                      bind(&type::value_type::first,_1) << ", value="
                      << bind(&type::value_type::second,_1) << '\n');
    std::cout << '\n';
    // Print the size and max_size of the container
    (std::cout << "keys_and_values.size()=" <<
               bind(&type::size,_1) << "\nkeys_and_values.max_size()="
               << bind(&type::max_size,_1))(keys_and_values);

}*/


int main() {
    main21();
    return 0;
}

/*lambda库通过创建一个匿名的lambda表达式来代替实名的函数对象，大大简化了标准库的语法。下面我们来看一个hello world级的lambda表达式：
(cout << _1 << " " << _3 << " " << _2)("Welcome"," cnblog ","to");
其中，_1、_2和_3称为占位符，用以表示第几个参数。
在“Boost库之bind的使用”一文中，我们用bind实现了找出一个整数容器中大于5但小于10的元素的个数，现在我们尝试用lambda来完成这项工作。
int nCount = count_if(vctTemp.begin(), vctTemp.end(), _1>5 && _1<10);
可以看到，相对于使用bind进行函数对象的绑定，使用lambda使得语法更显简洁，逻辑也更觉清晰。
在lambda表达式中，还有一个非常重要的概念就是常量和变量的延迟，举例如下：
for_each(vctTemp.begin(),vctTemp.end(), cout << ' ' << _1);
该函数的本意是想在输出每一元素前都加一个空格，但由于cout << ' '不是一个lambda表达式，因此，它会被立即输出求值。
 为了实现延迟输出的目的，我们需要使用constant函数，以创建一个lambda仿函数。
for_each(vctTemp.begin(),vctTemp.end(), cout << constant(' ') << _1);
以上是常量延迟调用的例子，下面来看一下变量的延迟调用。
int nIndex = 0;
for_each(vctTemp.begin(),vctTemp.end(), cout << ++nIndex << _1<
        同理，由于cout << ++nIndex不是一个lambda表达式，
只会被求值一次。为了在每次调用时都能输出序号，需要使用var函数，以创建一个lambda仿函数。
for_each(vctTemp.begin(),vctTemp.end(), cout << ++var(nIndex) << _1<另外，还可以将一个lambda表达式赋给一个function，从而实现延迟调用。
function fAdd = cout << _1 << "+" << _2 << "=" <<_1+_2 << endl;
fAdd (1,2);
fAdd (3,4);
以上介绍了lambda库的一些基本功能。lambda库的更强大之处在于，它提供了一些用于控制结构的函数模板，
 比如：if_then、if_then_else、if_then_else_return、while_loop、do_while_loop、for_loop、switch_statement等。下面
        if_then_else为例，介绍其用法。
for_each(vctTemp.begin(),vctTemp.end(),if_then_else(_1%2==0,cout<<_1<< '\n',cout<*/