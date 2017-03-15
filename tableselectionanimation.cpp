#include "tableselectionanimation.h"
#include "ui_tableselectionanimation.h"
#include "frame.h"

#include <QScrollBar>
#include <QPropertyAnimation>
#include <QItemSelectionModel>
#include <QDebug>

static const int Duration = 300;
static const QEasingCurve::Type EasingCurve = QEasingCurve::OutCubic;

TableSelectionAnimation::TableSelectionAnimation(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::TableSelectionAnimation)
{
    m_ui->setupUi(this);
    m_ui->gridLayout->setContentsMargins(0, 0, 0, 0);

    QPalette p = m_ui->tableWidget->palette();
    p.setColor(QPalette::Highlight, Qt::white);
    p.setColor(QPalette::HighlightedText, Qt::blue);
    m_ui->tableWidget->setPalette(p);

    populateTable();
    m_frame = new Frame(this);
    m_frame->setColor(Qt::blue);
    m_frame->hide();

    auto updateSingleItem = [this] (QTableWidgetItem* item) {
        QRect itemRect = m_ui->tableWidget->visualItemRect(item);
        int horHeaderHeight = m_ui->tableWidget->horizontalHeader()->height();
        int verHeaderWidth = m_ui->tableWidget->verticalHeader()->width();
        m_frame->show();

        QRect newGeo(QPoint(itemRect.left() + verHeaderWidth, itemRect.top() + horHeaderHeight), itemRect.size());

        QPropertyAnimation* anim = new QPropertyAnimation(m_frame, "geometry");
        anim->setEasingCurve(EasingCurve);
        anim->setDuration(Duration);
        anim->setStartValue(m_frame->geometry());
        anim->setEndValue(newGeo);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    connect(m_ui->tableWidget, &QTableWidget::itemClicked, [=, this] (QTableWidgetItem* item) {
        updateSingleItem(item);
    });

    auto updateMultiItems = [this] (const QList<QTableWidgetItem*>& items) {
        if (items.isEmpty())
            return;

        QRect firstRect = m_ui->tableWidget->visualItemRect(items.first());
        QRect lastRect = m_ui->tableWidget->visualItemRect(items.last());

        int xMin = firstRect.topLeft().x();
        int yMin = firstRect.topLeft().y();
        int xMax = lastRect.bottomRight().x();
        int yMax = lastRect.bottomRight().y();

        int horHeaderHeight = m_ui->tableWidget->horizontalHeader()->height();
        int verHeaderWidth = m_ui->tableWidget->verticalHeader()->width();
        m_frame->show();

        QRect newGeo(QPoint(xMin + verHeaderWidth, yMin + horHeaderHeight), QSize(xMax - xMin, yMax - yMin));

        QPropertyAnimation* anim = new QPropertyAnimation(m_frame, "geometry");
        anim->setEasingCurve(EasingCurve);
        anim->setDuration(Duration);
        anim->setStartValue(m_frame->geometry());
        anim->setEndValue(newGeo);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    connect(m_ui->tableWidget, &QTableWidget::itemSelectionChanged, [=, this] {
        updateMultiItems(m_ui->tableWidget->selectedItems());
    });

    auto onScrollBarValueChanged = [this] (int) {
        QList<QTableWidgetItem*> selectedItems = m_ui->tableWidget->selectedItems();

        if (selectedItems.isEmpty())
            return;

        if (selectedItems.size() == 1) {
            QRect itemRect = m_ui->tableWidget->visualItemRect(selectedItems.first());
            int horHeaderHeight = m_ui->tableWidget->horizontalHeader()->height();
            int verHeaderWidth = m_ui->tableWidget->verticalHeader()->width();
            m_frame->show();

            QRect newGeo(QPoint(itemRect.left() + verHeaderWidth, itemRect.top() + horHeaderHeight), itemRect.size());

            QPropertyAnimation* anim = new QPropertyAnimation(m_frame, "geometry");
            anim->setEasingCurve(EasingCurve);
            anim->setDuration(Duration);
            anim->setStartValue(m_frame->geometry());
            anim->setEndValue(newGeo);
            anim->start(QAbstractAnimation::DeleteWhenStopped);

        } else if (selectedItems.size() >= 2) {
            QRect firstRect = m_ui->tableWidget->visualItemRect(selectedItems.first());
            QRect lastRect = m_ui->tableWidget->visualItemRect(selectedItems.last());

            int xMin = firstRect.topLeft().x();
            int yMin = firstRect.topLeft().y();
            int xMax = lastRect.bottomRight().x();
            int yMax = lastRect.bottomRight().y();

            int horHeaderHeight = m_ui->tableWidget->horizontalHeader()->height();
            int verHeaderWidth = m_ui->tableWidget->verticalHeader()->width();
            m_frame->show();

            QRect newGeo(QPoint(xMin + verHeaderWidth, yMin + horHeaderHeight), QSize(xMax - xMin, yMax - yMin));

            QPropertyAnimation* anim = new QPropertyAnimation(m_frame, "geometry");
            anim->setEasingCurve(EasingCurve);
            anim->setDuration(Duration);
            anim->setStartValue(m_frame->geometry());
            anim->setEndValue(newGeo);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }
    };

    connect(m_ui->tableWidget->horizontalScrollBar(), &QScrollBar::valueChanged, onScrollBarValueChanged);
    connect(m_ui->tableWidget->verticalScrollBar(), &QScrollBar::valueChanged, onScrollBarValueChanged);
}

TableSelectionAnimation::~TableSelectionAnimation()
{
    delete m_ui;
}

void TableSelectionAnimation::populateTable()
{
    const int Cols = 10;
    const int Rows = 100;

    m_ui->tableWidget->setColumnCount(Cols);
    m_ui->tableWidget->setRowCount(Rows);

    int index = 0;
    for (int col = 0; col < Cols; ++col) {
        for (int row = 0; row < Rows; ++row) {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString("Item %1").arg(++index));
            m_ui->tableWidget->setItem(row, col, item);
        }
    }
}
