/**
 * When the model hits an unrecoverable error (such as invalid input params)
 * it reports the error and then immediately exist the application.
 *
 * Whilst this is correct behaviour when running the model for real - this
 * stop us from creating unit tests that check this validation.
 *
 * To work around this in we replace the error.cpp implementation with our own
 * at link time.
 */
#include <Error.h>
#include <cstdarg>
#include <sstream>

class CriticalError: public std::exception {
public:
    CriticalError(std::string msg): msg(std::move(msg)) {}
    const char* what() const noexcept  override { return msg.c_str();}
private:
    std::string msg;
};

void ErrorCritical(const char* fmt, const char* file, int line, ...)
{
    va_list args;
    va_start(args, line);

    constexpr size_t maxErrLen = 1024*2;
    char errMsgBuf[maxErrLen] = "";
    std::vsnprintf(errMsgBuf, maxErrLen, fmt, args);

    va_end(args);

    std::stringstream buf;
    buf << "[" << file << " " << line << "] " << errMsgBuf << std::endl;

    throw CriticalError(buf.str());
}
