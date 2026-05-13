#include <iostream>
#include <functional>   // 函数发生器头文件

// 自由函数
void test_free_fun(const std::string &file_name)
{
    std::cout << "自由函数" << file_name << std::endl;
}

// 成员函数
class FileSave
{
private:
    /* data */
public:
    FileSave(/* args */) = default;
    ~FileSave() = default;
    void test_member_fun(const std::string &file_name)
    {
        std::cout << "成员方法" << file_name << std::endl;
    };

};


int main()
{
    FileSave file_save;

    // Lambda函数
    auto test_lambda_fun = [](const std::string &file_name) -> void
    {
        std::cout << "lambda函数:" << file_name << std::endl;
    };

    test_free_fun("file.txt");
    file_save.test_member_fun("file.txt");
    test_lambda_fun("file.txt");

    std::function<void(const std::string)> fun1 = test_free_fun;
    std::function<void(const std::string)> fun2 = test_lambda_fun;
    // 成员函数，绑定放入函数包装器
    std::function<void(const std::string)> fun3 = std::bind(&FileSave::test_member_fun, 
                                                    &file_save, std::placeholders::_1);
                                                    
    fun1("file.txt");
    fun2("file.txt");
    fun3("file.txt");

    return 0;
}