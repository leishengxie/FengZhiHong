#include <QObject>
#include <QColor>

class ColorMaker : public QObject
{
    Q_OBJECT
    Q_ENUMS(GenerateAlgorithm)     //声明一个枚举类型到qml里面用
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)        //声明一个属性，在QML里面用
    Q_PROPERTY(QColor timeColor READ timeColor)
	Q_PROPERTY(GenerateAlgorithm algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged) //add

public:
    ColorMaker(QObject *parent = 0);
    ~ColorMaker();

    enum GenerateAlgorithm{
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };

    QColor color() const;
    void setColor(const QColor & color);
    QColor timeColor() const;

//    Q_INVOKABLE GenerateAlgorithm algorithm() const;
//    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

	GenerateAlgorithm algorithm() const;
	void setAlgorithm(GenerateAlgorithm algorithm);

signals:
    void colorChanged(const QColor & color);
    void currentTime(const QString &strTime);
	void algorithmChanged(const GenerateAlgorithm &algorithm);

public slots:
    void start();
    void stop();
	void nextAlgorithm();

protected:
    void timerEvent(QTimerEvent *e);

private:
    GenerateAlgorithm m_algorithm;
    QColor m_currentColor;
    int m_nColorTimer;
};
