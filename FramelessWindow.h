#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FramelessWindow;
}
QT_END_NAMESPACE

class FramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Thickness
    {
        Thickness(int left = 5, int right = 5, int top = 5, int bottom = 5)
            : left(left)
            , right(right)
            , top(top)
            , bottom(bottom)
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

    /**
     * @brief When the mouse is pressed, drag the window.
     * (Note: You need to make sure that when calling this function, the left mouse button is pressed)
     */
    void dragMove();

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    Ui::FramelessWindow *ui;
    Thickness m_resizeThickness;
};
#endif // FRAMELESSWINDOW_H
