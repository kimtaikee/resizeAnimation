#include "changeshapecanvas.h"
#include "ui_changeshapecanvas.h"
#include "graphicspathobject.h"
#include "graphicslineobject.h"
#include "graphicsellipseobject.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

inline QColor randomColor()
{
    return QColor(qrand() % 255, qrand() % 255, qrand() % 255);
}

ChangeShapeCanvas::ChangeShapeCanvas(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ChangeShapeCanvas)
{
    m_ui->setupUi(this);
    init();
}

ChangeShapeCanvas::~ChangeShapeCanvas()
{
    delete m_ui;
}

void ChangeShapeCanvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_scene->setSceneRect(rect());
}

void ChangeShapeCanvas::init()
{
    m_view = new QGraphicsView(this);
    m_ui->canvasLayout->addWidget(m_view);

    m_scene = new QGraphicsScene(this);
    m_view->setScene(m_scene);

    QPainterPath circle;
    circle.addEllipse(QRect(QPoint(0, 0), QSize(100, 100)));

    QPainterPath rect;
    circle.addRect(QRect(QPoint(100, 100), QSize(300, 400)));

    m_pathObj = new GraphicsPathObject(this);
    m_scene->addItem(m_pathObj);

    QPropertyAnimation* anim = new QPropertyAnimation(m_pathObj, "path");
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setDuration(1000);
    anim->setStartValue(QVariant::fromValue<QPainterPath>(circle));
    anim->setEndValue(QVariant::fromValue<QPainterPath>(rect));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ChangeShapeCanvas::on_addLineButton_clicked()
{
    QPoint initPoint(m_ui->point1XSpinBox->value(), m_ui->point1YSpinBox->value());
    QPoint endPoint(m_ui->point2XSpinBox->value(), m_ui->point2YSpinBox->value());

    GraphicsLineObject* line = new GraphicsLineObject;
    line->setFlag(QGraphicsItem::ItemIsMovable);
    line->setFlag(QGraphicsItem::ItemIsSelectable);
    line->setPoint1(initPoint);
    line->setPoint2(initPoint);
    line->setPen(QPen(randomColor(), 2));
    m_scene->addItem(line);

    QPropertyAnimation* anim = new QPropertyAnimation(line, "point2");
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setDuration(500);
    anim->setStartValue(QVariant::fromValue<QPoint>(initPoint));
    anim->setEndValue(QVariant::fromValue<QPoint>(endPoint));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ChangeShapeCanvas::on_addPieButton_clicked()
{
    QRect pieRect(QPoint(10, 10), QPoint(300, 300));

    GraphicsEllipseObject* ellipse = new GraphicsEllipseObject();
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
    ellipse->setFlag(QGraphicsItem::ItemIsSelectable);
    ellipse->setRect(pieRect);
    ellipse->setStartAngle(m_ui->startAngleSpinBox->value() * 16);
    ellipse->setBrush(QBrush(randomColor()));
    m_scene->addItem(ellipse);

    QPropertyAnimation* anim = new QPropertyAnimation(ellipse, "spanAngle");
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setDuration(500);
    anim->setStartValue(0);
    anim->setEndValue(m_ui->spanAngleSpinBox->value() * 16);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
