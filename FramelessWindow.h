#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class FramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Thickness
    {
        Thickness(int left, int right, int top, int bottom)
            : left(left)
            , right(right)
            , top(top)
            , bottom(bottom)
        {}
        Thickness(int thickness)
            : left(thickness)
            , right(thickness)
            , top(thickness)
            , bottom(thickness)
        {}
        int left, right, top, bottom;
    };

public:
    FramelessWindow(QWidget *parent = nullptr);
    ~FramelessWindow();

    /**
     * @brief Sets the thickness of the resize border
     * @param thickness
     */
    void setResizeThickness(const Thickness &thickness);

    /**
     * @brief Gets the thickness of the resized border
     */
    Thickness resizeThickness();

public slots:

    /**
     * @brief When the mouse is pressed, drag the window.
     * (Note: You need to make sure that when calling this function, the left mouse button is pressed)
     */
    void dragMove();

protected:

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
#elif (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#endif

private:
    Thickness m_resizeThickness;
};
#endif // FRAMELESSWINDOW_H
