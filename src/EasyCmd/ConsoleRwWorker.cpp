#include "ConsoleRwWorker.h"
#include <Windows.h>
#include <QDebug>
#include <QThread>

#pragma comment(lib, "User32.lib")

ConsoleRwWorker::ConsoleRwWorker()
{
    connect(&m_cmd_process, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    // 初始化并启动cmd.exe进程
    m_cmd_process.setProgram("cmd.exe");
    m_cmd_process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());

    /*将标准输出和标准错误输出合并在一起输出，防止遗漏输出内容*/
    m_cmd_process.setProcessChannelMode(QProcess::MergedChannels);
    m_cmd_process.start();
    bool ok = m_cmd_process.waitForStarted(2000);
    Q_ASSERT(ok);
}

ConsoleRwWorker::~ConsoleRwWorker()
{
    // 等待进程退出
    m_cmd_process.kill();
    m_cmd_process.waitForFinished(10000);
}

void ConsoleRwWorker::ctrlBreak()
{
    // 进程运行才做操作
    if (m_cmd_process.state() == QProcess::NotRunning) return;

    // 下面的代码参考https://blog.csdn.net/binzhongbi757/article/details/50698486/
    qint64 PID = m_cmd_process.processId();
    AttachConsole(PID); // attach to process console
    SetConsoleCtrlHandler(NULL, TRUE); // disable Control+C handling for our app
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0); // generate Control+C event

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
    if (INVALID_HANDLE_VALUE == hProcess)
    {
        return ;
    }
    WaitForSingleObject(hProcess, INFINITE);
    CloseHandle(hProcess);
    Sleep(500); //等待，以防止自身被关闭。

    FreeConsole();
    SetConsoleCtrlHandler(NULL, FALSE);
}

void ConsoleRwWorker::slotWrite(QString input)
{
    QByteArray ba = input.toLocal8Bit();
    m_cmd_process.write(ba.data(), ba.size());
}

void ConsoleRwWorker::slotReadyRead()
{
    QString output = QString::fromLocal8Bit(m_cmd_process.readAll());
    if (!output.isEmpty())
    {
        // 发出通知
        emit sigOutput(output);
    }
}
