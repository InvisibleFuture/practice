#include <windows.h>

//窗口过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wc;                              //定义窗口类结构体变量F
    static TCHAR *szAppName = TEXT("zixue7"); //窗口类名称
    HWND hwnd = NULL;                         //窗口句柄
    MSG msg;                                  //消息结构

    /**
        下面的代码填充窗口类信息，如图标，鼠标样式，背景，过程函数等
    */
    wc.style = CS_HREDRAW | CS_VREDRAW;              //窗口样式
    wc.lpfnWndProc = WndProc;                        //过程函数
    wc.cbClsExtra = 0;                               //扩展字段
    wc.cbWndExtra = 0;                               //扩展字段
    wc.hInstance = hInstance;                        //当前实例句柄
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION); //设置程序图标
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);        //设置鼠标

    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //用白色画刷填充背景
    wc.lpszMenuName = NULL;                                 //菜单
    wc.lpszClassName = szAppName;                           //类名

    //向操作系统注册窗口类
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("程序只能在windowsNT下运行"), szAppName, MB_ICONERROR);
        return 0;
    }

    //创建窗口
    hwnd = CreateWindow(szAppName,                   //要注册的窗口类名
                        TEXT("c语言编写的窗口程序"), //窗口标题
                        WS_OVERLAPPEDWINDOW,         //窗口样式
                        CW_USEDEFAULT,               //窗口距离屏幕左上角都横坐标
                        CW_USEDEFAULT,               //窗口距离屏幕左上角都纵坐标
                        400,                         //窗口宽度
                        300,                         //窗口高度
                        NULL,                        //父窗口句柄
                        NULL,                        //菜单句柄
                        hInstance,                   //当前实例句柄
                        NULL);                       //指向一个值的指针，该值传递给窗口 WM_CREATE消息。一般为NULL

    //窗口全屏
    LONG style = GetWindowLong(hwnd, GWL_STYLE);                    //获得窗口风格
    style = WS_CAPTION || WS_SIZEBOX;                               //窗口全屏显示且不可改变大小
    SetWindowLong(hwnd, GWL_STYLE, style);                          //设置窗口风格
    int screenX = GetSystemMetrics(SM_CXSCREEN);                    //获取整个屏幕右下角X坐标
    int screenY = GetSystemMetrics(SM_CYSCREEN);                    //屏幕Y坐标
    SetWindowPos(hwnd, NULL, 0, 0, screenX, screenY, SWP_NOZORDER); //改变窗口位置、尺寸和Z序
    //ShowCursor(FALSE);                                            //显示时隐藏鼠标

    //显示窗口
    ShowWindow(hwnd, iCmdShow);

    //更新窗口
    UpdateWindow(hwnd);

    //消息循环，一直停在这里，退出消息循环就表示程序结束了
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); //翻译消息
        DispatchMessage(&msg);  //分发消息
    }

    return msg.wParam;
}

/**
消息处理函数
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);      // 1
        Rectangle(hdc, 50, 50, 200, 200); // 2
        EndPaint(hwnd, &ps);              // 3
        break;
    case WM_DESTROY:
        //发送结束请求，里面的参数为退出码
        PostQuitMessage(0);
        break;
    }

    //调用默认的过程函数
    return DefWindowProc(hwnd, message, wParam, lParam);
}