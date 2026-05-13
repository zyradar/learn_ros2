#include <iostream>     // 标准头文件，输入输出流
#include <memory>       // 指针相关

int main()
{
    // std::make_shared<数据类型/类>(参数);return（对应类的共享指针）
    auto p1 = std::make_shared<std::string>("this is a str");   // 共享指针
    std::cout << "p1引用计数:" << p1.use_count() << "指向内存" << p1.get() << std::endl;

    auto p2 = p1;
    std::cout << "p1引用计数:" << p1.use_count() << "指向内存" << p1.get() << std::endl;
    std::cout << "p2引用计数:" << p2.use_count() << "指向内存" << p1.get() << std::endl;

    p1.reset();         // 释放指针,释放引用，不指向"this is a str"所在内存
    std::cout << "p1引用计数:" << p1.use_count() << "指向内存" << p1.get() << std::endl;
    std::cout << "p2引用计数:" << p2.use_count() << "指向内存" << p1.get() << std::endl;

    std::cout << "p2指向内存地址数据" << p2->c_str() << std::endl;
    
    return 0;
}