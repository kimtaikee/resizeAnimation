#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
    class Widget;
}

class QLabel;
class ColorBall;
class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float rotation READ rotation WRITE setRotation)
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    float rotation() const;
    void setRotation(float rotation);

public slots:
    void flyIn();
    void flyOut();

protected:
    QSize sizeHint() const;

private slots:
    void on_resizeButton_clicked();
    void on_easingCurveCombo_currentIndexChanged(int index);
    void doAnimation();
    void on_dropShadowCheckBox_toggled(bool checked);
    void on_shakeButton_clicked();
    void on_shrinkButton_clicked();
    void on_expandButton_clicked();
    void on_shakeDirectionCombo_currentIndexChanged(int index);
    void on_fadeInButton_clicked();
    void on_fadeOutButton_clicked();
    void on_flipButton_clicked();
    void on_newWindowButton_clicked();
    void on_changeShapeButton_clicked();
    void on_slideTextButton_clicked();
    void on_layoutWindowsButton_clicked();
    void on_toolButton_clicked();
    void on_popupWindowButton_clicked();
    void on_slideInButton_clicked();
    void on_slideOutButton_clicked();
    void on_tagButton_clicked();
    void on_imageCarouselButton_clicked();
    void on_bounceButton_clicked();
    void on_slideWidgetButton_clicked();
    void on_fadingCheckBox_toggled(bool checked);
    void on_tstFlowLayout_clicked();
    void on_explodeButton_clicked();
    void on_tableSelectionButton_clicked();
    void on_ledDisplayButton_clicked();
    void on_slideMenuButton_clicked();
    void on_shadowWindowButton_clicked();
    void on_inputButton_clicked();

private:
    Ui::Widget *m_ui;
    int m_easingCurve = 0; // default to linear
    QPoint m_shrinkOldPos;
    QSize m_shrinkOldSize;
    float m_rotation = 0;
    bool m_fliping = false;
    QLabel* m_flipLabel = nullptr;
    ColorBall* m_colorBall = nullptr;
};

#endif // WIDGET_H
