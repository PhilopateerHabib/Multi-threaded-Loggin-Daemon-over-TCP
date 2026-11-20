#pragma once
enum SuccessState
{
    SUCCESS,
    FAILURE
};
enum LogLevel
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};
struct Message
{
    char msg[100];
    LogLevel log_level;
};