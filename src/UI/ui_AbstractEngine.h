

class ui_AbstractEngine
{
private:
    /* data */
public:
    ui_AbstractEngine() = default;
    ~ui_AbstractEngine() = default;

    virtual bool setupUi(ui_AbstractEngine* parent = nullptr) = 0;
};

