


class AbstractApplication
{
public:
    AbstractApplication() = default;
    ~AbstractApplication() = default;

    virtual bool run() = 0;
};