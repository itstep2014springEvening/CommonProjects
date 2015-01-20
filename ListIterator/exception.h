#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace std
{
class exception
{
public:
    exception() noexcept;
    exception(const exception&) noexcept;
    exception &operator=(const exception&) noexcept;
    virtual ~exception() noexcept;

    virtual const char *what() const noexcept;
};
}
#endif // EXCEPTION_H
