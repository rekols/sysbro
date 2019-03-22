#ifndef TOOLSVIEW_H
#define TOOLSVIEW_H

#include <QListView>

class ToolsView : public QListView
{
    Q_OBJECT

public:
    ToolsView(QWidget *parent = nullptr);
    ~ToolsView();

/* protected: */
/*     bool eventFilter(QObject *obj, QEvent *e) override; */

/* private: */
/*     void fitToContent(); */
};

#endif
