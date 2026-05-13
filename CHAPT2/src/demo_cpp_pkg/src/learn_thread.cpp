#include <iostream>
#include <thread>   // 多线程
#include <chrono>   // 时间相关
#include <functional> // 函数包装器
#include "cpp-httplib/httplib.h"  // 下载相关头文件

class Download
{
    private:
        /* data */
    public:
        void download(const std::string &host, const std::string &path, const std::function
        <void(const std::string &, const std::string &)> &callback_test)
        {
            std::cout << "thread" << std::this_thread::get_id() << std::endl;
            httplib::Client client(host);
            auto response = client.Get(path);
            if(response && response -> status==200)
            {
                callback_test(path, response->body);
            }
        };

        // 调用download
        void start_download(const std::string &host, const std::string &path, const std::function
        <void(const std::string &, const std::string &)> &callback_test)
        {
            auto download_fun = std::bind(&Download::download, this, std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3);
            std::thread thread(download_fun, host, path, callback_test);
            thread.detach();        // 子线程独立出去，在后台独立运行
        };
};

int main()
{
    auto d = Download();    // 创建对象

    // 创建回调函数
    auto word_count = [](const std::string &path, const std::string &result) -> void{
        std::cout << "download finish" << path << ":" << result.length() << "->" 
        << result.substr(0, 5) << std::endl;
    };

    d.start_download("http://127.0.0.1:8000", "novel1.txt", word_count);
    d.start_download("http://127.0.0.1:8000", "novel2.txt", word_count);
    d.start_download("http://127.0.0.1:8000", "novel3.txt", word_count);

    // 主线程休眠1000ms*10=10s
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*10));
    return 0;

}
