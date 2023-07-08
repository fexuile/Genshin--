#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QWidget>
#include "role.h"

namespace Ui {
class EndWindow;
}

class EndWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndWindow(my_genshin*game, int flag, QWidget *parent = nullptr);
    ~EndWindow();

signals:
    void closeWindow(void);
    void quiting(void);
    void nexting(void);
private:
    Ui::EndWindow *ui;
};

#endif // ENDWINDOW_H
